#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef struct {
    int elem[MAX];
    int count;
}LIST;

LIST *allEven(LIST given);


int main(){
    LIST values = {{2,1,4,5,1}, 5};

    LIST *catcher = allEven(values);


    return 0;
}

LIST *allEven(LIST given){
    LIST *ptr = (LIST *) malloc (sizeof(LIST));

    if(ptr != NULL){

        for(int i = 0; i < given.count;i++){
            if(given.elem[i] % 2 == 0){
                ptr->elem[ptr->count] = given.elem[i];
                ptr->count++;
            }
        }

    }

    return ptr;
}