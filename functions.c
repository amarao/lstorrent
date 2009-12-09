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
    dict_t* d=root;
    while(d){
        if(!strcmp(name,d->key)){ /*here little risk, that name is bigger than avaible chars in buf - we fix it by inresizeing buff  */
            return d->data;
        }
        d=d->next;    
    }
    return NULL;
}



/*void print_file_data(char* first_dir_name,item_t* f,int mode ){
//    item_t* length=get_record(f,"length");
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
*/

int process_filelist(dict_t* root, int display_flags){
    return 0;
}
//UNDER DEBUG!
/*    dict_t* info=get_record(root,"info");
    list_t* filelist=get_record(info,"files");
    void* name;
    void* name_item;
    char* first_dir_name;
    list_t* l;
    int lc;
    int pc;
    list_t* path;

    if (!info){
        printf("none\n");
        return 0;
    }
    //we have to cases: 'info' contains an files record for mutlifile torrent or contain data about file for single-file torrent
    if(!filelist){
    //first case - single-file torrent without directories, we just print name
        if(1){
            name=get_record(info,str_et,"name");
            //process string here
            printf("%s\n",real_decode_string(name));
        }
    //second case - mulitfile torrent
    }else{ 
        first_dir_name=real_decode_string((unsigned char*)get_record(info,str_et,"name"));
        for(lc=0;lc<filelist->used;lc++){
            path=get_record(filelist->values[lc].dict,list_et,"path");
//            print_file_data(first_dir_name,l->value,display_flags);
            printf("%s",first_dir_name);
            for(pc=0;pc<path->used;pc++){
                printf("/%s",real_decode_string(path->values[pc].data));
            }
            printf("\n");
        }
    }
}


*/
