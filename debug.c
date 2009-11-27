#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "ui.h"
#include "bdecode.h"
#include "functions.h"

void print_item(item_t* item,int tabs){
/* mostly for debug */
    int c;
    int dc,lc;
    dict_t* d;
    list_t* l;
    if (!item){
        printf("Item is NULL!\n");
        return;
    }
    switch(item->type){
        case num:
            printf("num(%lli)",item->num);
            break;
        case str:
            printf("str(%s)",item->str);
            break;
        case dict:
            d=item->dict;
            printf("dict(\n");
            for( dc=0;dc<d->count;dc++){
                for (c=0;c<tabs+1;c++)
                    printf("    ");
                printf("key (%d/%d)=",dc,d->count);
                print_item(d->keys+dc,tabs+2);
                printf("\n");
                for (c=0;c<tabs+1;c++)
                    printf("    ");
                printf("value (%d/%d)=",dc,d->count);
                print_item(d->values+dc,tabs+2);
                printf("\n");
            }
            for (c=0;c<tabs;c++)
                printf("    ");
            printf(" ) //dict end\n");
            break;
        case list:
            l=item->list;
            printf("list(\n");
            for( lc=0;lc<l->count;lc++){
                for (c=0;c<tabs;c++)
                    printf("    ");
                printf("(l%d/%d)=",lc,l->count);
                print_item(l->array+lc,tabs+1);
                printf("\n");
            }
            printf("\n");
            for (c=0;c<tabs;c++)
                printf("    ");
            printf(" ) //list end\n");
            break;
    }
}


void debug(item_t* res){
    item_t* search;
    print_item(res,0);
    printf("-------------------------------------------\n");
    process_filelist(res,1); 
}
