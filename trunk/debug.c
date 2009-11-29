#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "ui.h"
#include "bdecode.h"
#include "functions.h"

void print_item(item_t* item,int tabs){
/* mostly for debug */
    int c;
    dict_t* d;
    list_t* l;
    if (!item){
        printf("Item is NULL!\n");
        return;
    }
    switch(item->type){
        case num_et:
            printf("num(%lli)",item->num);
            break;
        case str_et:
            if(strlen(item->str)<80){
                printf("str(%s)",item->str);
            }else
                printf("str[%d]",strlen(item->str));
            break;
        case dict_et:
            d=item->dict;
            printf("dict(\n");
            while(d){
                for (c=0;c<tabs+1;c++)
                    printf("    ");
                printf("key =");
                printf("%d",d->key); /*fix ,tabs+2*/
                printf("\n");
                for (c=0;c<tabs+1;c++)
                    printf("    ");
                printf("value=");
                print_item(d->value,tabs+2);
                printf("\n");
                d=d->next;
            }
            for (c=0;c<tabs;c++)
                printf("    ");
            printf(" ) //dict end\n");
            break;
        case list_et:
            l=item->list->next;
            printf("list(\n");
            while(l){
                for (c=0;c<tabs;c++)
                    printf("    ");
                printf("(value)=");
                print_item(l->value,tabs+1);
                printf("\n");
                l=l->next;
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
//   print_item(res,0);
//    printf("-------------------------------------------\n");
    process_filelist(res,1); 
//    printf("============================================\n");
}
