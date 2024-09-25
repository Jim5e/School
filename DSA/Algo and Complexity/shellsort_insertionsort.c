#include <stdio.h>
#define MAX 12

void insertionsort(int *arr);
void shellsort(int *arr);

void print(int *arr);


int main(){
    int arr[] = {62,	83,	18,	53,	7	,17,	95	,86,	47,	69,	25, 28}; //change max to 12
    // int arr2[]  = {23, 1, 10, 5, 2};


    //sorting algos
    // insertionsort(arr2);
    shellsort(arr);


    print(arr);
    return 0;
}
void shellsort(int *arr){ //insertion + shifting
    //create gap
    int count = MAX;
    int c = 0;

    // {62,	83,	18,	53,	7 ,17, 95 ,86, 47, 69, 25, 28}
    for(int gap = count / 2; gap > 0; gap = gap / 2){
        for(int x = gap; x < count;x++){
            int temp = arr[x];
            int i = x;
                for(; i >= gap && arr[i - gap] > temp; i = i - gap){ //lcoating place to insert
                    c++;
                    //shift rights
                    arr[i] = arr[i - gap];
                }
            arr[i] = temp;
        }
    }

    printf("comparisons: %d\n", c);
}

// void shellsort(int *arr){ //via swapping
//     //create gap
//     int count = MAX;
//     int c = 0;

//     for(int gap = count / 2; gap >= 1; gap = gap/2){
//         for(int x = 0;x < gap;x++){
//             while(x + gap < count && x >= 0){
//                 if(arr[x] > arr[x + gap]){
//                     c++;
//                     //swap
//                     int temp = arr[x];
//                     arr[x] = arr[x + gap];
//                     arr[x + gap] = temp;
//                     x = x - gap; 
//                 }else{
//                     x = x + gap;
//                 }
//             }
//         }
//     }

//     printf("comparisons: %d\n", c);
// }

void insertionsort(int *arr){
    int count = MAX;

    for(int i = 1; i < count; i++){
        int temp = arr[i];
        int x = i - 1;

        for(; x >= 0 && arr[x] > temp; x--){
            arr[x+1] = arr[x];
        }

        arr[x + 1] = temp;
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