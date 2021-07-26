#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "stack.h"
#include "queue.h"
#include "hashtable.h"
#include "tester.h"

void free_int(void *val) {
    ;
}

int comparare(void* a, void* b) {
    //0-egalitate
	if((*(int*)a) > (*(int*)b)) 
        return 1;
	if((*(int*)a) < (*(int*)b)) 
        return -1;
	return 0;
}

void afisare(void* info) {
    printf("%d ", *(int*)info);
}

/*
Lista
    Vector (array)
        elementel adiacente in memorie
        indexezi
    Liste simplu inlantuite
    Liste dublu inlantuite

.h -> interfata - cum folosesc 
.c -> sursa / implementarea - cum functioneaza

.h .c -> .o -> .out
         .o
*/

/*
info = 3
00000000|00000000|00000000|00000011
acc = 10000011

info = "mere"
01101101|01100101|01110010|01100101
acc =    11101101
                  10001000
                           11111010
                           10011111
*/

int hashf(void* info, int size, int size_info) {
    char acc = 0;
    for(int i = 0; i < size_info; i++) {
        acc = acc ^ *((char*)info + i) ; 
    }
    return acc % size;
}

// int hashf(void* info, int size, int size_info) {
//     int acc = 0;
//     for(int i = 0; i < size_info; i++) {
//         acc = acc ^ *((int*)info + i) ; 
//     }
//     return acc % size;
// }

int main() {
    void *list   = l_create();
    int a = 3, b = 4, c = 6, d = 8, e = 9;
    
    test1(list, free_int,afisare);
    test2(list, a, b, c, afisare);
    test3(list, a, b, c, d, free_int, afisare);
    test4(list, a, b, c, d, comparare, afisare);
    test5(list, a, free_int);

    return 0;
}