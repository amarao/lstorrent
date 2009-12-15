void* get_record( dict_t* root, const unsigned char* name);
void* print_file(char* root_dir, list_t* path, int mode,char finish);
int process_filelist(dict_t* root, int display, char finish);
#define MODE_DISPLAY_FILES 0x1
#define MODE_DISPLAY_DIRS 0x2
#define MODE_DISPLAY_PATHS 0x4


