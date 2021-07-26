#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

typedef struct {
    int index;
    int size_info;
    void* inform;
} Info;

typedef struct node {
    Info* info;
    struct node *next;
} Node;

void *l_create() {
    return NULL;
}

static Node *conv(void *list) {
    return (Node*)list;
}

static void *create_node(void *val) {
    Node *node = malloc(sizeof(Node));
    node->info = calloc(1, sizeof(Info));
    node->info->inform = val;
    node->next = NULL;
    return node;
}

static void *reconv(Node *list) {
    return (void*)list;
}

int l_insert_first(void **list, void *val) {
    if(val == NULL) 
        return -EKEYREJECTED;
    Node* li = conv(*list);
    Node* node = create_node(val);
    node->next = li;
    li = node;
    *list = li;
    return 0;
}

int l_insert_last(void** list, void* val) {
    if(val == NULL) 
        return -EKEYREJECTED;
    Node* li = conv(*list);
    Node* node = create_node(val);
    if(li == NULL) {
        li = node; 
        *list = li;
        return 0; 
    } 

    Node *t = li, *p = li->next;
    while(p != NULL) {
        t = t->next;
        p = p->next;
    }
    node->next = NULL;
    t->next = node;
    *list = li;
    return 0;
}

static void free_node(Node *list, void (*free_info)(void *)) {
    free_info(list->info->inform);
    free(list);
}

void *l_remove(void **list, int idx) {
    if(list == NULL) 
        return NULL;
    Node* li = conv(*list);
    int contor = 0;
    if(idx == 0) {
        void* s = li->info->inform;
        *list = li->next;
        li->next = NULL;
        free(li);
        return s;
    }
    for(Node *t = li, *r = li->next; r != NULL; t = t->next, r = r->next) {
        contor++;
        if(contor == idx) {
            void *w = r->info->inform;
            t->next = r->next;
            r->next = NULL;
            free(r);
            return w;
        }
    }
}

void l_delete(void **list, int idx, void (*free_info)(void *)) {
    if(idx >= l_length(*list)) 
        return;
    Node* li = conv(*list);
    int contor = 0;
    if(idx == 0) {
        *list = li->next;
        free_node(li, free_info);
        return;
    }
    for(Node *t = li, *r = li->next; r != NULL; t = t->next, r = r->next) {
        contor++;
        if(contor == idx) {
            t->next = r->next;
            free_node(r, free_info);
            return;
        }
    }
}

void l_print(void *list, void(*afisare)(void*)) {
    Node *li = conv(list);
    while(li != NULL) {
        afisare(li->info->inform);
        li = li->next;
    }
    printf("\n");
}

int l_contains(void *list, void *val, int (*comp)(void*, void*)) {
    // 1-lista contine val
    // 0-lista nu contine val
    Node* li = conv(list);
    for(; li != NULL; li = li->next) {
        if(comp(li->info->inform, val) == 0) {
            return 1;
        }
    }
    return 0;
}

int l_length(void *list) {
    Node* li = conv(list);
    int contor = 0;
    while( li != NULL) {
        contor++;
        li = li->next;
    }
    return contor;
}

void l_free(void **list, void (*free_info)(void *)) {
    Node* li= conv(*list);
    while(li != NULL) {
        Node* stersul = li;
        li = li->next;
        free_node(stersul, free_info);
    }
    *list = NULL;
}

int l_empty(void *list) {
    return list == NULL;
}

/*
free_list   -> list.h
free_node   -> list.c
free_info   -> studenti.h
free        -> stdlib.h
*/