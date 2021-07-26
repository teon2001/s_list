#include "list.h"
#include "stack.h"
#include <stdlib.h>

void *st_create() {
    return list_create();
}

void push(void **stack, void* val) {
    ins(stack, val);
}

void *pop(void **stack) {
    return rmv(stack, 0);
}

void *top(void *stack) {    
    void* a = rmv(&stack, 0);
    if(a == NULL) return NULL;
    ins(&stack, a);
    return a;
} 

int stack_empty(void *stack) {
    return list_empty(stack);
}

void free_stack(void **stack, void (*free_info)(void*)) {
    free_list(stack, free_info);
}

