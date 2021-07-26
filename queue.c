#include "list.h"
#include "queue.h"
#include <stdlib.h>

void *q_create() {
    return list_create();
}

void enqueue(void **queue, void* val) {
    ins_la_final(queue, val);
}

void dequeue(void **queue, void (*free_info)(void *)) {
    del(queue, 0, free_info);
}

void *front(void* queue) {
    void* a = rmv(&queue, 0);
    ins(&queue, a);
    return a;
}

void free_queue(void **queue, void (*free_info)(void*)) {
    free_list(queue, free_info);
}

int queue_empty(void *queue) {
    return list_empty(queue);
}