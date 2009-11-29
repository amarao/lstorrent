#ifndef _H_UI_H
#define _H_UI_H
extern const char* err_uncomplete;
extern const char* err_nomem;
extern const char* err_bad;
extern const char* err_internal;
extern const char* err_help;
extern const char* err_torrent_too_big;
extern const char* err_nostat;
extern const char* err_empty;
extern const char* err_noread;
#define oops(a) oops_message(a,__FILE__,__LINE__);   
#endif

