void *h_create(int size_table, int (*hashf)(void *, int));
int h_insert(void* ht, void *nume_adresa, int size_nume_adresa, void* ip_adresa, int size_ip_adresa, void** list);
int h_delete(void* ht, void *nume_adresa, int size_nume_adresa, void (*free_info)(void *));
int h_exist(void *ht, void *nume_adresa, int size_nume_adresa, int (*comp)(void*, void*));
void h_free(void *ht, void (*free_info)(void *));
// void* h_resize(void *ht, int new_size, int (*hashf)(void *, int));
void h_print(void* ht, void (*print)(void*));
void* h_get_val(void* ht, void* nume_adresa, int size_nume_adresa, void* list);
void h_print_ip_adresa(void* ht, void (*print)(void*));
void h_print_list(void* ht, int idx, void (*print)(void*));