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

typedef struct{
    char* filename;
    int path_parts_number;
    char **path_parts;
    long long size;
}file_t;

typedef struct{
    file_t file;
    item_t* root;
    int current;
}file_enum_t;

file_enum_t* get_first_file (item_t* root){
    file_enum_t* fe=calloc(1,sizeof(file_enum_t));
    fe->root=get_record(get_record(root,"info"),"files");
    if (!fe->root)
        return NULL;
    
}

int get_next_file (file_enum_t* fe){
}
