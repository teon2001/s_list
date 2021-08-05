#include <stdio.h>
#include <assert.h>

#include "list.h"
#include "tester_list.h"

static void print(void* info) {
    printf("%d ", *(int*)info);
}

static void free_int(void *val) {
    ;
}

static int comp(void* a, void* b) {
    //0-egalitate
	if((*(int*)a) > (*(int*)b)) 
        return 1;
	if((*(int*)a) < (*(int*)b)) 
        return -1;
	return 0;
}

void test_insert_NULL() {
    void *list = l_create();
    
    assert(l_insert_first(&list1, &NULL) == 0);
    l_free(&list, free_int);
}

void test_insert_list_first() {
    void *list = l_create();
    int a = 1, b = 2;

    assert(l_insert_first(&list, &a) == 0);
    assert(l_insert_first(&list, &b) == 0);

    l_free(&list, free_int)
}

void test_insert_last() {
    void *list = l_create();
    int a = 1, b = 2;

    assert(l_insert_last(&list, &a) == 0);
    assert(l_insert_last(&list, &b) == 0);

    l_free(&list, free_int)
}

void test_insert() {
    test_insert_NULL();
    test_insert_list_last();
    test_insert_list_first();
}

void test_remove_node() {
    void *list = l_create();
    int a = 1, b = 2, c = 3;

    l_insert_first(&list, &a);
    l_insert_first(&list, &b);    
    l_insert_last(&list, &c);

    void* w = l_remove(&list, 2);
    assert(w != NULL);
    l_free(&list, free_int);
}

void test_remove_info() {
    void *list = l_create();
    int a = 1, b = 2, c = 3;

    l_insert_first(&list, &a);
    l_insert_first(&list, &b);    
    l_insert_last(&list, &c);

    void* w = l_remove(&list, &b, comp);
    assert(w != NULL);
    l_free(&list, free_int);
}

void test_remove_NULL() {
    void *list = l_create();
   
    void* w = l_remove(&list, 6);
    assert(w == NULL);
    l_free(&list, free_int);
}

void test_remove() {
    test_remove_NULL();
    test_remove_val();
    test_remove_info();
}

void test_delete_NULL() {
    void *list = l_create();
   
    assert(l_delete(&list, 3, free_int) == 1);
    l_free(&list, free_int);
}

void test_delete_node() {
    void *list = l_create();
    int a = 1, b = 2, c = 3, d = 4;

    assert(l_insert_first(&list, &a) == 0);
    assert(l_insert_first(&list, &b) == 0);
    assert(l_insert_first(&list, &c) == 0);
    assert(l_insert_first(&list, &d) == 0);

    assert(l_delete(&list, 3, free_int) == 0);
    assert(l_delete(&list, 5, free_int) == 1);

    l_free(&list, free_int);   
}

void test_delete() {
   test_delete_NULL();
   test_delete_node();
}

void test_empty() {
    void *list = l_create();
    int a = 1, b = 2, c = 3;

    assert(l_empty(list) == 1)

    l_insert_first(&list, &a);
    l_insert_first(&list, &b);    
    l_insert_last(&list, &c);

    assert(l_empty(list) == 0)
    
    l_free(&list, free_int);   
}

void test_contains_length() {
    void *list = l_create();
    int a = 1, b = 2, c = 3, d = 4;
    
    assert(l_contains(list, &d, comp) == 0);
    assert(l_length(list) == 0);
    
    assert(l_insert_first(&list, &a) == 0);
    assert(l_insert_last(&list, &b) == 0);
    assert(l_insert_first(&list, &c) == 0);
    assert(l_insert_first(&list, &d) == 0);

    assert(l_contains(list, &d, comp) == 1);
    assert(l_length(list) == 4);
    l_free(&list, free_int);
}

static void test_concat_NULL_NULL() {
    void *list1 = l_create();
    void *list2 = l_create();
    void *list3 = l_create();
   
    assert(l_concat(&list3, list1, list2) == 0);

    l_free(&list1, free_int);
    l_free(&list2, free_int);
    l_free(&list3, free_int);
}

static void test_concat_list_NULL() {
    void *list1 = l_create();
    void *list2 = l_create();
    void *list3 = l_create();
    int a = 1, b = 2, c = 3, d = 4;
    
    assert(l_insert_first(&list1, &a) == 0);
    assert(l_insert_last(&list1, &b) == 0);
    assert(l_insert_first(&list1, &c) == 0);
    assert(l_insert_first(&list1, &d) == 0);
    assert(l_concat(&list3, list1, list2) == 0);

    l_free(&list1, free_int);
    l_free(&list2, free_int);
    l_free(&list3, free_int);
}
static void test_concat_NULL_list() {
    void *list1 = l_create();
    void *list2 = l_create();
    void *list3 = l_create();
    int a = 1, b = 2, c = 3, d = 4;
    
    assert(l_insert_first(&list2, &a) == 0);
    assert(l_insert_last(&list2, &b) == 0);
    assert(l_insert_first(&list2, &c) == 0);
    assert(l_insert_first(&list2, &d) == 0);
    assert(l_concat(&list3, list1, list2) == 0);

    l_free(&list1, free_int);
    l_free(&list2, free_int);
    l_free(&list3, free_int);
}
static void test_concat_list_list() {
    void *list1 = l_create();
    void *list2 = l_create();
    void *list3 = l_create();
    int a = 1, b = 2, c = 3, d = 4;
    
    assert(l_insert_first(&list1, &a) == 0);
    assert(l_insert_last(&list1, &b) == 0);
    assert(l_insert_first(&list2, &c) == 0);
    assert(l_insert_first(&list2, &d) == 0);
    assert(l_concat(&list3, list1, list2) == 0);

    assert(l_include(list3, list1, comp) == 0);

    l_free(&list1, free_int);
    l_free(&list2, free_int);
    l_free(&list3, free_int);
}

void test_concat() {
    test_concat_list_list();
    test_concat_NULL_list();
    test_concat_list_NULL();
    test_concat_NULL_NULL();
}