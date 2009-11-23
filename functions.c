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


typedef enum {
    skip,
    filename_only,
    filename_and_paths
}options_t;

typedef options_t (*pass_filter_callback_t(item_t* item));

int process_filelist(item_t* root, pass_filter_callback_t *filter){
    item_t* file_info=get_record(get_record(root,"info"),"files");
    item_t* cur;
    if (!file_info)
        return 0;

}
