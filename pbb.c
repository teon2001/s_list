/*

(), [], {}


()(())

((()

)
)(

())
int i = 0;
while(i >= 0 && s != NULL) {
    daca este p.deschisa i++;
    altfel i--;
}
if(i < 0) return 1;
return 0;


while (s != NULL)
    if i < 0
        return 1;
return 0;

while(s != null) {
daca e p.deschisa "(" ||"["
    push(p.deschisa)
else {
    if (stack_empty(stiva)) return 1;
    pop(stiva);
    }

s=  s->next;}
return stack_empty(stiva);
( 
*/
#include "list.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
//1-ok, 0-gresit
int main() {
    char* a = calloc(30,  sizeof(char));
    scanf("%s", a);
    void* stack = st_create();
    int i = 0;
    while(a[i] != '\0') {
        if(a[i] == '(' || a[i] == '{' || a[i] == '[')
            push(&stack, &a[i]);
        else {
            //printf("a[%d] este PParanteza %c\n", i, *(char*)top(stack));
            if((*(char*)(top(stack)) == '(' && a[i] != ')') ||
             (*(char*)(top(stack)) == '[' && a[i] != ']') || 
             (*(char*)(top(stack)) == '{' && a[i] != '}')) {
                    printf("este: 0\n");
                    return 0;
            }
            else pop(&stack);  
        }
        i++;
    }
    printf("este: %d\n", stack_empty(stack));
    return 0;
}