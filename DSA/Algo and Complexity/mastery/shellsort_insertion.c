#include <stdio.h>
#define MAX 12


void print(int *arr, int count);
void insertion(int *arr);
void shell(int *arr);


int main(){
    int arr[] = {62, 83, 18, 53, 7, 17, 95, 86, 47, 69,	25, 28}; //change max to 12

    // insertion(arr);
    shell(arr);
    print(arr, MAX);

    return 0;
}

void shell(int *arr){
    int count = MAX;
    int c = 0;
    
    for(int gap = count / 2; gap >= 1; gap = gap / 2){
        printf("gap: %d\n", gap);
        for(int x = gap; x < count; x += gap){ //equivalent to starting at index 1 of a insertion sort
            int temp = arr[x];
            int goingback;

            for(goingback = x - gap; goingback >= 0 && temp < arr[goingback]; goingback = goingback - gap){
                arr[goingback + gap] = arr[goingback];
                c++;
            }

            arr[goingback + gap] = temp;
        }

    }
    printf("# of comparison</stdio.h>s: %d\n", c);
}

void insertion(int *arr){
    int count = MAX;
    int c = 0;

    for(int x = 1; x < count;x++){
        int temp = arr[x];
        int goingback;

        for(goingback = x - 1; goingback >= 0 && temp < arr[goingback]; goingback--){
            arr[goingback + 1] = arr[goingback];
            c++;
        }

        arr[goingback + 1] = temp;
    }

    printf("# of comparisons: %d\n", c);
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