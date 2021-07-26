#include "list.h"
#include "tester.h"
#include <stdio.h>

void test1(void *list, void (*free_info)(void *), void (*afisare)(void*)) {
    l_insert_last(&list, NULL);
    l_insert_first(&list, NULL);
    l_delete(&list, 4, free_info);
    l_print(list, afisare);
}

void test2(void *list, int a, int b, int c, void (*afisare)(void*)) {
    l_insert_first(&list, &a);
    l_insert_first(&list, &b);
    l_insert_last(&list, &c);
    l_print(list, afisare);
    void* w = l_remove(&list, (l_length(list)-1));
    printf("%d\n", *(int*)w);
    l_print(list, afisare);
}

void test3(void* list, int a, int b, int c, int d, void (*free_info)(void *), void (*afisare)(void*)) {
    l_insert_first(&list, &a);
    l_insert_first(&list, &b);
    l_insert_last(&list, &c);
    l_insert_first(&list, &d);
    l_print(list, afisare);
    for(int i = 0; i < 4; i++){
        l_delete(&list, l_length(list)-1, free_info);
    }    
    l_print(list, afisare);
}

void test4(void * list, int a, int b, int c, int d, int (*comp)(void *, void*), void (*afisare)(void*)) {
    l_insert_first(&list, &a);
    l_insert_first(&list, &b);
    l_insert_last(&list, &c);
    l_insert_first(&list, &d);
    l_print(list, afisare);
    printf("cont-> %d\n", l_contains(list, &a, comp));
    printf("leng-> %d\n", l_length(list));
}

void test5(void* list, int a, void (*free_info)(void *)) {
    l_insert_first(&list, &a);
    l_delete(&list, 0, free_info);
    l_delete(&list, 0, free_info);
}