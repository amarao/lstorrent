#ifndef _H_TYPES_H
#define _H_TYPES_H

enum type_e{
    num_et,
    str_et,
    dict_et,
    list_et
};

struct dict_s;
struct list_s;

typedef struct{
    enum type_e type;
    union{
        void* data;
        char* str;
        struct dict_s* dict; 
        struct list_s* list;
    };
}item_t;

typedef struct dict_s{
    char* key;
    enum type_e type;
    union{
        char* str;
        void* data;
        struct dict_s* dict; 
        struct list_s* list;
    };
    struct dict_s* next;
}dict_t;


typedef struct list_s{
    int used;
    int allocated;
    item_t* values;/*array*/
}list_t;


/*Functions*/
void add_to_dict(dict_t** dict, char *new_key, enum type_e type,void* data);
list_t* new_list();
#define new_dict() (NULL)
void add_to_list(list_t* list, enum type_e type, void* data);
void add_to_dict(dict_t** dict, char *new_key, enum type_e type,void* data);
void del_dict(dict_t* dict);
void del_list(list_t* list);

#endif

