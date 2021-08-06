#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Val{
    void* nume_adresa; // numele(key), www.google.com
    int size_nume_adresa;
    void* ip_adresa; // adresa IP, 8.8.8.8
    int size_ip_adresa;
    int key_hash; // index hash
} HtEntry;

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

static HtEntry* create_node(void *nume_adresa, int size_nume_adresa, void* ip_adresa, int size_ip_adresa, int key_hash) {
    HtEntry* cel = malloc(sizeof(HtEntry));
    cel->nume_adresa = nume_adresa;
    cel->size_nume_adresa = size_nume_adresa;
    cel->ip_adresa = ip_adresa;
    cel->size_ip_adresa = size_ip_adresa;
    cel->key_hash = key_hash;
    return cel;
}

int h_insert(void* ht, void *nume_adresa, int size_nume_adresa, void* ip_adresa, int size_ip_adresa, void** list) {
    // *list = l_create();
    Hasht* h = conv(ht);
    int idx = h->hashf(nume_adresa, h->size_table);
    HtEntry* cel = create_node(nume_adresa, size_nume_adresa, ip_adresa, size_ip_adresa, idx);
    int err = l_insert_first(list, cel);
    if(err != 0) return 1;
    return l_insert_first(&h->table[idx], cel);
}

//compar cheile, adica cele de felul www.google.com
static int comp_HtEntry(void *htentry1, void *htentry2) {
    //0 = egalitate
    // if(htentry1 == NULL || htentry2 == NULL) return 1;

    if(((HtEntry*)htentry1)->size_nume_adresa != ((HtEntry*)htentry2)->size_nume_adresa) return 1;
    return memcmp(((HtEntry*)htentry1)->nume_adresa, ((HtEntry*)htentry2)->nume_adresa, ((HtEntry*)htentry2)->size_nume_adresa);
}

static void free_htentry_cel(HtEntry* i, void (*free_info)(void *)) {
    free_info(i->nume_adresa);
    free_info(i->ip_adresa);
    free(i);
}

// static void afisare(void* info) {
//     printf("%d ", *(int*)((Val*)info)->info);
// }

int h_exist(void *ht, void *nume_adresa, int size_nume_adresa, int (*comp)(void*, void*)) {
    // 1 - exista in hasht
    // 0 - nu exista
    Hasht* h = conv(ht);
    int idx = h->hashf(nume_adresa, h->size_table);
    // printf("indexul: %d\n\n", idx);

    HtEntry wrapper;
    wrapper.nume_adresa = nume_adresa;
    wrapper.size_nume_adresa = size_nume_adresa;

    return l_contains(h->table[idx], &wrapper, comp_HtEntry);
}

int h_delete(void* ht, void *nume_adresa, int size_nume_adresa, void (*free_info)(void *)) {
    Hasht* h = conv(ht);
    if(nume_adresa == NULL) return 1;

    int idx = h->hashf(nume_adresa, h->size_table);
    HtEntry wrapper;
    wrapper.nume_adresa = nume_adresa;
    wrapper.size_nume_adresa = size_nume_adresa;
    void* i = l_remove_info(&h->table[idx], &wrapper, comp_HtEntry);
    if(i == NULL) 
        return 1;
    free_htentry_cel(i, free_info);
    return 0;
}

void h_free(void *ht, void (*free_info)(void *)) {
    Hasht* h = conv(ht);
    for(int i = 0; i < h->size_table; i++) {
        while(!l_empty(h->table[i])) {
            void* iter = l_remove(&h->table[i], 0);
            if(iter == NULL) break;
            free_htentry_cel(iter, free_info);
        }
    }
    free(h->table);
    free(h);
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

    for(int i = 0; i < h->size_table; i++) {
        if(h->table[i] != NULL) {
            int err = l_concat(&res, h->table[i], NULL);
            if( err != 0 ) return NULL;
        }
    }
    return res;
}

// void* h_resize(void *ht, int new_size, int (*hashf)(void *, int)) {
//     void* new_h = h_create(new_size, hashf);
//     void* vals = all_values(ht);
//     void** vector;
//     vector = l_to_vector(vals);
//     for(int i = 0; i< l_length(vals); i++) {
//         h_insert(new_h, ((HtEntry*)vector[i])->nume_adresa, ((HtEntry*)vector[i])->size_nume_adresa, ((HtEntry*)vector[i])->ip_adresa, ((HtEntry*)vector[i])->size_ip_adresa);
//     }
//     l_free_info(&vals);
//     free(vector);
//     return new_h;
// }

void* h_get_val(void* ht, void* nume_adresa, int size_nume_adresa, void* list) {
    if(h_exist(ht, nume_adresa, size_nume_adresa, comp_HtEntry) == 1) {
        HtEntry wrapper;
        wrapper.nume_adresa = nume_adresa;
        wrapper.size_nume_adresa = size_nume_adresa;
        void* ab = l_return_node(list, &wrapper, comp_HtEntry);
        if(ab == NULL) return NULL;
        return ((HtEntry*)ab)->ip_adresa;
    }
    return NULL;
}

void h_print(void* ht, void (*print)(void*)) {
    Hasht* h = conv(ht);
    for(int i = 0; i< h->size_table; i++) {
        void** vector = l_to_vector(h->table[i]);
        printf("lista %d: ", i);
        for(int j =0; j < l_length(h->table[i]); j++) {
            print(((HtEntry*)vector[j])->nume_adresa);
        }
        free(vector);
        printf("\n");
    }
 
}

void h_print_ip_adresa(void* ht, void (*print)(void*)) {
    Hasht* h = conv(ht);
    for(int i = 0; i< h->size_table; i++) {
        void** vector = l_to_vector(h->table[i]);
        printf("lista %d: ", i);
        for(int j =0; j < l_length(h->table[i]); j++) {
            print(((HtEntry*)vector[j])->ip_adresa);
        }
        free(vector);
        printf("\n");
    }
 
}

void h_print_list(void* ht, int idx, void (*print)(void*)) {
    Hasht* h = conv(ht);
    printf("print_bucket[%d]: ", idx);
    if(idx >= h->size_table) printf("NU AVEM ADRESE AICI!");
    void** vector = l_to_vector(h->table[idx]);
    for(int j =0; j < l_length(h->table[idx]); j++) {
        print(((HtEntry*)vector[j])->nume_adresa);
    }
    free(vector);
    printf("\n");

}

// typedef struct Val{
//     void* key; // numele, www.google.com
//     int size_key;
//     void* info; // adresa IP, 8.8.8.8
//     int size_info;
//     int key_hash; // index hash
// } Val;

// static int comp_info(void* a, void* b) {
//     //0 = egalitate
//     if(((Val*)a)->size_info != ((Val*)b)->size_info) return 1;
//     return memcmp(((Val*)a)->info, ((Val*)b)->info, ((Val*)a)->size_info);
// }

// static int comp(void *a, void *b) {
//     //0 = egalitate
//     if(((Val*)a)->size_info != ((Val*)b)->size_info) return 1;
//     return memcmp(((Val*)a)->info, ((Val*)b)->info, ((Val*)b)->size_info);
// }