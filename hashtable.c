#include "list.h"
#include <stdlib.h>

static int size_info;
typedef struct {
    void** table;
    int size_info;
    int (*hashf)(void *, int, int);
    int size;
} Hasht;

void *h_create(int size, int size_infoo, int (*hashf)(void *, int, int)) {
    Hasht *h = malloc(sizeof(Hasht));
    h->hashf = hashf;
    h->size = size;
    h->size_info = size_infoo;
    size_info = size_infoo;
    h->table = malloc(size * sizeof(void*));
    for(int i = 0; i < size; i++) {
        h->table[i] = list_create();
    }
    return h;
}

static Hasht *conv(void *ht) {
    return (Hasht *)ht;
}

int h_ins(void* ht, void *val) {
    Hasht* h = conv(ht);
    int idx = h->hashf(val, h->size, h->size_info);
    //erori->list
    ins(&h->table[idx], val);
    return 0;
}



static int comp(void *a, void *b) {
    char acc1 = 0, acc2 = 0;
    for(int i = 0; i< size_info; i++) {
        if(*((char*)a + i) != *((char*)b + i)) return 1;
    }
    return 0;
}

int h_del(void* ht, void *val);
int h_exist(void *ht, void *val ) {
    Hasht* h = conv(ht);
    int idx = h->hashf(val, h->size, h->size_info);
    return contains(h->table[idx], val, comp);
    
}

void h_free(void *ht);
int h_resize(void *ht, int size);