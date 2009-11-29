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

//#define CUR (buf[*index]+0*printf("CUR = position: 0x%x, char: '%c'\n",*index,buf[*index]))



#define DEBUG 1


int main(int argc, char* argv[]){
#define MAX_FILE_SIZE 40*1024*1024
/*I think, this is resonally big for *.torrent file. If you wish, you can try to use bigger values, but note, that parsing of files requied about 9 times of buffer size memory*/

    unsigned char* buf;
    off_t size=0;
    off_t fsize=0;
    FILE* f;
    item_t * res;
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
        if(fsize<0||fsize>MAX_FILE_SIZE){
            printf(err_torrent_too_big,argv[c],(intmax_t)fsize);
            continue;
        }
        buf=malloc(fsize+1);
        if(!buf){
            printf(err_nomem);
            continue;
        }
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
        res=bdecode(buf,size);   
        free(buf);
        process_filelist(res, display_mode);
        del(res);
    }

    return 0;
}
