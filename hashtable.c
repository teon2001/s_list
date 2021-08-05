#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Val{
    void* key; // numele, www.google.com
    int size_key;
    void* info; // adresa IP, 8.8.8.8
    int size_info;
    int key_hash; // index hash
} Val;

typedef struct {
    void** table;
    int (*hashf)(void *, int);
    int size_table;
} Hasht;

void *h_create(int size_table, int (*hashf)(void *, int)) {
    Hasht *h = malloc(sizeof(Hasht));
    h->hashf = hashf;
    h->size_table = size_table;
    h->table = malloc(size_table * sizeof(void*));
    for(int i = 0; i < size_table; i++) {
        h->table[i] = l_create();
    }
    return h;
}

static Hasht *conv(void *ht) {
    return (Hasht *)ht;
}

static Val* create_node(void *val, int size_val, void* key, int size_key, int key_hash) {
    Val* cel = malloc(sizeof(Val));
    cel->info = val;
    cel->size_info = size_val;
    cel->key = key;
    cel->size_key = size_key;
    cel->key_hash = key_hash;
    return cel;
}

int h_insert(void* ht, void *val, int size_val, void* key, int size_key) {
    Hasht* h = conv(ht);
    int idx = h->hashf(val, h->size_table);
    Val* cel = create_node(val, size_val, key, size_key, idx);
    return l_insert_first(&h->table[idx], cel);
}

static int comp_info(void* a, void* b) {
    //0 = egalitate
    if(((Val*)a)->size_info != ((Val*)b)->size_info) return 1;
    return memcmp(((Val*)a)->info, ((Val*)b)->info, ((Val*)a)->size_info);
}

static int comp(void *a, void *b) {
    //0 = egalitate
    if(((Val*)a)->size_info != ((Val*)b)->size_info) return 1;
    return memcmp(((Val*)a)->info, ((Val*)b)->info, ((Val*)b)->size_info);
}

static void free_val(Val* i, void (*free_info)(void *)) {
    free_info(i->key);
    free_info(i->info);
    free(i);
}

// static void afisare(void* info) {
//     printf("%d ", *(int*)((Val*)info)->info);
// }

int h_delete(void* ht, void *val, int size_val, void (*free_info)(void *)) {
    Hasht* h = conv(ht);
    int idx = h->hashf(val, h->size_table);
    Val wrapper;
    wrapper.info = val;
    wrapper.size_info = size_val;
    // wrapper.key = key;
    // wrapper.size_key = size_key; 
    void* i = l_remove_info(&h->table[idx], &wrapper, comp_info);
    printf("point: %p\n", i);
    if(i == NULL) return 1;
    free_val(i, free_info);
    return 0;
}

int h_exist(void *ht, void *val, int size_val, void* key, int size_key) {
    Hasht* h = conv(ht);
    int idx = h->hashf(val, h->size_table);

    Val wrapper;
    wrapper.info = val;
    wrapper.size_info = size_val;
    wrapper.key = key;
    wrapper.size_key = size_key;  
    return l_contains(h->table[idx], &wrapper, comp);
}

void h_free(void *ht, void (*free_info)(void *)) {
    Hasht* h = conv(ht);
    // printf("h->size %d\n", h->size);
    for(int i = 0; i < h->size_table; i++) {
        // printf("lalala %d  ", i);
        // printf("adresa %p\n", h->table[i]);
        while(!l_empty(h->table[i])) {
            void* iter = l_remove(&h->table[i], 0);
            if(iter == NULL) break;
            free_val(iter, free_info);
        }
    }
    free(h->table);
    free(h);
}

// static int count_elements(Hasht* h) {
//     int sum = 0;
//     for(int i = 0; i < h->size_table; i++)
//         sum = sum + l_length(h->table[i]);
//     return sum;
// }

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

void* all_values(void* ht) {
    Hasht* h = conv(ht);
    void* res = l_create();

    for(int i = 0; i < h->size_table; i++) {
        if(h->table[i] != NULL) {
            int err = l_concat(&res, h->table[i], NULL);
            if( err != 0 ) return NULL;
        }
    }
    return res;
}

void* h_resize(void *ht, int new_size, int (*hashf)(void *, int)) {
    void* new_h = h_create(new_size, hashf);
    void* vals = all_values(ht);
    void** vector;
    vector = l_to_vector(vals);
    for(int i = 0; i< l_length(vals); i++) {
        h_insert(new_h, ((Val*)vector[i])->info, ((Val*)vector[i])->size_info, ((Val*)vector[i])->key, ((Val*)vector[i])->size_key);
    }
    l_free_info(&vals);
    free(vector);
    return new_h;
}

// void* h_get_val(void* ht, void* key) {
//     if()

// }

void h_print(void* ht, void (*print)(void*)) {
    Hasht* h = conv(ht);
    for(int i = 0; i< h->size_table; i++) {
        void** vector = l_to_vector(h->table[i]);
        printf("lista %d: ", i);
        for(int j =0; j < l_length(h->table[i]); j++) {
            print(((Val*)vector[j])->info);
        }
        free(vector);
        printf("\n");
    }
 
}
