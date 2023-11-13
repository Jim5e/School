//#include "PSEUDO_utilityFunctions.h"
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#define MAX 10 

typedef struct node{
    int data;
    int link;
    
}LIST;

typedef struct{
    LIST array[MAX];
    int avail;
    
}pseudoheap;

void initHeap(pseudoheap *A);
void insertElem(pseudoheap *A, int elem);
int allocSpace(pseudoheap *A);
void deAlloc(pseudoheap *A, int index);
void deleteElem(pseudoheap *A, int elem);

int main(){
    pseudoheap A;
    initHeap(&A);
    insertElem(&A, 6);
    insertElem(&A, 5);
    insertElem(&A, 4);
    insertElem(&A, 3);
    insertElem(&A, 2);
    insertElem(&A, 1);
    deleteElem(&A, 2);
    
    return 0;
}

void initHeap(pseudoheap *A){
    int i = 0;
    // A->avail = i;
    while(i < MAX){
        A->array[i].link = i - 1;
        i++;
    }
    // A->array[i].link = -1;
    A->avail = MAX - 1;
    
}

void insertElem(pseudoheap *A, int elem){
    int ndx = allocSpace(A); 
    
    if(ndx != -1){
        A->array[ndx].data = elem;
        A->array[ndx].link = A->array[MAX - 1].link;
         
    }

}

void deleteElem(pseudoheap *A, int elem){
    int ndx = A->avail;
    int *trav = &(A)->array[MAX - 1].link;
    
    while(*trav != -1){
      if(A->array[*trav].data == elem){
      	*trav = A->array[*trav].link;
        break;
        }
        trav = &(A)->array[*trav].link;
      }
      
      int temp = *trav;
      *trav = A->array[temp].link;
      deAlloc(A, temp);
}

int allocSpace(pseudoheap *A){
    int ndx = A->avail;
    
    if(ndx != -1){
    	A->avail = A->array[A->avail].link;        
    }
	
	return ndx;
}

void deAlloc(pseudoheap *A, int index){
    if(index >= 0 && index < MAX){
    	(A)->array[index].link = A->avail;
    	A->avail = index;
	}
}
