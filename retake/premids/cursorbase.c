#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct node{
    char elem;
    int link;
}Nodetype;

typedef struct{
    Nodetype elements[MAX];
    int avail;
}VirtualHeap;

typedef int CList;

void initVirtualHeap(VirtualHeap *A);
void insertFirst(VirtualHeap *A, CList *head, char elem);
void insertElemAtPos(VirtualHeap *A, CList *head, char elem, int pos);
void deleteElem(VirtualHeap *A, CList *head, char elem);
int allocSpace(VirtualHeap *A);
void deallocSpace(VirtualHeap *A, int index);
void displayVH(VirtualHeap A, CList head);



int main(){
    VirtualHeap MAIN;
    CList L = -1;
    initVirtualHeap(&MAIN);
    insertFirst(&MAIN, &L, 'A');
    insertFirst(&MAIN, &L, 'B');
    insertFirst(&MAIN, &L, 'C');
    insertFirst(&MAIN, &L, 'D');
    deleteElem(&MAIN, &L, 'C');
    deleteElem(&MAIN, &L, 'A');
    insertFirst(&MAIN, &L, 'A');


    displayVH(MAIN, L);
    return 0;
}

void initVirtualHeap(VirtualHeap *A){
    int i;
    for(i = MAX-1; i > -1; i--){
        A->elements[i].link = i-1;
    }
    A->avail = MAX-1;
}

int allocSpace(VirtualHeap *A){
    int temp;
    temp = A->avail;
    A->avail = A->elements[temp].link;
    return temp;
}

void deallocSpace(VirtualHeap *A, int index){
    A->elements[index].link =A->avail;
    A->avail = index;
}

void insertFirst(VirtualHeap *A, CList *head, char elem){
    if(A->avail != -1){
        int newNode = allocSpace(A);
        if(newNode != -1){
            A->elements[newNode].elem = elem;
            A->elements[newNode].link = *head;
            *head = newNode;
        }        
    }
}

void deleteElem(VirtualHeap *A, CList *head, char elem){
    if(*head != -1){
        int *trav;
        for(trav = head; *trav != -1 && A->elements[*trav].elem != elem; trav = &A->elements[*trav].link){}
        if(*trav != -1){
            CList temp = *trav;
            *trav = A->elements[temp].link;
            deallocSpace(A, temp);
        }
    }
}

void insertElemAtPos(VirtualHeap *A, CList *head, char elem, int pos){
    //will do this tomorrow
}

void displayVH(VirtualHeap A, CList head){
    printf("NDX\tDATA\t|\tLINK\n");
    for(int index = head; index != -1; index = A.elements[index].link){
        printf("%d:\t[%c]\t\t|\t[%d]\n", index, A.elements[index].elem, A.elements[index].link);
    }
}