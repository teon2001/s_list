//MinHeap
typedef struct heap Heap;

Heap* heap_create();
int heap_insert(Heap* heap, void* val);
void *heap_remove(Heap* heap, void (*free_info)(void*));
void heap_free(Heap* heap, void (*free_info)(void*));
void heap_print(Heap* heap, void (*print)(void*));
