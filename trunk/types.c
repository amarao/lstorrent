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

#define DEBUG 1

void add_to_dict(dict_t** dict, char *new_key, enum type_e type,void* data){
    /*skip duplicate key check, we are not python...*/
    dict_t* newdict=malloc(sizeof(dict_t));
    if(!newdict){
        oops(err_nomem);
    }
    newdict->key=new_key;
    newdict->data=data;/*same for str/dict/list pointers*/
    newdict->type=type;
    newdict->next=*dict;
    /*dicts has no order, so we use this - reversing order (FILO)*/
    *dict=newdict;
//    printf("add new key:%s\n",(*dict)->key);
//    if(type==str_et)
//        printf("add new value: %s\n",(*dict)->data);
//    else
//        printf("add new value (not str)\n");
}


list_t* new_list(){
    #define DEFAULT_LIST_SIZE 2
    list_t* newlist=malloc(sizeof(list_t));
    if(!newlist)
        oops(err_nomem);
    newlist->values=malloc(sizeof(item_t)*DEFAULT_LIST_SIZE);
    newlist->allocated=DEFAULT_LIST_SIZE;
    newlist->used=0;
    return newlist;
}

void add_to_list(list_t* list, enum type_e type, void* data){
    item_t* temp;    
    if(list->used==list->allocated){
        list->allocated=list->allocated+list->allocated/2;/* ==*1.5 */
        temp=realloc(list->values,sizeof(item_t)*(list->allocated));
        if(!temp)
            oops(err_nomem);
        list->values=temp;
    }
    list->values[list->used].type=type;
    list->values[list->used].data=data;
//    printf("add a new list entry:");
//    if(type==str_et)
//        printf("%s\n",list->values[list->used].data);
//    else
//        printf("(not str)\n");
    list->used++;
}


void del_dict(dict_t* dict){
    dict_t* d=dict;
    dict_t* temp;
    while(d){
        temp=d->next;
        free(d->key);
        switch(d->type){
            case dict_et:
                del_dict(d->dict);
                break;
            case list_et:
                del_list(d->list);
                break;
            /*we do not free() a strings - they are pointer to original buffer, not allocated memory*/
        }
        free(d);
        d=temp;        
    }
}

void del_list(list_t* list){

    int c;
    for(c=0;c<list->used;c++){
        switch(list->values[c].type){
            case dict_et:
                del_dict(list->values[c].dict);
                break;
            case list_et:
                del_list(list->values[c].list);
                break;
            /*we do not free() a strings - they are pointer to original buffer, not allocated memory*/
        }
    }
    free(list->values);    
    free(list);
}


