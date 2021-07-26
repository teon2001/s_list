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
    Info *info;
    struct node* next;
    struct node* prev;
} Node;

void *l_create() {
    return NULL;
}

static Node *create_node(void *val) {
    Node *node = malloc(sizeof(Node));
    node->info = calloc(1, sizeof(Info));
    node->info->inform = val;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

static Node *conv(void *list) {
    return (Node*)list;
}

int l_insert_first(void **list, void *val) {
    if(val == NULL)  
        return -EKEYREJECTED;;
    Node* nod_nou = create_node(val);
    Node* li = conv(*list);
    if(li == NULL) {
        li = nod_nou;
        *list = (void*)li;
        return 0;
    }
    nod_nou->next = li;
    li->prev = nod_nou;
    li = nod_nou;
    *list = (void*)li;
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
    node->prev = t;
    *list = li;
    return 0;
}

static void free_node(Node *list, void (*free_info)(void *)) {
    free_info(list->info->inform);
    free(list);
}

int l_length(void *list) {
    Node* li = conv(list);
    int contor = 0;
    while(li != NULL) {
        contor++;
        li = li->next;
    }
    return contor;
}

void l_delete(void **list, int idx, void (*free_info)(void *)) {
    if(idx >= l_length(*list)) 
        return;
    Node* li = conv(*list);
    int contor = 0;
    if(idx == 0) {
        li->next = NULL;
        *list = li->next;
        free_node(li, free_info);
        return;
    }
    for(Node *t = li, *r = li->next; r != NULL; t = t->next, r = r->next) {
        contor++;
        if(contor == idx) {
            if(r->next == NULL) {
                t->next = NULL;
            } else {
                t->next = r->next;
                r->next->prev = t;
            }
            free_node(r, free_info);
            return;
        }
    }
}

void *l_remove(void **list, int idx) {
    if(list == NULL) 
        return NULL;
    Node* li = conv(*list);
    int contor = 0;
    if(idx == 0) {
        void *s = li->info->inform;
        li->next->prev = NULL;
        *list = li->next;
        free(li);
        return s;
    }

    for(Node *t = li, *r = li->next; r != NULL; t = t->next, r = r->next) {
        contor++;
        if(contor == idx) {
            Node* x = r->info->inform;
            if(r->next == NULL) {
                t->next = NULL;
            } else {
                t->next = r->next;
                r->next->prev = t;
            }
            free(r);
            return x;
        }
    }
}

int l_contains(void *list, void *val, int (*comp)(void *, void*)) {
    Node* li = conv(list);
    for(; li != NULL; li = li->next) {
        if(comp(li->info, val) == 0) {
            return 1;
        }
    }
    return 0;
}

void l_print(void *list,  void(*afisare)(void*)){
    Node *li = conv(list);
    Node* t = li;
    while(t != NULL) {
        printf("%d ", *(int*)t->info->inform);
        t = t->next;
    }
    printf("\n");
}

void l_free(void **list, void (*free_info)(void *)) {
    Node* li= conv(list);
    while(li != NULL) {
        Node* stersul = li;
        li = li->next;
        free_node(stersul, free_info);
    }
    list = NULL;
}

int l_empty(void *list) {
    return list == NULL;
}