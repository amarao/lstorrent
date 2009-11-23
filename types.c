/*****************************************************************************
 *
 *  Data types emulation (dictionary and lists)
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


#include <malloc.h>
#include <stdio.h>
#include "ui.h"
#include "types.h"
#define MAX_RECORD 10000

list_t* new_list();
dict_t* new_dict();

item_t* new_item(enum type_e type){
    item_t* retval=calloc(1,sizeof(item_t));
    if(!retval)
        oops(err_nomem);
    retval->type=type;
    return retval;    
}

void add_to_dict(dict_t* dict, item_t *new_key, item_t *new_value){
    /*skip duplicate key check*/
    dict->count++;
//    #ifdef DEBUG
//        printf("realloc: %d,%d, %d\n",sizeof(dict->keys), dict->count,sizeof(dict->keys)*dict->count);
//    #endif
//    dict->keys=realloc(dict->keys,sizeof(dict->keys)*dict->count);
//    dict->values=realloc(dict->values,sizeof(dict->values)*dict->count);
//    if(!dict->keys || !dict->values)
//        oops(err_nomem);
    if( dict->count>MAX_RECORD )
        oops("Too many records");
    dict->keys[dict->count-1]=*new_key;
    dict->values[dict->count-1]=*new_value;
}


dict_t* new_dict(){
    dict_t* retval=calloc(1,sizeof(dict_t));
    retval->keys=calloc(MAX_RECORD,sizeof(item_t));
    retval->values=calloc(MAX_RECORD,sizeof(item_t));
    if(!retval)
        oops(err_nomem);
    return retval;
}

list_t* new_list(){
    list_t* retval=calloc(1,sizeof(list_t));
    retval->array=calloc(MAX_RECORD,sizeof(item_t));
    if(!retval)
        oops(err_nomem);
    return retval;
}


void add_to_list(list_t* list, item_t* item){
    list->count++;
//    list->array=realloc(list->array,sizeof(list->array)*list->count);
    if (list->count > MAX_RECORD)
        oops("Too many records");
    if (!list->array)
        oops(err_nomem);
    list->array[list->count-1]=*item;
}

