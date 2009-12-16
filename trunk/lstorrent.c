#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include "types.h"
#include "bdecode.h"
#include "functions.h"
#include "ui.h"
#include "debug.h"
#include "errno.h"



int main(int argc, char* argv[]){
#define MAX_FILE_SIZE 64*1024*1024
/*
      I think, this is resonally big for *.torrent file. If you wish, you can 
      try to use bigger values, but note, that parsing of files requied about 6 times 
      of buffer size memory
*/

    unsigned char* buf;
    size_t size=0;
    size_t fsize=0;
    size_t old_size=0;
    FILE* f;
    dict_t *torrent;
    struct stat st;    
    int c;
    int display_mode=7;
    if (argc<2){
        puts(err_help);
        exit(0);
    }
    for(c=1;c<argc;c++){
        if(stat(argv[c],&st)){
            printf(err_nostat,argv[c],strerror(errno));
            continue;
        };
        fsize=st.st_size;
        if(!fsize){
            printf(err_empty,argv[c]);
            continue;
        }
        if(fsize<=0||fsize>MAX_FILE_SIZE){
            printf(err_torrent_too_big,argv[c],(intmax_t)fsize);
            continue;
        }
        if(fsize>old_size){ //fist file: fsize is not zero, old_size==0
            if(old_size){
                free(buf);
            }
            buf=malloc(fsize+SAFE_PAD);
            if(!buf){
                printf(err_nomem);
                continue;
            }
        }//if we already have a large buffer, we can reuse it again
        f=fopen(argv[c],"rb");
        if(!f){
            printf("%s\n",strerror(errno));
            continue;
        }
        size=fread(buf,1,fsize,f);
        if (size!=fsize){
            printf(err_noread,argv[c],strerror(errno));
            continue;
        }
        fclose(f);
        buf[fsize]=0;
        torrent=bdecode(buf,size);   
//    	debug(torrent);
//        printf("---\n");
        process_filelist(torrent, display_mode,'\n');
        del_dict(torrent);
    }

    return 0;
}
