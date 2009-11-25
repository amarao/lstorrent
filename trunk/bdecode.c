/*****************************************************************************
 *
 *  Bencodered files (*.torrent data format) decoder
 *      part of lstorrent application
 *
 *  Copyright(C) 2009      George Shuklin <amarao@desunote.ru>
 *                          http://desunote.ru/soft/lstorrent
 *
 *  This program is free software ; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation ; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY ; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 ****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "bdecode.h"
#include "ui.h"

#define NEXT (*index)++; if (*index>size) oops_message (err_uncomplete,__LINE__);
#define CUR (buf[*index])

#define MAX_RECORD 10000

item_t* decode(unsigned char *buf, int *index, size_t size);

long long decode_num(unsigned char *buf, int *index, size_t size){
    long long retval=0;
    if( !buf || !index)
        oops(err_internal);        
    if (size<3)
        oops(err_bad);
    if (CUR!='i')
        oops(err_internal);
    NEXT;
    while(CUR!='e'){ 
        if (!isdigit(CUR))
            oops(err_bad);
        retval*=10;
        retval+=(int)CUR-(int)'0';
        NEXT;
    }
    NEXT;
    return retval;
}

item_t* decode_num_t(unsigned char *buf, int *index, size_t size){
    item_t* retval=new_item(num);
    retval->num=decode_num(buf,index,size);
    return retval;
}

unsigned char* decode_string(unsigned char *buf, int *index, size_t size){
    unsigned char* retval=NULL;
    size_t str_len=0;
    #define MAX_STRING 1024*1024
    if( !buf || !index)
        oops(err_internal);        
    if (size<2)
        oops(err_bad);
    if (! isdigit(CUR))
        oops(err_internal);
    while(isdigit(CUR)){
        str_len*=10;
        str_len+=(int)CUR-(int)'0';
        NEXT;
    }
    if( CUR==':' ){
        NEXT;
    }
    else{
        oops(err_bad);
    }
    if (str_len<0 || str_len>MAX_STRING)
        oops("string size is too big");
    retval=calloc(1,str_len+1);
    if (!retval)
        oops(err_nomem);
    if (str_len+(*index)>size)
        oops(err_uncomplete);
    if (str_len>0){
        memcpy(retval,buf+(*index),str_len);
        (*index)+=str_len;
    }
    return retval;
}


item_t* decode_str_t(unsigned char *buf, int *index, size_t size){
    item_t* retval=new_item(str);
    retval->str=decode_string(buf,index,size);
    return retval;
}




dict_t* decode_dict(unsigned char *buf, int *index, size_t size){
    dict_t* retval=new_dict();
    item_t  *key,*value;
    if( !buf || !index)
        oops(err_internal);        
    if (size<2)
        oops(err_bad);
    if (CUR!='d')
        oops(err_internal);
    NEXT;
    while(CUR!='e'){
        key=decode(buf,index,size);
        value=decode(buf,index,size);
        /*here we simply drop 'pieces' record (with human-unreadable SHA1 hashes)*/
        if(strcmp(key->str,"pieces"))
            add_to_dict(retval,key,value);
        else{
            free(key->str);
            free(value->str);/*about 3/4 of all *.torrent's size - better to clean*/
            free(key);
            free(value); 
        }
    }
    NEXT;
    return retval;
}

item_t* decode_dict_t(unsigned char *buf, int *index, size_t size){
    item_t* retval=new_item(dict);
    retval->dict=decode_dict(buf,index,size);
    return retval;
}

list_t* decode_list(unsigned char *buf, int *index, size_t size){
    list_t* retval=new_list();
    item_t* value;
    if( !buf || !index)
        oops(err_internal);        
    if (size<2)
        oops(err_bad);
    if (CUR!='l')
        oops(err_internal);
    NEXT;
    while(CUR!='e'){
        value=decode(buf,index,size);
        add_to_list(retval,value);
//        NEXT;
    }
    NEXT;
    return retval;
}


item_t* decode_list_t(unsigned char *buf, int *index, size_t size){
    item_t* retval=new_item(list);
    retval->list=decode_list(buf,index,size);
    return retval;
}

item_t* decode(unsigned char *buf, int *index, size_t size){
/*decode anything with autodetection. For dicts/lists become recursive*/
    item_t *retval=NULL;
    if( !buf || !index)
        oops(err_internal);        
    if (!size || *index+1>=size)
        oops(err_bad);
    switch (CUR){
        case 'i':
            retval=decode_num_t(buf,index,size);
            break;
        case 'd':
            retval=decode_dict_t(buf,index,size);
            break;
        case 'l':
            retval=decode_list_t(buf,index,size);
            break;
        default:
            if(isdigit(CUR)){
                retval=decode_str_t(buf,index,size);
                break;
            }
            else{
                oops(err_bad);
            }
    }
    return retval;   

}

item_t* bdecode(unsigned char*buf, size_t size){
/*decorator for export*/
    int pos=0;
    return decode(buf,&pos,size);
}
