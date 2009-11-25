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
            for (c=0;c<tabs;c++)
                printf("    ");
            printf("%lli",item->num);
            break;
        case str:
           for (c=0;c<tabs;c++)
                printf("    ");
            printf("%s",item->str);
            break;
        case dict:
            d=item->dict;
            for( dc=0;dc<d->count;dc++){
                for (c=0;c<tabs;c++)
                    printf("    ");
                printf("(d)\n");
                print_item(d->keys+dc,tabs+1);
                printf(":");
                print_item(d->values+dc,tabs+1);
                printf("\n");
            }
            printf("\n");
            break;
        case list:
            l=item->list;
            for( lc=0;lc<l->count;lc++){
                for (c=0;c<tabs;c++)
                    printf("    ");
                printf("(l)\n");
                print_item(l->array+lc,tabs+1);
                printf("\n");
            }
            printf("\n");
            break;
    }
}


void debug(item_t* res){
    item_t* search;
    print_item(res,0);
    printf("-------------------------------------------\n");
    search=get_record(res,"info");
    print_item(search,0);
}
