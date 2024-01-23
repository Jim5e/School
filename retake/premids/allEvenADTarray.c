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
    ptr->elem = (int *) malloc(sizeof(int) * given.count);

    if(ptr != NULL){
        int newCount = 0;
        int r = 0;

        for(int i = 0; i < given.count;i++){
            if(given.elem[i] % 2 == 0){
                ptr->elem[r] = given.elem[i];
                r++;
            }
        }

        ptr->count = r;

        //adjust
        ptr->elem = realloc(ptr->elem, sizeof(int) * ptr->count); 
    }

    return ptr;
}