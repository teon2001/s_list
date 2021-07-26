void *q_create();
void enqueue(void **queue, void* val);
void dequeue(void **queue, void (*free_info)(void *));
void *front(void* queue);
void free_queue(void **queue, void (*free_info)(void*));
int queue_empty(void *queue);