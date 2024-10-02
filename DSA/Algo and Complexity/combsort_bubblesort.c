#include <stdio.h>
#define MAX 10

void bubblesort(int *arr);
void combsort(int *arr);
void print(int *arr);


int main(){
    int arr[] = {8, 4, 1, 56, 3, -44, 23, -6, 28, 0};
    int arr2[]  = {4, -6, 0, 1, 3, -44, 8, 23, 28, 56};


    //sorting algos
    bubblesort(arr);
    // combsort(arr2);
    // printf("%d", (int)(1 / 1.3));


    print(arr);
    return 0;
}

void combsort(int *arr){
    int count = MAX, swapped = 1;
    int gap = count / 1.3;

    while(swapped == 1 || gap >= 1){
        printf("gap: %d\n", gap); //tracker
        swapped = 0; //set flag to false

        for(int x = 0; x + gap < count; x++){
            if(arr[x] > arr[x + gap]){
                //swap
                int temp = arr[x];
                arr[x] = arr[x + gap];
                arr[x + gap] = temp;
                swapped = 1; //set flag true if swapped occured
            }
        }
        gap = gap / 1.3;
    }

}   

void bubblesort(int *arr){
    int count = MAX;

    for(int x = 0; x < count; x++){
        for(int y = 0; y < count - x; y++){
            if(arr[y] > arr[y + 1]){
                //swap
                int temp = arr[y];
                arr[y] = arr[y+1];
                arr[y+1] = temp;
            }
        }
    }

}

void print(int *arr){
    int count = MAX;

    printf("[");
    for(int i = 0; i < count; i++){
        printf("%d", arr[i]);
        if(i < count - 1){
            printf(", ");
        }
    }
    printf("]");
}