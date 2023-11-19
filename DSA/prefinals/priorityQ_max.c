#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

typedef struct{
    int array[MAX];
    int last;

}heap; //MAX HEAP

heap initHeap(heap *H);
void insert(heap *H, int value);
int getParent(int childNdx);
int deleteMax(heap *H);
int getBiggest_C(heap H, int parentNdx);
void isMember(heap H, int value);
void heapsort_insertion(heap *H, int arr[], int size);
void heapsort_heapify((int arr[], int size));
heap heapify(int arr[], int size, int index);
void print(heap A);


int main(){
    int test[] = {5,10,3,11,4,7,8,13};
    int test_size = sizeof(test) /4;
    heap H = initHeap(&H); //MAX HEAP DONT FORGETTTTTTTTTTT

    // insert(&H, 5);
    // insert(&H, 10);
    // insert(&H, 3);
    // insert(&H, 11);
    // insert(&H, 4);
    // insert(&H, 7);
    // insert(&H, 8);
    // insert(&H, 13);
    // print(H);

    // deleteMax(&H);
    // deleteMax(&H);
    // print(H);
    //testing heapsort_insert
    // heapsort_insertion(&H, test, test_size);
    
    //testing heapsort_heapify
    heapsort_heapify(test, test_size);
    return 0;
}

void isMember(heap H, int value){

}

void heapsort_insertion(heap *H, int arr[], int size){
    for(int i = 0; i < size; i++){
        insert(H, arr[i]);
    }
    print(*H);

    int orig = H->last;
    for(;H->last != -1;){
        deleteMax(H);
    }

    H->last = orig;
    print(*H);
}

void heapsort_heapify(int arr[], int size, int index){
    //build a heap using heapify()
    heap A = heapify(arr);
    print(A);


}

void heapify(int arr[], int size){
    //use reductive method. start from H.last, moving to index 0
    //check if parent violates POT, if it does, swap.
    int parentNdx = H->last;
    int biggestNdx = getBiggest_C(*H, parentNdx);

    //conditions: if no child (i.e. -1) then dont bother, we have reached max node (so no parent to compare), then actual comparison: if child > parent, swap.
    while(biggestNdx != -1 && parentNdx < 0 && H->array[biggestNdx] > H->array[parentNdx]){
        int temp = H->array[parentNdx];
        H->array[parentNdx] = H->array[biggestNdx];
        H->array[biggestNdx] = temp;

        parentNdx--;
        biggestNdx = getBiggest_C(*H, parentNdx);
    }

}




int deleteMax(heap *H){
    //swap last and root, and then reduce last by 1
    int rootNdx = 0;
    int rootValue = H->array[rootNdx];
    int temp = H->array[rootNdx];
    H->array[rootNdx] = H->array[H->last];
    H->array[H->last] = temp;
    H->last -= 1;

    //if child > parent, swap
    int parentNdx = rootNdx;
    int biggestNdx = getBiggest_C(*H, parentNdx);

    while(biggestNdx != -1 && H->array[biggestNdx] > H->array[parentNdx]){
        int temp = H->array[parentNdx];
        H->array[parentNdx] = H->array[biggestNdx];
        H->array[biggestNdx] = temp;

        parentNdx = biggestNdx;
        biggestNdx = getBiggest_C(*H, parentNdx);
    }

    return rootValue;
}

int getBiggest_C(heap H, int parentNdx){
    int leftNdx = (parentNdx * 2) + 1;
    int rightNdx = (parentNdx * 2) + 2;
    int biggestNdx = -1;

    //check validity of index and also compare
    if(leftNdx <= H.last && (rightNdx > H.last || H.array[leftNdx] >= H.array[rightNdx])){
        biggestNdx = leftNdx;
    }else if(rightNdx <= H.last){
        biggestNdx = rightNdx;
    }

    return biggestNdx;
}


void insert(heap *H, int value){
    //add to last
    H->last++;
    H->array[H->last] = value;

    //if child > parent, swap
    int childNdx = H->last;
    int parentNdx = getParent(childNdx);

    while(H->array[parentNdx] < H->array[childNdx]){
        //swap if true
        int temp = H->array[parentNdx];
        H->array[parentNdx] = H->array[childNdx];
        H->array[childNdx] = temp;
        
        //repeat until POT is true
        childNdx = parentNdx;
        parentNdx = getParent(childNdx);
    }
}

int getParent(int childNdx){
    int val = 0;
    val = ((childNdx - 1) / 2);
    return val;
}

heap initHeap(heap *H){
    H->last = -1;

    return *H;
}

void print(heap A){
    for(int i = 0 ; i <= A.last; i++){
        printf("%d ", A.array[i]);
    }

    printf("\nLast is: %d\n", A.last);
}