#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Val{
    int key;
    void* info;
    //int hash_key;
    int size;
    //int size_info;
} Val;

typedef struct {
    void** table;
    int (*hashf)(void *, int, int);
    int size;
} Hasht;

void *h_create(int size, int (*hashf)(void *, int, int)) {
    Hasht *h = malloc(sizeof(Hasht));
    h->hashf = hashf;
    h->size = size;
    h->table = malloc(size * sizeof(void*));
    for(int i = 0; i < size; i++) {
        h->table[i] = l_create();
    }
    return h;
}

static Hasht *conv(void *ht) {
    return (Hasht *)ht;
}

static Val* create_node(void *val, int size, int key) {
    Val* cel = malloc(sizeof(Val));
    cel->info = val;
    cel->size = size;
    cel->key = key;
    return cel;
}

int h_insert(void* ht, void *val, int size) {
    Hasht* h = conv(ht);
    int idx = h->hashf(val, h->size, size);
    Val* cel = create_node(val, size, idx);
    return l_insert_first(&h->table[idx], cel);
}

static int comp_info(void* a, void* b) {
    //0 = egalitate
    if(((Val*)a)->size != ((Val*)b)->size) return 1;
    return memcmp(((Val*)a)->info, ((Val*)b)->info, ((Val*)a)->size);
}

static int comp(void *a, void *b) {
    //0 = egalitate
    if(((Val*)a)->size != ((Val*)b)->size) return 1;
    return memcmp(((Val*)a)->info, ((Val*)b)->info, ((Val*)b)->size);
}

static void free_val(Val* i, void (*free_info)(void *)) {
    free_info(i->info);
    free(i);
}

static void afisare(void* info) {
    printf("%d ", *(int*)((Val*)info)->info);
}

int h_delete(void* ht, void *val, void (*free_info)(void *), int size) {
    Hasht* h = conv(ht);
    int idx = h->hashf(val, h->size, size);
    Val wrapper;
    wrapper.info = val;
    wrapper.size = size; 
    void* i = l_remove_info(&h->table[idx], &wrapper, comp_info);
    free_val(i, free_info);
}

int h_exist(void *ht, void *val, int size ) {
    Hasht* h = conv(ht);
    int idx = h->hashf(val, h->size, size);
    return l_contains(h->table[idx], val, comp);
    
}

void h_free(void *ht, void (*free_info)(void *)) {
    Hasht* h = conv(ht);
    printf("h->size %d\n", h->size);
    for(int i = 0; i < h->size; i++) {
        printf("lalala %d  ", i);
        printf("adresa %p\n", h->table[i]);
        l_free(&h->table[i], free_info);
    }
    // free(h->table);
    free(h);
}

static int count_elements(Hasht* h) {
    int sum = 0;
    for(int i = 0; i < h->size; i++)
        sum = sum + l_length(h->table[i]);
    return sum;
}

/*
concatenare(rez, i) {
    for(iter; iter != NULL; iter = iter->next) {
        l_insert_last(i, iter->info)
    }
}

rez = l_create
for(pt lista)
concatenare(rez, i)
return rez
*/

static void* all_values(void* ht) {
    Hasht* h = conv(ht);
    void* res = l_create();

    for(int i = 0; i < h->size; i++) {
        int err = l_concat(&res, h->table[i]);

        if( err != 0 ) {
            return NULL;
        }
    }
    return res;
}

void* h_resize(void *ht, int new_size, int (*hashf)(void *, int, int)) {
    Hasht* h = conv(ht);
    void* new_h = h_create(new_size, hashf);
    void* vals = all_values(ht);
    void** vector;
    vector = l_vector(vals);
    for(int i = 0; i< l_length(vals); i++) {
        h_insert(new_h, ((Val*)vector[i])->info, ((Val*)vector[i])->size);
    }
    return new_h;
}

void h_print(void* ht, void (*print)(void*)) {
    Hasht* h = conv(ht);
    for(int i = 0; i< h->size; i++) {
        void** vector = l_vector(h->table[i]);
        printf("lista %d: ", i);
        for(int j =0; j < l_length(h->table[i]); j++) {
            print(((Val*)vector[j])->info);
        }
        printf("\n");
    }
}
