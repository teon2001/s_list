void *h_create(int size_table, int (*hashf)(void *, int));
int h_insert(void* ht, void *val, int size_val, void* key, int size_key);
int h_delete(void* ht, void *val, int size_val, void (*free_info)(void *));
int h_exist(void *ht, void *val, int size_val, void* key, int size_key);
void h_free(void *ht, void (*free_info)(void *));
void* h_resize(void *ht, int size, int (*hashf)(void *, int));
void h_print(void* ht, void (*print)(void*));
void* all_values(void* ht);