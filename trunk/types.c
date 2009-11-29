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

void add_to_dict(dict_t** dict, char *new_key, item_t *new_value){
    /*skip duplicate key check, we are not python...*/
    dict_t* newdict=malloc(sizeof(dict_t));
    if(!newdict){
        oops(err_nomem);
    }
    newdict->key=new_key;
    newdict->value=new_value;
    newdict->next=*dict;
    /*dicts has no order, so we use this - reversing order (FILO)*/
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
    newlist->next=NULL;
    newlist->last=NULL;
    if(list->last){
        list->last->next=newlist;
    }else{/*adding fist real element to empty list*/
        list->next=newlist;
    }
    list->last=newlist;
    newlist->value=item;
}

void del_dict(dict_t* dict){
    dict_t* d=dict;
    dict_t* temp;
    while(d){
        temp=d->next;
        free(d->key);
        del(d->value);
        free(d);
        d=temp;        

    }
}

void del_list(list_t* list){
    list_t* l=list->next; /*note, that 1st element contains no data*/
    list_t* temp;
    while(l){
        temp=l->next;
        if(!l->value) oops("!");
        del(l->value);
        l->value=NULL;
        free(l);
        l=temp;
    }
    free(list);    
}

void del(item_t* i){
    switch(i->type){
        case num_et:
            break;
        case str_et:
            if(!i->str) oops("!");
           free(i->str);
            i->str=NULL;
            break;
        case dict_et:
            if(!i->dict) oops("!");
            del_dict(i->dict);
            i->dict=NULL;
            break;
        case list_et:
            if(!i->list) oops("!");
            del_list(i->list);
            i->list=NULL;
            break;
        default:
            printf("some shit in del");
    }    
    free(i);
}

