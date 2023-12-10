#include <stdio.h>
#include <stdlib.h>
#define MAX 10


typedef struct{
    int array[MAX];
    int last;

}heap;

typedef struct{
    int array[MAX];
    int count;

}arrayList;

void initHeap(heap *A);
void insertElement(heap *A, int value);
void deleteMin(heap *A);
int get_parent(int child);
void printMinHeap(heap A);
int isMember(heap A, int value);
int get_smallestC(heap A, int parent);
void heapsort(heap *A, arrayList samples);


int main(){
    heap MAIN;
    initHeap(&MAIN);

    //values'
    arrayList samples = {{2,5,1,8,4,9,38,75,3}, 9};

    //operations
    // insertElement(&MAIN, 2);
    // insertElement(&MAIN, 5);
    // insertElement(&MAIN, 1);
    // insertElement(&MAIN, 8);
    // insertElement(&MAIN, 4);
    // insertElement(&MAIN, 9);
    // insertElement(&MAIN, 38);
    // insertElement(&MAIN, 75);
    // insertElement(&MAIN, 3);

    // deleteMin(&MAIN);
    // deleteMin(&MAIN);
    // deleteMin(&MAIN);
    // deleteMin(&MAIN);
    // deleteMin(&MAIN);
    // deleteMin(&MAIN);
    // deleteMin(&MAIN);
    // deleteMin(&MAIN);
    // deleteMin(&MAIN);
    // MAIN.last = 8;

    //heapsort heapify method
    heapsort(&MAIN, samples);

    printMinHeap(MAIN);
    return 0;
}

void insertElement(heap *A, int value){
    if(A->last >= MAX){
    printf("Heap is full. Unable to insert");

    }else{
        if(!isMember(*A, value)){
            A->last++;
            A->array[A->last] = value;

            //if parent > child, swap
            int childNdx = A->last;
            int parentNdx = get_parent(childNdx);

            while(A->array[childNdx] < A->array[parentNdx]){
                int temp = A->array[parentNdx];
                A->array[parentNdx] = A->array[childNdx];
                A->array[childNdx] = temp;

                childNdx = parentNdx;
                parentNdx = get_parent(childNdx);
            }            
        }else{
            printf("Cannot insert Duplicate value. %d, already exists.\n", value);
        }
    }
}

void deleteMin(heap *A){
    if(A->last == -1){
        printf("Heap is empty. nothing to delete");
    }else{
            //swap root and last
            int rootNdx = 0;
            int temp = A->array[rootNdx];
            A->array[rootNdx] = A->array[A->last];
            A->array[A->last] = temp;
            A->last--;

            //if child > parent, swap
            int parentNdx = rootNdx;
            int smallestChildNdx = get_smallestC(*A, parentNdx);

            while(smallestChildNdx != -1 && A->array[smallestChildNdx] < A->array[parentNdx]){
                //swap parent with child, loop until pot rule is satisfied
                int temp = A->array[parentNdx];
                A->array[parentNdx] = A->array[smallestChildNdx];
                A->array[smallestChildNdx] = temp;

                parentNdx = smallestChildNdx;
                smallestChildNdx = get_smallestC(*A, parentNdx);
            }

        }
    
}

void heapsort(heap *A, arrayList samples){
    //create a new heap with values from heapify, i.e. to "heapify" an array.
    A = heapify(samples);
}

heap *heapify(arrayList samples){
    //create new heap
    heap *genesis = (heap *) malloc (sizeof(heap));
    initHeap(genesis);

    //transfer items from samples to newly made heap
    for(int i = 0; i <= samples.count; i++){
        genesis->array[i] = samples.array[i];
        genesis->last++;
    } 

    //trickle down  sorting effect like a deleteMin(). Sorting begins at lowest level parent
    int lowestParentNdx = genesis->last;

    return genesis;
}
int get_smallestC(heap A, int parent){
    int leftC_Ndx = ((parent * 2) + 1);
    int rightC_Ndx = ((parent * 2) + 2);
    int retval;

    if(leftC_Ndx > A.last && rightC_Ndx > A.last){ //case: 1 no children at all
        retval = -1;
    }else if(A.array[leftC_Ndx] < A.array[rightC_Ndx] || rightC_Ndx >= A.last){ //case 2: left is smaller than right OR right doesnt exist
        retval = leftC_Ndx;
    }else{
        retval = rightC_Ndx;
    }

    return retval;
}

int get_parent(int child){
    return (child - 1)/2;
}

void initHeap(heap *A){
    A->last = -1;
}

void printMinHeap(heap A){

    for(int i = 0; i <= A.last; i++){
        printf("%d ", A.array[i]);
    }
}

int isMember(heap A, int value){
    int i;
    for(i = 0; i <= A.last && A.array[i] != value; i++){}
    return (i <= A.last) ? 1 : 0;
}