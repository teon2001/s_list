#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include "list.h"

typedef struct node {
    void *info;
    struct node* next;
    struct node* prev;
} Node;

void *l_create() {
    return NULL;
}

static Node *create_node(void *val) {
    Node *node = malloc(sizeof(Node));
    node->info = val;
    node->next = node->prev = node;
    return node;
}

static Node *conv(void *list) {
    return (Node*)list;
}

int l_insert_first(void **list, void *val) {
    if(val == NULL)  
        return -EINVAL;
    Node* nod_nou = create_node(val);
    Node* li = conv(*list);
    if(li == NULL) {
        li = nod_nou;
        nod_nou->prev = nod_nou;
        nod_nou->next = nod_nou;
        *list = li;
        return 0;
    } 

    nod_nou->next = li;
    nod_nou->prev = li->prev;
    li->prev->next = nod_nou;
    li->prev = nod_nou;
    li = nod_nou;

    *list = (void*)li;
    return 0;
}

int l_insert_last(void** list, void* val) {
    if(val == NULL) 
        return -EINVAL;
    Node* li = conv(*list);
    Node* node = create_node(val);
    if(li == NULL) {
        li = node; 
        node->prev = node;
        node->next = node;
        *list = li;
        return 0; 
    } 
    node->prev = li->prev;
    li->prev->next = node;
    node->next = li;
    li->prev = node;
    *list = li;
    return 0;
}

static void free_node(Node *node, void (*free_info)(void *)) {
    free_info(node->info);
    free(node);
}

int l_length(void *list) {
    if(list  == NULL) 
        return 0;
    Node* li = conv(list);
    if(li == li->next) 
        return 1;

    int contor = 1;
    Node *iter = li->next;
   
    while(iter != li) {
        contor++;
        iter = iter->next;
    }
    return contor;
}

static Node *aux(void **list, int idx) {
    Node* li = conv(*list);
    int contor = 0;

    if(idx == 0) {
        Node *i = li;
        if(l_length(*list) == 1) {
            *list = NULL;
            return li;
        }

        li->prev->next = li->next;
        li->next->prev = li->prev;
        
        *list = li->next;
        return i;
    }
    for(Node *iter1 = li, *iter2 = li->next; iter2 != li; iter1 = iter1->next, iter2 = iter2->next) {
        contor++;
        if(contor == idx) {
            Node *j = iter2;
            if(iter2->next == li) {
                iter1->next = li;
                li->prev = iter1;
            } else {
                iter1->next = iter2->next;
                iter2->next->prev = iter1;
            }
            return j;
        }
    }
}

int l_delete(void **list, int idx, void (*free_info)(void *)) {
    if(idx >= l_length(*list)) 
        return 1;
    Node *i = aux(list, idx);
    free_node(i, free_info);
    return 0; 
}

void *l_remove(void **list, int idx) {
    if(idx >= l_length(*list)) 
        return  NULL;
    Node* i =  aux(list, idx);
    void* j = i->info;
    free(i);
    return j;
}

int l_contains(void *list, void *val, int (*comp)(void *, void*)) {
    Node* li = conv(list);
    if(li->info == val) return 1;
    Node* i = li->next;
    for(; i != li; i = i->next) {
        if(comp(i->info, val) == 0) {
            return 1;
        }
    }
    return 0;
}

void l_print(void *list,  void(*print)(void*)){
    Node *li = conv(list);
    if(l_length(list) == 0)
        return;
    if(l_length(list) == 1) {
        print(li->info);
        printf("\n");
        return;
    }
    Node* t = li->next;
    print(li->info);
    while(t != li) {
        print(t->info);
        t = t->next;
    }
    printf("\n");
}

void l_free(void **list, void (*free_info)(void *)) {
    Node* li= conv(list);
    Node* i = li->next;
    while(i != li) {
        Node* rm = li;
        li = li->next;
        free_node(rm, free_info);
    } 
    free_node(li, free_info);
    list = NULL;
}

int l_empty(void *list) {
    return list == NULL;
}

void* get_info(void* node) {
    Node* n = conv(node);
    return n->info;
}

void** l_vector(void* list) {
    void** vector = malloc(l_length(list) * sizeof(void*));
    Node* li = conv(list);
    int i = 1;
    if(li == NULL) {
        return vector;
    }
    vector[0] = li->info;
    for(Node* iter = li->next; iter != li; iter = iter->next)
        vector[i++] = iter->info;
    return vector;
}  

//CONCATENARE EFICIENTA 
int l_concat(void** list1, void** list2) {
    Node* li1 = conv(*list1);
    Node* li2 = conv(list2);
    
    if(li1 == NULL) {
        li1 = li2;
        *list1 = li1;
        return 0;
    }
    if(li2 == NULL) {
        *list1 = li1;
        return 0;
    }
    Node* tail1 = li1->prev;
    Node* tail2 = li2->prev;
    tail1->next = li2;
    li2->prev = tail1;
    tail2->next = li1;
    li1->prev = tail2;
    list2 = NULL;
    return 0;
}

void *l_remove_info(void **list, void *val, int (*comp)(void*, void*)) {
    if(list == NULL) {
        return NULL;
    }
    Node* li = conv(*list);
    int contor = 0;
    if(comp(li->info,  val) == 0) {
        
        void* s = li->info;
        *list = li->next;
        li->next = NULL;
        free(li);
        return s;
    }
    for(Node *iter2 = li->next; iter2 != li; iter2 = iter2->next) {
        if(comp(iter2->info, val) == 0) {
            void *w = iter2->info;
            iter2->prev = iter2->next;
            iter2->next->prev = iter2->prev;
            free(iter2);
            return w;
        }
    }
    return NULL;
}