#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "hashtable.h"

#define N 1500
#define M 8

//compar cheile, adica cele de felul www.google.com
int comp(void *htentry1, void *htentry2) {
    //0 = egalitate
    printf("lala\n");
    if(strcmp((char*)htentry1, (char*)htentry2) == 0)
        return 0;
    return 1;
}

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
    // ;
    // free(val);
}

static char* from_prop_to_info(void* prop) {
    char* p = (char*)prop;
    char* aux = strtok(p, " ");
    aux = strtok(NULL, " ");
    aux = strtok(NULL, "\n");
    return aux;
}

int hashf(void* key, int table_size) {
    char* nume_adresa = (char*)key;
    int s = 0;
    for(long unsigned int i = 0; i < strlen(nume_adresa); i++) {
        s = s + nume_adresa[i];
    }
    if(nume_adresa[strlen(nume_adresa)-1] == '\n')
        s = s - 10;
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

    int nr_lines = i;
    void* list = l_create();

    for(int i = 0; i < nr_lines; i++) {
        if(strstr(act_vector[i], "put") != 0) {
            h_insert(h, from_prop_to_key(act_vector[i]), sizeof(char*), from_prop_to_info(act_vector_copy[i]), sizeof(char*), &list);
        }
        if (strstr(act_vector[i], "print") != 0) {
            h_print(h, print);
        }
        if (strstr(act_vector[i], "remove") != 0) {
            h_delete(h, from_prop_to_key(act_vector[i]), sizeof(char*), free_int);
        } 
        if (strstr(act_vector[i], "get") != 0) {
            char* aux = from_prop_to_key(act_vector[i]);
            void *ip = h_get_val(h, aux, sizeof(char*), list);
            printf("adresa IP pentru %s este: %s\n", aux, (char*)ip);
        }
        if(strstr(act_vector[i], "find") != 0) {
            char* aux = from_prop_to_key(act_vector[i]);
            printf("\t pentru adresa %s\n", aux);
            if(h_exist(h, aux, sizeof(char*), comp) == 1) {
                printf("TRUE!!\n");
            } else printf("FALSE!!\n");
        }
        if(strstr(act_vector[i], "print_bucket") != 0) {
            char* nr = from_prop_to_key(act_vector_copy[i]);
            int idx = atoi(nr);
            h_print_list(h, idx, print);
        }
    }


    fclose(inputfile);

}