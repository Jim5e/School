#include <stdio.h>
#define MAX 11


void print(int *arr, int count);
void insertion(int *arr);
void shell(int *arr);


int main(){
    int arr[] = {62,	83,	18,	53,	7	,17,	95	,86,	47,	69,	25, 28}; //change max to 12



    return 0;
}

vo

void print(int *arr, int count){

    printf("[");
    for(int i = 0; i < count; i++){
        printf("%d", arr[i]);
        if(i < count - 1){
            printf(", ");
        }
    }
    printf("]\n");
}