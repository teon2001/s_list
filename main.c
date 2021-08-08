#include <stdio.h>
#include <stdlib.h>

#include "heap.h"
#include "tester_heap.h"


void print(void* val) {
    printf("%d ", *(int*)val);
}

int comp(void* a, void* b) {
    //0-egalitate
    if( a == NULL) return -1;
    if( b == NULL) return 1;
	if((*(int*)a) > (*(int*)b)) 
        return 1;
	if((*(int*)a) < (*(int*)b)) 
        return -1;
	return 0;
}

void free_int(void *val) {
    ;
}
 
// void test_list() {
//     test_insert();
//     test_remove();
//     test_delete_empty();
//     test_contains_length();
//     test_concat();
// }
// void test_hash() {
//     test_insert();
//     test_delete();
//     test_exist_resize();
// }

void test_heap() {
    test_insert();
    test_remove();
}

int main() {
    test_heap();


    return 0;
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

// ---varianta cu int---
//  int hashf(void* info, int size, int size_info) {
//     int acc = 0;
//     for(int i = 0; i < size_info; i++) {
//         acc = acc ^ *((int*)info + i) ; 
//     }
//     return acc % size;
// }


/*
#include "list.h"
#include "hashtable.h"
#include "tester_hash.h"
#include "tester_list.h"




int comp(void* a, void* b) {
    //0-egalitate
	if((*(int*)a) > (*(int*)b)) 
        return 1;
	if((*(int*)a) < (*(int*)b)) 
        return -1;
	return 0;
}

int hashf(void* info, int size_table, int size_info) {
    char acc = 0;
    for(int i = 0; i < size_info; i++) {
        acc = acc ^ *((char*)info + i) ; 
    }
    return acc % size_table;
}

static int hashf(void* key, int table_size) {
    char* prop = (char*)key;
    int s = 0;
    char* nume_adresa = from_prop_to_key(prop);
    for(int i = 0; i < strlen(nume_adresa); i++) {
        s = s + nume_adresa[i];
    }
    return s % table_size;
}

*/