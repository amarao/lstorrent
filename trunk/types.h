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
    int count;
    item_t* keys;
    item_t* values;
}dict_t;


typedef struct list_s{
    int count;
    item_t* array;
}list_t;

/*Functions*/
item_t* new_item(enum type_e type);
dict_t* new_dict();
list_t* new_list();
void add_to_dict(dict_t* dict, item_t *new_key, item_t *new_value);
void add_to_list(list_t* list, item_t* item);

#endif

