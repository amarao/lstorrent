#include <stdio.h>
#include <stdlib.h>
#include "ui.h"


const char* err_uncomplete="bad format or uncomplete file";
const char* err_nomem="not enough memory";
const char* err_bad="bad file format";
const char* err_internal="internal error (bad call or bad parameters)";
const char* err_help="(here must be help)";
const char* err_torrent_too_big="File %s is too big (%d), skipping\n";
const char* err_nostat="stat() error for file %s: %s\n";
const char* err_empty="File %s is empty, skipping.\n";
const char* err_noread="Unable to read %s: %s\n";

void oops_message(const char* message, const char* file,int line){
    printf ("(%s:%d): %s\n",file,line,message);
    exit(-1);
}

