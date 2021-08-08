#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "heap.h"
#include "tester_heap.h"

static int comp(void* a, void* b) {
    //0-egalitate
    if( a == NULL) return -1;
    if( b == NULL) return 1;

	if((*(int*)a) > (*(int*)b)) 
        return 1;
	if((*(int*)a) < (*(int*)b)) 
        return -1;
	return 0;
}

static void free_int(void *val) {
    ;
}

static void print(void* val) {
    if(val == NULL ) printf("\n");
    printf("%d ", *(int*)val);
}

void test_insert_NULL() {
    Heap* h = heap_create(10, comp);
    assert(heap_insert(h, NULL) == 0);

    heap_free(h, free_int);
}

void test_insert_val() {
    int a = 10, b = 9, c = 56, d = 4, e = 1;
    Heap* h = heap_create(10, comp);
    assert(heap_insert(h, &a) == 0);
    assert(heap_insert(h, &b) == 0);
    assert(heap_insert(h, &c) == 0);
    assert(heap_insert(h, &d) == 0);
    assert(heap_insert(h, &e) == 0);
    
    heap_free(h, free_int);    
}

void test_insert() {
    test_insert_NULL();
    test_insert_val();
}

void test_remove_NULL() {
    Heap* h = heap_create(10, comp);
    void *i = heap_remove(h, free_int);
    assert(i == NULL);
    heap_free(h, free_int);   
}

void test_remove_s() {
    int a = 10, b = 9, c = 56, d = 4, e = 1;
    Heap* h = heap_create(10, comp);
    assert(heap_insert(h, &a) == 0);
    void *i = heap_remove(h, free_int);
    assert(i != NULL);
    heap_free(h, free_int);   
}

void test_remove_m() {
    int a = 10, b = 9, c = 56;
    Heap* h = heap_create(10, comp);
    assert(heap_insert(h, &a) == 0);
    assert(heap_insert(h, &b) == 0);
    assert(heap_insert(h, &c) == 0);
    void *i = heap_remove(h, free_int);
    assert(i != NULL);

    void *ii = heap_remove(h, free_int);
    assert(ii != NULL);

    heap_free(h, free_int);   
}

void test_remove() {
    test_remove_NULL();
    test_remove_s();
    test_remove_m();
}