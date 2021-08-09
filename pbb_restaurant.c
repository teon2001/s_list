/*
Sa consideram ca la un restaurant fast-food o singura persoana pregateste comenzile. 
Cand are mai multe comenzi in asteptare, o pregateste pe cea care va dura cel mai putin.
De exemplu, daca exista 2 comenzi cu timp de pregatire de 5 si 50 de minute, 
va fi pregatita comanda de 5 minute. Daca intre timp apare o comanda care ar dura 15 minute,
dupa ce comanda de 5 minute este incheiata, va fi pregatita comanda de 15 minute.
La sfarsit, va fi pregatita si comanda de 50 de minute.
Ce structura de date modeleaza acest tip de comportament? 
                    ---MINHEAP---
*/

#include <stdio.h>
#include <stdlib.h>

#include "heap.h"
#define MAX 6

void print(void* val) {
    printf("%d ", *(int*)val);
}

void free_int(void *val) {
    ;
}

int comp(void* a, void* b) {
    //0-egalitate
    // printf("O O O O O O \n");
	if( a == NULL) return -1;
    if( b == NULL) return 1;
    if((*(int*)a) > (*(int*)b)) 
        return 1;
	if((*(int*)a) < (*(int*)b)) 
        return -1;
	return 0;
}

/*
           2
    4             3
  67 45          9   
*/

int main() {
    int time[MAX];
    for(int i = 0; i < MAX; i++) {
        scanf("%d", &time[i]);
    }
    Heap* h = heap_create(10, comp); 
    for(int i = 0; i < MAX; i++) {
        heap_insert(h, &time[i]);
    }
    // heap_print(h, print);
    printf("Comenzile sunt gata in ordinea:\n");
    for(int i = 0; i < MAX; i++) {
        void *comanda = heap_remove(h, free_int, comp);
        // heap_print(h, print);
        printf("Comanda de %d minute este gata.\n", *(int*)comanda);
    }
    return 0;
}