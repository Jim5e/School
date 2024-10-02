#include <stdio.h>
#define MAX 10

void print(int *arr, int count);
void selection(int *arr);


int main(){
    int arr[] = {8, 4, 1, 56, 3, -44, 23, -6, 28, 0};

    selection(arr);
    print(arr, MAX);

    return 0;
}

void selection(int *arr){ //locate the smallest
    int count = MAX;

    for(int x = 0; x < count; x++){
        int smallestndx = x;
        int y;
        for(y = x + 1; y < count; y++){ //locate smallest then replace x
            if(arr[y] < arr[smallestndx]){
                smallestndx = y;
            }
        }

        //swap
        int temp = arr[x];
        arr[x] = arr[smallestndx];
        arr[smallestndx] = temp;
    }
}

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