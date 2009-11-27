#include <stdio.h>
#include <stdlib.h>
#include "ui.h"


const char* err_uncomplete="bad format or uncomplete file";
const char* err_nomem="not enough memory";
const char* err_bad="bad file format";
const char* err_internal="internal error (bad call or bad parameters)";
const char* err_help="(here must be help)";
const char* err_torrent_too_big="Torrent is too big";

void oops_message(const char* message,int line){
    printf ("%d: %s\n",line,message);
    exit(-1);
}
#define oops(a) oops_message(a,__LINE__);   
