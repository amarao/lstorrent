/*****************************************************************************
 *
 *  Middle level functions for lstorrent
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
#include <string.h>
#include <malloc.h>
#include "types.h"
#include "bdecode.h"
#include "functions.h"
#define DEBUG 1

item_t* get_record(item_t* root,const unsigned char* name){
/*records from dict*/
    dict_t* d;
    if (!root)
        return NULL;
    if (root->type!=dict_et)
        return NULL;
    d=root->dict;
    while(d){
        if(!strcmp(name,d->key))
            return d->value;
        d=d->next;    
    }
    return NULL;
}



void print_file_data(char* first_dir_name,item_t* f,int mode ){
//    item_t* length=get_record(f,"length"); /*right now has no meaning*/
    item_t* path=get_record(f,"path");
    list_t* l;
//    if(!(mode& MODE_DISPLAY_DIRS) && !(mode&MODE_DISPLAY_FILES))
//        return;

    if (path){

        if(first_dir_name){
            if(mode & MODE_DISPLAY_DIRS){
                printf("%s",first_dir_name);
                if(mode & MODE_DISPLAY_PATHS)
                    printf("/");
                else
                    printf ("\n");                
            }
        }
        
        l=path->list->next;
        while(l){
            if(l->next && mode & MODE_DISPLAY_DIRS){
                printf("%s",l->value->str);
                if( mode & MODE_DISPLAY_PATHS)
                    printf("/");
                else
                    printf("\n");
            }
            if(!l->next && mode & MODE_DISPLAY_FILES)
                printf("%s",l->value->str);
            if(!l->next && (mode & (MODE_DISPLAY_DIRS|MODE_DISPLAY_FILES)))
                printf ("\n");
            l=l->next;
       }

    }
}

int process_filelist(item_t* root, int display_flags){
    item_t* info=get_record(root,"info");
    item_t* filelist=get_record(info,"files");
    item_t* name;
    item_t* name_item;
    char* first_dir_name;
    list_t* l;
    if (!info)
        return 0;
    /*we have to cases: 'info' contains an files record for mutlifile torrent or contain data about file for single-file torrent*/
    if(!filelist){
    /*first case - single-file torrent without directories, we just print name*/
        if(display_flags&MODE_DISPLAY_FILES){
            name=get_record(info,"name");
            printf("%s\n",name->str);
        }
    /*second case - mulitfile torrent*/
    }else{ 
        name_item=get_record(info,"name");
        first_dir_name=name_item->str;
        l=filelist->list->next; /*skip first entry (used for technical needs of list)*/
        while(l){
            print_file_data(first_dir_name,l->value,display_flags);
            l=l->next;
        }
    }
}



