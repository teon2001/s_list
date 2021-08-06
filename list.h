    /**
     * functia parametru comp: 0 = egalitate 
     * in l_contains: 1-lista contine val
                      0-lista nu contine val
     */

void *l_create();
int l_insert_first(void **list, void *val);
int l_insert_last(void **list, void* val);
int l_delete(void **list, int idx, void (*free_info)(void *));
void *l_remove(void **list, int idx);
void *l_remove_info(void **list, void *val, int (*comp)(void*, void*));
int l_contains(void *list, void *val, int (*comp)(void *, void*));
void l_print(void *list, void(*print)(void*));
int l_length(void *list);
void l_free(void **list, void (*free_info)(void *));
int l_empty(void *list);
void* get_value(void* list, int j);
int l_concat(void** res_list, void* list1, void* list2);
void** l_to_vector(void* list);
void* get_info(void* node);
void l_free_info(void **list);
int l_include(void* list1, void* list2, int (*comp)(void*, void*));
void *l_return_node(void *list, void* val, int (*comp)(void*, void*));