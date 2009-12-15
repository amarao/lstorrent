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
#include <assert.h>
#include "types.h"
#include "bdecode.h"
#include "functions.h"
#define DEBUG 1

void* get_record( dict_t* root, const unsigned char* name){
//return value for 'name' in dictionary 'root' or NULL in nothing found of 'root' is NULL
    dict_t* d=root;
    while(d){
        if(!strcmp(name,d->key)){
            return d->data;
        }
        d=d->next;    
    }
    return NULL;
}

void* print_file(char* root_dir, list_t* path, int mode,char finish){
    /*
        print file data
        if MODE_DISPLAY_PATHS does not specified, does not print a root dir
    */
    int c;
    if(!path->used)
        return;
    if(mode & MODE_DISPLAY_PATHS){
        if(root_dir)
            if(*root_dir){
                printf("%s",root_dir);
                if(mode & MODE_DISPLAY_FILES || path->used>1){
                    printf("/");
                }
            }
        for(c=0;c<path->used-1;c++){
            printf("%s",path->values[c].str);
        }
        printf("%s%c",path->values[path->used-1].str,finish);
    }else{/*no paths - prints items per-line*/
        if(mode & MODE_DISPLAY_DIRS){
            for(c=0;c<path->used-1;c++){
                printf("%s%c",path->values[c].str,finish);
            }
        }
        if(mode & MODE_DISPLAY_FILES){
                printf("%s%c",path->values[path->used-1].str,finish);
        }
    }
    
}


int process_filelist(dict_t* root, int display, char finish){
    /* 
        we have two cases: single file and multiply files
        this desided by 'length' record in 'info' dict in 'root' dict
    */
    dict_t* info=get_record(root,"info");
    char* length=get_record(info, "length");
    char* name=get_record(info,"name");
    list_t* files;
    list_t* path;
    int fc;
    int pc;
    if (length){
        /*first case: single file - it name keeps in 'name' record in same root dict*/
        if(display & MODE_DISPLAY_FILES)
            printf("%s%c",name,finish);
    }
    else{
        /*
            second case: muliply files:
            more complificated - we have an 'name' record with name of "main directory" (where all other files are kept) and
            'files' record, with list of entries. Every entry is a dict of following structure and describe a single file:
                length - length of file
                path - list of strings, every string is part of filename, last piece is a  file_name_without_path

            to get full path of file in torrent we must join 'name' (from root) and every peice in 'path' list.
        */
        files=get_record(info,"files");
        assert(files);


        if (!(display & MODE_DISPLAY_PATHS) &&display  & MODE_DISPLAY_DIRS && name){ /*special case for item-per-line and main dir: it prints once*/
                if(*name)
                    printf("%s%c",name,finish);
        }

        for(fc=0;fc<files->used;fc++){
            path=get_record(files->values[fc].dict,"path");
            if(!path) /* TODO: in future here will be error reporting (path MUST be here)*/
                continue;
            print_file(name,path,display,finish);
        }
        
    }


}

