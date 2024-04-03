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

void deleteMax(LIST *A){
    if(A->last > -1){ //check if not empty
        //swap root with last
        int temp = A->array[0];
        A->array[0] = A->array[A->last];
        A->array[A->last] = temp;
        A->last--;

        //push root DOWN since POT is broken
        int parentNdx = 0;
        int biggestChild = BIGGEST(*A, parentNdx);
        for(; biggestChild != -1 && biggestChild <= A->last;){

            if(A->array[parentNdx] < A->array[biggestChild]){
                //swap parent & bigChild
                int temp = A->array[parentNdx];
                A->array[parentNdx] = A->array[biggestChild];
                A->array[biggestChild] = temp; 
            }
            

            //adjust
            parentNdx = biggestChild;
            biggestChild = BIGGEST(*A, parentNdx);
        }
    }
}

int BIGGEST(LIST H, int parentNdx){
    int leftNdx = (parentNdx * 2) + 1;
    int rightNdx = (parentNdx * 2) + 2;
    int biggestNdx = -1;

    //check validity of index and also compare
    if(leftNdx <= H.last && H.array[leftNdx] > H.array[rightNdx]){
        biggestNdx = leftNdx;
    }else if(rightNdx <= H.last && H.array[rightNdx] > H.array[leftNdx]){
        biggestNdx = rightNdx;
    }

    return biggestNdx;
}

void Heapify(LIST *A){
    //lowest level parent
    for(int lowest = parent(A->last); lowest >= 0 ; lowest--){

        //fix subtrees
        int biggestChild;
        for(int current = lowest, biggestChild = BIGGEST(*A, current); biggestChild != -1 && biggestChild <= A->last;){

            if(A->array[current] < A->array[biggestChild]){
                //swap parent & bigChild
                int temp = A->array[current];
                A->array[current] = A->array[biggestChild];
                A->array[biggestChild] = temp;
            }

            //
            current = biggestChild;
            biggestChild = BIGGEST(*A, current);
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
