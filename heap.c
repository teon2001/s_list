#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

struct heap{
    void **v;
    int size;
    int capacity;
    int (*comp)(void*, void*);
};

Heap* heap_create(int capacity, int (*comp)(void*, void*)) {
    Heap* h;
    h = malloc(sizeof(Heap));
    h->size = 0;
    if(capacity <= 0)
        capacity = 1;
    h->v = malloc(capacity * sizeof(void*));
    h->capacity = capacity;
    h->comp = comp;
    return h;
}

static int expand(Heap* h) {
    h->v = realloc(h, h->capacity * 2);
    //daca nu reuseste realocarea
    if(h->v == NULL) return 1;
    h->capacity = 2 * h->capacity;
    return 0;
}

static int get_parent(int idx) {
    return (idx-1)/2; 
}

static void swap(void** a, void** b)  {
    void* aux = *a;
    *a = *b;
    *b = aux;
}

static void siftup(Heap* h) {
    int idx = h->size - 1;
    int parent = get_parent(idx);

    while( idx > 0 && (h->comp(h->v[idx], h->v[parent]) < 0)) {
        swap(&h->v[idx], &h->v[parent]);
        idx = parent;
        parent = get_parent(idx);
    }
}

int heap_insert(Heap* h, void* val) {
    if(h->size == h->capacity) {
        int err = expand(h);
        if(err == 1) 
            return 1;
    }
    h->v[h->size++] = val;
    siftup(h);
    return 0;
}

//p:0
//c:1         c:2
//c:3, c:4    c:5, c:6
static int get_left_child(int idx) {
    return 2 * idx + 1; 
}

static int get_right_child(int idx) {
    return get_left_child(idx) + 1; 
}

static int get_min(Heap* h, int idx_a, int idx_b, int (*comp)(void*, void*)) {
    if(h->v[idx_a] == NULL) return idx_b;
    if(h->v[idx_b] == NULL) return idx_a;

    if (comp(h->v[idx_a], h->v[idx_b]) > 0)
        return idx_b;
    else 
        return idx_a;
}

static void print(void* val) {
    printf("%d ", *(int*)val);
}

static void siftdown(Heap* h, int (*comp)(void*, void*)) {
    int idx = 0;
    if(h->size == 1) return;
    int left_child = get_left_child(idx);
    int right_child = get_right_child(idx);

    int min = get_min(h, left_child, right_child, comp);

    while(min < h->size && h->comp(h->v[idx], h->v[min]) > 0) {
        swap(&h->v[idx], &h->v[min]);
        idx = min;
        left_child = get_left_child(idx);
        right_child = get_right_child(idx);
        
        if(left_child > h->size && right_child <= h->size)
            min = right_child;
        else if(left_child <= h->size && right_child > h->size)
            min = left_child;
        else if(left_child > h->size && right_child > h->size)
            return;
        else min = get_min(h, left_child, right_child, comp);
    }
}

void *heap_remove(Heap* h, void (*free_info)(void*), int (*comp)(void*, void*)) {
    if(h == NULL) 
        return NULL;
    
    if( h->size == 0) 
        return NULL;
    void* aux = h->v[0];
    swap(&h->v[0], &h->v[h->size-1]);
    h->v[h->size-1] = NULL;
    free_info(h->v[h->size-1]);
    h->size--;
    siftdown(h, comp);
    return aux;
}

void heap_free(Heap* h, void (*free_info)(void*)) {
    for(int i = 0; i <  h->size; i++) {
        free_info(h->v[i]);
    }
    free(h->v);
    free(h);
}

void heap_print(Heap* h, void (*print)(void*)) {
    for(int i = 0; i < h->size; i++) {
        print(h->v[i]);
    }
    printf("\n");
}
