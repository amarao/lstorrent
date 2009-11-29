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

list_t* new_list();

item_t* new_item(enum type_e type){
    item_t* retval=calloc(1,sizeof(item_t));
    if(!retval)
        oops(err_nomem);
    retval->type=type;
    return retval;    
}

void add_to_dict(dict_t** dict, item_t *new_key, item_t *new_value){
    /*skip duplicate key check, we are not python...*/
    dict_t* newdict=malloc(sizeof(dict_t));
    if(!newdict){
        oops(err_nomem);
    }
    newdict->key=new_key;
    newdict->value=new_value;
    newdict->next=*dict;
    /*dicts has no order, so we use this - reversing up the order*/
    *dict=newdict;
}

list_t* new_list(){
    list_t* newlist=calloc(1,sizeof(list_t));
    if(!newlist)
        oops(err_nomem);
    return newlist;
}

void add_to_list(list_t* list, item_t* item){
    list_t* newlist=malloc(sizeof(list_t));
    if(!newlist)
        oops(err_nomem);
    if(!list)
        oops("shit");
    if(list->next){
        list->last->next=newlist;
    }else{/*adding fist real element to empty list*/
        list->next=newlist;
    }
    list->last=newlist;
    newlist->value=item;
}

