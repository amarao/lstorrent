item_t* get_record(item_t* root,const unsigned char* name);

typedef enum {
    skip,
    filename_only,
    filename_and_paths
}options_t;

typedef options_t (*pass_filter_callback_t(item_t* item));
/*right now return 0/1 to filter files*/

