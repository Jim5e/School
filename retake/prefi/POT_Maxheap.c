#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct {
    int array[MAX];
    int last;
}LIST;

//MAJOR functions
void initMaxHeap(LIST *A);
void insertElem(LIST *A, int elem);
void deleteMax(LIST *A);
void Heapify(LIST *A);
void Heapsort(LIST *A);


//Helper
void initMaxHeap(LIST *A){
    A->last = -1;
}

int parent(int child){
    return (child-1)/2;
}

void display(LIST A){
    for(int i = 0; i <= A.last; i++){
        printf("%d ", A.array[i]);
    }
    printf("\nLAST: %d\n", A.last);
}


int main (){
    //Variables
    LIST given  = {{8,2,6,3,4,1,1,723,14,23},9}; //adjust size for testing ra.
    LIST MAIN;
    
    //
    // initMaxHeap(&MAIN);
    // for(int i = 0; i <= given.last; i++){
    //     insertElem(&MAIN, given.array[i]);
    // }

    display(given);
    Heapsort(&given);
    display(given);

    return 0;
}

void insertElem(LIST *A, int elem){
    if(A->last < MAX){ //check space
        A->last++;
        A->array[A->last] = elem;

        //satisfy POT
        int childNdx;
        for(childNdx = A->last; childNdx != 0;){
            int parentNdx = parent(childNdx);

            //check POT property
            if(A->array[parentNdx] < A->array[childNdx]){ //MAX HEAPPPPPPPPPP
                int temp = A->array[parentNdx];
                A->array[parentNdx] = A->array[childNdx];
                A->array[childNdx] = temp;
            }

            childNdx = parentNdx;
        }
    }
}

int BIGGEST(LIST H, int parentNdx){
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

void deleteMax(LIST *A){
    if(A->last > -1){ //check if not empty
        //swap root with last
        int temp = A->array[0];
        A->array[0] = A->array[A->last];
        A->array[A->last] = temp;
        A->last--;

        //push root DOWN since POT is broken
        int biggestChild;
        for(int parentNdx = 0, biggestChild = BIGGEST(*A, parentNdx); biggestChild <= A->last;){

            //swap parent & bigChild
            int temp = A->array[parentNdx];
            A->array[parentNdx] = A->array[biggestChild];
            A->array[biggestChild] = temp; 

            //adjust
            parentNdx = biggestChild;
            biggestChild = BIGGEST(*A, parentNdx);
        }
    }
}

void Heapify(LIST *A){
    //lowest level parent
    for(int parentNdx = parent(A->last); parentNdx >= 0 ; parentNdx--){
        int biggestChild;

        //push down root of subtree via swapping with biggestChild
        for(biggestChild = BIGGEST(*A, parentNdx); biggestChild <= A->last;){
             //swap parent & bigChild
            int temp = A->array[parentNdx];
            A->array[parentNdx] = A->array[biggestChild];
            A->array[biggestChild] = temp; 

            //adjust
            parentNdx = biggestChild;
            biggestChild = BIGGEST(*A, parentNdx); fix tomorrow
        }
    }
}


void Heapsort(LIST *A){
    if(A->last != -1){ //check if valid
        //heapify the LIST
        Heapify(A);   

        //delete till sorted
        int og_size = A->last;
        while(A->last != -1){
            deleteMax(A);
        }

        A->last = og_size;
    }
}
