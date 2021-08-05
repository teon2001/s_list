#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "hashtable.h"

#define N 1500
#define M 8
 
void print(void* info) {
    printf("%s ", (char*)info);
}

static char* from_prop_to_key(void* prop) {
    char* p = (char*)prop;
    char* aux = strtok(p, " ");
    aux = strtok(NULL, " ");
    return aux;
}

static void free_int(void *val) {
    ;
}
static char* from_prop_to_info(void* prop) {
    char* p = (char*)prop;
    char* aux = strtok(p, " ");
    aux = strtok(NULL, " ");
    aux = strtok(NULL, "\n");
    return aux;
}

static int hashf(void* key, int table_size) {
    char* nume_adresa = (char*)key;
    int s = 0;
    for(long unsigned int i = 0; i < strlen(nume_adresa); i++) {
        s = s + nume_adresa[i];
    }
    return s % table_size;
}




int main() {
    void* h = h_create(M, hashf);
    FILE* inputfile = fopen("./Test0.in", "r");
    char* ptr = malloc(N * sizeof(char));
    char** act_vector = malloc(N * sizeof(char*));
    char** act_vector_copy = malloc(N * sizeof(char*));

    int i = 0;

    while(fgets(ptr, N, inputfile) != NULL) {
        act_vector[i] = strdup(ptr);
        act_vector_copy[i] = strdup(ptr);    
        i++;
    }
    // void* all_vals; 
    // void** vector;
    // int q = 0;
    int nr_lines = i;
    for(int i = 0; i < nr_lines; i++) {
        if(strstr(act_vector[i], "put") != 0) {
            h_insert(h, from_prop_to_key(act_vector[i]), sizeof(char*), from_prop_to_info(act_vector_copy[i]), sizeof(char*));            // all_vals = all_values(h);
            // printf("%p\n", all_vals);
            // vector = l_to_vector(all_vals);
        } else if (strstr(act_vector[i], "print") != 0) {
            h_print(h, print);
        } else if (strstr(act_vector[i], "remove") != 0) {
            // printf("%s\n", act_vector[i]);

            // SEG --> h_delete(h, from_prop_to_key(act_vector[i]), sizeof(char*), free_int);
            
            // h_print(h, print);
            // printf("\n");
            // for(int k = 0; k < l_length(all_vals); k++ ) {
            //     printf("all: %s\n", (char*)vector[k]);
        } 
        printf("\n");
    }
    fclose(inputfile);

}