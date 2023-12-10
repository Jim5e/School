#include <stdio.h>
#include <stdlib.h>
#define MAX 15

typedef struct {
    int array[MAX];
    int last;

}heap;

void insert(heap *heap, int value);
int deleteMin(heap *heap);
void print(heap H);
int get_parent(int child);
int get_smallChild(heap heap, int parentNdx);
heap heapsort(heap *heap, int arr[], int count);
heap initHeap(heap *heap);

int main(){
    int unsorted[] = {7,5,4,3,6,2,1,8,1};
    int unsorted_count = sizeof(unsorted) / 4;
    heap J = initHeap(&J);


//------------------------------//
    
    heap catcher = heapsort(&J, unsorted, unsorted_count);
    print(catcher);

    return 0;
}

int get_parent(int child){
    int val;
    return val = ((child - 1) / 2);
}

heap initHeap(heap *heap){
    heap->last = -1;

    return *heap;
}

void insert(heap *heap, int value){
    //place the value at last + 1
    heap->last += 1;
    heap->array[heap->last] = value;
    //if child < parent, then swap
    int childNdx = heap->last;
    int parentNdx = get_parent(childNdx);

    while(heap->array[childNdx] < heap->array[parentNdx]){
            int temp = heap->array[parentNdx];
            heap->array[parentNdx] = heap->array[childNdx];
            heap->array[childNdx] = temp;

            childNdx = parentNdx;
            parentNdx = get_parent(childNdx);
        
    }
}

int deleteMin(heap *heap){
    if(heap->last == -1){
        printf("The tree is empty. Cannot delete");
        return -999;
    }

    //swap root and last, decrease last.
    int rootNdx = 0;
    int temp = heap->array[rootNdx];
    heap->array[rootNdx] = heap->array[heap->last];
    heap->array[heap->last] = temp;
    heap->last--;

    //if parent is smaller than smalelst_Child, swap.
    int parentNdx = rootNdx;
    int smallNdx = get_smallChild(*heap, rootNdx);

    while(smallNdx != -1 && heap->array[smallNdx] < heap->array[parentNdx]){
        int temp = heap->array[parentNdx];
        heap->array[parentNdx] = heap->array[smallNdx];
        heap->array[smallNdx] = temp;            

        parentNdx = smallNdx;
        smallNdx = get_smallChild(*heap, parentNdx);
    }

    return temp;
}

heap heapsort(heap *A, int arr[], int count){
    //transfer
    for(int i = 0; i < count; i++){
        insert(A, arr[i]);
    }

    //shallow copy values of A to heap dupe
    heap dupe = *A;

    //delete everything in dupe to sort
    int orig_last = dupe.last;
    for(;dupe.last != -1;){
        deleteMin(&dupe);
    }

    //reset last
    dupe.last = orig_last;

    return dupe;
}


int get_smallChild(heap heap, int parentNdx){
    int left_childNdx = ((parentNdx * 2) + 1);
    int right_childNdx = ((parentNdx * 2) + 2);
    int smallest_childNdx;

    if(left_childNdx > heap.last && right_childNdx > heap.last) { //case: no children
        return -1;
    } else if(right_childNdx > heap.last || heap.array[left_childNdx] < heap.array[right_childNdx]) {
        //case: no right child or left child is smaller
        smallest_childNdx = left_childNdx;
    } else {
        //case: right child is smaller or only right child exists
        smallest_childNdx = right_childNdx;
    }

    return smallest_childNdx;
}


void print(heap H){

    //print
    for(int i = 0; i <= H.last; i++){
        printf("%d ", H.array[i]);
    }

    printf("\nlast is: %d\n", H.last);

}