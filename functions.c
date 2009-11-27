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

item_t* get_record(item_t* root,const unsigned char* name){
    int d;
    if (!root)
        return NULL;
    if (root->type!=dict)
        return NULL;
    for(d=0;d<root->dict->count;d++){
        if(!strcmp(name,root->dict->keys[d].str)){
            return root->dict->values + d;
        }
    }
    return NULL;
}



void print_file_data(char* first_dir_name,item_t* f){
    item_t* length=get_record(f,"length"); /*right now has no meaning*/
    item_t* path=get_record(f,"path");
    item_t* name=get_record(f,"name");
    int c;
    if (name){
        printf("%s\n",name->str);     
        return;
    }
    if (path){
        if(first_dir_name)
            printf("%s",first_dir_name);
        for(c=0;c<path->list->count;c++){
            if(c)
                printf("/");
            printf("%s",path->list->array[c].str);
        }
        printf("\n");
    }

}

int process_filelist(item_t* root, int display_flags){
    item_t* info=get_record(root,"info");
    item_t* filelist=get_record(info,"files");
    item_t* name_item;
    char* first_dir_name;
    int c;
    if (!info)
        return 0;
    /*we have to cases: 'info' contains an files record for mutlifile torrent or contain data about file for single-file torrent*/
    if(!filelist){
    /*first case - single-file torrent without directories, we just print name*/
        if(1){/*TODO here will be a case for display_flags*/
            print_file_data(NULL,info);
        }
    /*second case - mulitfile torrent*/
    }else{ 
        name_item=get_record(info,"name");
        first_dir_name=name_item->str;
        for(c=0;c<filelist->list->count;c++){
            if(1){/*display_flags will be here*/
                print_file_data(first_dir_name,filelist->list->array+c);
            }
        }
    }
}


