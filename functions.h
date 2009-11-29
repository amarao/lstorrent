item_t* get_record(item_t* root,const unsigned char* name);

typedef enum {
    skip,
    filename_only,
    filename_and_paths
}options_t;


#define MODE_DISPLAY_FILES 0x1
#define MODE_DISPLAY_DIRS 0x2
#define MODE_DISPLAY_PATHS 0x4

typedef options_t (*pass_filter_callback_t(item_t* item));
/*right now return 0/1 to filter files*/

