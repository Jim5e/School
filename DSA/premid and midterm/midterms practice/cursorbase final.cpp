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
void insert(List *A, int data);

int main(){
    List A;
    initList(&A);
    
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

void insert(List *A, int data){
	int node = allocSpace(A);
	
	
}
