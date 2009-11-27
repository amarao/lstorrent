#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "bdecode.h"
#include "functions.h"
#include "ui.h"
#include "debug.h"
#include "errno.h"

//#define CUR (buf[*index]+0*printf("CUR = position: 0x%x, char: '%c'\n",*index,buf[*index]))



#define DEBUG 1


int main(int argc, char* argv[]){
#define MAX_FILE 1024*1024
    unsigned char* buf=malloc(MAX_FILE);
    int size=0;
    FILE* f;
    item_t * res;
    int c;
    if (argc<2){
        puts(err_help);
        exit(0);
    }
    for(c=1;c<argc;c++){
        f=fopen(argv[c],"rb");
        if(!f){
            printf("%s\n",strerror(errno));
            return -1;
        }
        size=fread(buf,1,MAX_FILE,f);
        if (size==MAX_FILE)
            oops(err_torrent_too_big);
        fclose(f);
        res=bdecode(buf,size);   
        debug(res);
    }
    return 0;
}
