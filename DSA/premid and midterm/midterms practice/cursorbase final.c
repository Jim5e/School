#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

typedef struct{
    int data;
    int link;
    
}Node;

typedef struct{
    Node array[MAX];
    int avail;
}Vheap;

typedef struct{
    Vheap VH;
    int head;
    
}List;

void initList(List *A);
int allocSpace(List *A);
void deAlloc(List *A, int node);
void insert(List *A, int elem);
void deleteElem(List *A, int elem);

int main(){
    List A;
    initList(&A);
    insert(&A, 5);
    insert(&A, 2);
    insert(&A, 1);
    deleteElem(&A, 2);
    
    
    return 0; 
}

void initList(List *A){
    int i = MAX - 1;
    
    while(i >= 0){
        A->VH.array[i].link = i - 1;
        i--;
    }
    
    
    A->head = -1;
    A->VH.avail = MAX - 1;
}

int allocSpace(List *A){
    int ndx = A->VH.avail;
    
    if(ndx != -1){
        A->VH.avail = A->VH.array[ndx].link;
    }
    
    return ndx;
}

void insert(List *A, int elem){
        int node = allocSpace(A);
    

    if(node != -1){
        A->VH.array[node].data = elem;
        A->VH.array[node].link = A->head;
        A->head = node;
    }else{
        printf("Fulll");
    }
    
    
}

void deleteElem(List *A, int elem){
	int *trav;
	
	for(trav = &(A)->head;*trav != -1 && A->VH.array[*trav].data != elem; trav = &A->VH.array[*trav].link);
	
	if(*trav != -1){
		int temp = *trav;
		*trav = A->VH.array[temp].link;
		deAlloc(A, temp);
	}
}

void deAlloc(List *A, int index){
	
	if(index >= 0 && index < MAX){ //if within range
		A->VH.array[index].link = A->VH.avail;
		A->VH.avail = index;
	}
}
