#ifndef _H_TYPES_H
#define _H_TYPES_H

enum type_e{
    num,
    str,
    dict,
    list
};

struct dict_s;
struct list_s;

typedef struct{
    enum type_e type;
    union{
        long long num;
        unsigned char* str;
        struct dict_s* dict;
        struct list_s* list;
    };
}item_t;

typedef struct dict_s{
    item_t* key;
    item_t* value;
    struct dict_s* next;
}dict_t;


typedef struct list_s{
    union{
        item_t* value;
        struct list_s* last; /*last filled only for first element of list, so, actual value will be stored starts from second element*/
    };
    struct list_s* next;

}list_t;

/*Functions*/
item_t* new_item(enum type_e type);
list_t* new_list();
#define new_dict() (NULL)
void add_to_dict(dict_t** dict, item_t *new_key, item_t *new_value);
void add_to_list(list_t* list, item_t* item);

#endif

