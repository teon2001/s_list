void test1(void *list, void (*free_info)(void *), void (*afisare)(void*));
void test2(void *list, int a, int b, int c, void (*afisare)(void*));
void test3(void* list, int a, int b, int c, int d, void (*free_info)(void *), void (*afisare)(void*)); 
void test4(void * list, int a, int b, int c, int d, int (*comp)(void *, void*), void (*afisare)(void*));
void test5(void* list, int a, void (*free_info)(void *));