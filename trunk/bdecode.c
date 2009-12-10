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

#define DEBUG 1
#define NEXT (*index)++; if (*index>size) oops_message (err_uncomplete,__LINE__);
#define CUR (buf[*index])
#define MAX_STRING 15*1024*1024

static char last=0;
void* decode(unsigned char *buf, int *index, int *type, size_t size); /*for internal use only*/

void* decode_num(unsigned char *buf, int *index, size_t size){
/*
    We found a number in ASCII format and convert it to C-like string (adding a '\0' to end).
    string format (input: i99...999e; output: i99...999\0, we return pointer to first char after 'i')
*/
    void* data=buf+*index+1;
    if( !buf || !index)
        oops(err_internal);        
    if (size<3)
        oops(err_bad);
    NEXT;
    last=0;
    while(CUR!='e'){ 
        if (!isdigit(CUR))
            oops(err_bad);
        NEXT;
    }
    CUR=0; /*we replace 'e' at the end by \0 to make number type be a char* */
    last=0; /*we does not make any changes to 'future', so we not keep last char*/
    NEXT;
//	printf("decode_num=%s\n",data);
    return data;
}

void* decode_string(unsigned char* buf, int *index, size_t size){
/*
    We do a really DIRTY HACK here: we found a string and convert it to C-like (adding a '\0' to end.
    But we has no space for extra char at string end, so we copy 'next' char to global variable 'last' and REPLACE it with zero.
    It's really dirty, but allow us to skip a lots of memcpy() and reduce requied memory

    And note, we does not needs an reserve byte at file end, because any torrent file is a dict, 
    so it HAVE at least one 'e' char at end (witch one we replace with \0).
*/

    size_t str_len=0;
    void* retval;
    if (size<2)
        oops(err_bad);
//    printf("[in_decode_str]last:%d(%c), cur %d(%c), *index=%X\n",last,last,CUR,CUR,*index);
    if (last)
         str_len=last-'0';
    else
        str_len=CUR-'0';
    last=0;
    NEXT;
//  printf("str_len[0]=%d\n",str_len);
    while(isdigit(CUR)){
        str_len*=10;
        str_len+=(int)CUR-(int)'0';
        NEXT;
    }
//  printf("str_len=%d\n",str_len);
    if (str_len<0 || str_len>MAX_STRING){
        printf("%d\n",str_len);
        oops("string size is too big");
    }
    if (str_len+(*index)>size)
        oops(err_uncomplete);
    if( CUR==':' ){
        NEXT;
    }else{
        oops(err_bad);
    }
    retval=buf+(*index);
    (*index)+=str_len;
    last=CUR; /*keep changed char in global variable*/
    CUR=0;/*change it to '\0' to convert P-string to C-string*/
    safe(retval);
//    printf("decode_string=%s\n",retval);
    return retval;
}

dict_t* decode_dict(unsigned char *buf, int *index, size_t size){
    dict_t *retval=NULL;
    char  *key;
    void  *value;
    int type;
    int cmp;
    if( !buf || !index)
        oops(err_internal);        
    if (size<2)
        oops(err_bad);
    NEXT;
    last=0;
//    printf("enter a dict:%X\n",*index);
/*  here we got result of dirty hack in decode_string: 
    last MUST contain here or sero (and then CUR='d') or last='d' (and then CUR='\0'). 
    In any case this does not matter - skip
*/
    do{
        key=decode_string(buf,index,size);
//	printf("decode_key=%s\n",key);
        value=decode(buf,index,&type,size);
//	printf("decode_value=%s\n",value);
        add_to_dict(&retval,key,type,value);
//    printf("(after adding a rec)last:%d(%c), cur:%d(%c),*index=%X\n",last,last,CUR,CUR,*index);
    
        if (last)/*we handle here a dirty hack*/
            cmp=last;
        else
            cmp=CUR;
//        printf("Next char is %d(%c)\n",cmp,cmp);
//        last=0;
    }while(cmp!='e');
//    printf("dict_end=%X\n",*index);
    NEXT;
	last=0;
    return retval;
}


list_t* decode_list(unsigned char *buf, int *index, size_t size){
    list_t* retval=new_list();
    void* value;
    int type;
    char cmp=0;
    if( !buf || !index)
        oops(err_internal);        
    if (size<2)
        oops(err_bad);
    NEXT;
    last=0;
/*  here we got result of dirty hack in decode_string: 
     last MUST contain here or sero (and then CUR='l') or last='l' (and then CUR='\0'). 
    In any case this does not matter - skip
*/
    do{
        value=decode(buf,index,&type,size);
        add_to_list(retval,type,value);
        if (last)/*we handle here a dirty hack*/
            cmp=last;
        else
            cmp=CUR;
    }while(cmp!='e');
//    printf("list_end=%X\n",*index);
    NEXT;
	last=0;
    return retval;
}



void* decode(unsigned char *buf, int *index, int *type, size_t size){
/*decode anything with autodetection. For dicts/lists become recursive*/
    void *retval=NULL;
    char cmp;
    if( !buf || !index)
        oops(err_internal);        
    if (!size || *index+1>=size)
        oops(err_bad);

/*  here we got result of dirty hack of decode_string (or not got!) 
    or current char keeps in 'last', or (if last is zero), current char in untoched*/
    if(last)
        cmp=last;
    else
        cmp=CUR;
    switch (cmp){
        case 'i':
            retval=decode_num(buf,index,size);
            *type=str_et; /*yes, we decode numbers as strings, if someone decide to process it - atoi() will help*/
            break;
        case 'd':
            retval=decode_dict(buf,index,size);
            *type=dict_et;
            break;
        case 'l':
            retval=decode_list(buf,index,size);
            *type=list_et;
            break;
        default:
            if(isdigit(cmp)){ /*note - not isdigit(CUR), but isdigit (cmp) - see note above about dirty hack*/
                retval=decode_string(buf,index,size);
                *type=str_et;
                break;
            }
            else{
                oops(err_bad);
            }
    }
//	printf("debug: decode=(%d)%s\n",*type,retval);
    return retval;   

}

dict_t* bdecode(unsigned char*buf, size_t size){
/*decorator for export*/
    int pos=0;
    return decode_dict(buf, &pos, size);
}
