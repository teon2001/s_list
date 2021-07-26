void *st_create();
void push(void **stack, void* val);
void *pop(void **stack);
void *top(void *stack);
int stack_empty(void *stack);
void free_stack(void **stack, void (*free_info)(void*));