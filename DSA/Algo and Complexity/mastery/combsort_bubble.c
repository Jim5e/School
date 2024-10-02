#include <stdio.h>
#define MAX 10


void print(int *arr, int count);
void bubble(int *arr);

int main(){
    int arr[] = {8, 4, 1, 56, 3, -44, 23, -6, 28, 0};


    bubble(arr);
    print(arr, MAX);
    return 0;
}

void bubble(int *arr){
    int count = MAX;
    int c = 0;

    for(int y = 0; y < count; y++){
        for(int x = 0; x < count - y;  x++){
            if(arr[x] > arr[x + 1]){
                int temp = arr[x];
                arr[x] = arr[x + 1];
                arr[x + 1] = temp;
            }
            c++;
        }
    }

    printf("comparisons: %d\n", c);
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