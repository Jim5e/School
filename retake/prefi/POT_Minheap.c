#include <stdio.h>
#include <stdlib.h>
#define MAX 15

typedef struct {
    int array[MAX];
    int last;
}LIST;

//MAJOR functions
void initMaxHeap(LIST *A);
void insertElem(LIST *A, int elem);
void deleteMin(LIST *A);
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
    LIST given  = {{50,23,12,70,43,90,4,5,63,1,33,65,25,14,1}, 14}; //adjust size for testing ra.

    display(given);
    // Heapsort(&given);
    Heapify(&given);
    display(given);

    return 0;
}

int SMALLEST(LIST H, int parentNdx){
    int leftNdx = (parentNdx * 2) + 1;
    int rightNdx = (parentNdx * 2) + 2;
    int smallestNdx = parentNdx;

    if(leftNdx <= H.last && H.array[leftNdx] < H.array[smallestNdx]){
        smallestNdx = leftNdx;
    }
    if(rightNdx <= H.last && H.array[rightNdx] < H.array[smallestNdx]){
        smallestNdx = rightNdx;
    }

    return smallestNdx == parentNdx ? -1 : smallestNdx;
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
            if(A->array[parentNdx] > A->array[childNdx]){ //MIN HEAP
                int temp = A->array[parentNdx];
                A->array[parentNdx] = A->array[childNdx];
                A->array[childNdx] = temp;
            }

            childNdx = parentNdx;
        }
    }
}

void deleteMin(LIST *A){
    if(A->last > -1){ //check if not empty
        //swap root with last
        int temp = A->array[0];
        A->array[0] = A->array[A->last];
        A->array[A->last] = temp;
        A->last--;

        //push root DOWN since POT is broken
        int parentNdx = 0;
        int smallestChild;
        for(smallestChild = SMALLEST(*A, parentNdx); smallestChild != -1 && smallestChild <= A->last;){

            if(A->array[parentNdx] > A->array[smallestChild]){
                //swap parent & smallChild
                int temp = A->array[parentNdx];
                A->array[parentNdx] = A->array[smallestChild];
                A->array[smallestChild] = temp; 
            }
            

            //adjust
            parentNdx = smallestChild;
            smallestChild = SMALLEST(*A, parentNdx);
        }
    }
}

void Heapify(LIST *A){
    //lowest level parent
    for(int lowest = parent(A->last); lowest >= 0 ; lowest--){

        //fix subtrees
        int smallestChild;
        for(int current = lowest, smallestChild = SMALLEST(*A, current); smallestChild != -1 && smallestChild <= A->last;){

            if(A->array[current] > A->array[smallestChild]){
                //swap parent & smallChild
                int temp = A->array[current];
                A->array[current] = A->array[smallestChild];
                A->array[smallestChild] = temp;
            }

            //
            current = smallestChild;
            smallestChild = SMALLEST(*A, current);
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
            deleteMin(A);
        }

        A->last = og_size;
    }
}