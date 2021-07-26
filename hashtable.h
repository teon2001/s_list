void *h_create(int size, int size_info, int (*hashf)(void *, int, int));
int h_ins(void* ht, void *val);
// int h_del(void* ht, void *val);
int h_exist(void *ht, void *val);
// void h_free(void *ht);
// int h_resize(void *ht, int size);