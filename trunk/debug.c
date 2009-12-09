#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "ui.h"
#include "bdecode.h"
#include "functions.h"
#include "debug.h"

space(int tabs){
    int c;
    for (c=0;c<tabs+1;c++)
        printf("    ");

}

void print_dict(dict_t* dict,int tabs){
    dict_t* d;
    if (!dict){
        printf("Item is NULL!\n");
        return;
    }

    d=dict;
    while(d){
	space(tabs);
        printf("dict_key = %d\n",d->key);
	space(tabs);
        printf("dict_value=");
        switch(d->type){
            case num_et://impossible
                printf("YOU ARE SHOCK!!! (got a num_et here)");
                break;
            case str_et:
                if(strlen(dict->str)<60)
                    printf("str(%s)",dict->str);
                else
                    printf("str[%d]",strlen(dict->str));
                break;
            case dict_et:
                printf("dict(\n");
                print_dict(d->dict,tabs+2);
		space(tabs);
                printf(") //dict end\n");
                break;
            case list_et:
                printf("list(\n");
                print_list(d->list,tabs+2);
		space(tabs);
                printf(") //list end\n");
                break;
        }
	printf("\n");
	d=d->next;
    }
}

void print_list(list_t* list,int tabs){
    int c;
    int lc;
    if (!list ){
        printf("Item is NULL!\n");
        return;
    }
    for(lc=0;lc<list->used;lc++){
	space(tabs);
        printf("list_item=");
        switch(list->values[lc].type){
            case num_et://impossible
                printf("YOU ARE SHOCK!!! (got a num_et here)");
                break;
            case str_et:
                if(strlen(list->values[lc].str)<60)
                    printf("str(%s)",list->values[lc].str);
                else
                    printf("str[%d]",strlen(list->values[lc].str));
                break;
            case dict_et:
                printf("dict(\n");
                print_dict(list->values[lc].dict,tabs+2);
		space(tabs);
                printf(") //dict end\n");
                break;
            case list_et:
                printf("list(\n");
                print_list(list->values[lc].list,tabs+2);
		space(tabs);
                printf(") //list end\n");
                break;
        }
        printf("\n");
    }

}

void debug(dict_t* res){
   print_dict(res,0);
//    printf("-------------------------------------------\n");
 //   process_filelist(res,1); 
//    printf("============================================\n");
}
