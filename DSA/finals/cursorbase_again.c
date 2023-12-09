#include <stdio.h>
#include <stdlib.H>
#define MAX 15

typedef struct node{
    int data;
    int link;
}node;

typedef struct{
    node array[MAX];
    int avail;
}vheap;

typedef struct{
    int num[MAX];
    int count;
}ArrayList;

typedef int cursorList;

vheap initVheap();
void insertCBlist(vheap *A, ArrayList AL, cursorList *head);
void insertFirst(vheap *A, cursorList *head, int value);

int main(){
    cursorList head=-1;
    ArrayList X={{4,7,19,3,2,1},0};
    vheap main = initVheap();


    insertFirst(&A, &head, 6);
    return 0;
}


vheap initVheap(){
    vheap main;
    int i;

    for(i = 0; i < MAX - 1; i++){
        main.array[i].link = i+1;
    }

    main.array[i].link = -1;
    main.avail = 0;

    return main;
}

void insertFirst(vheap *A, cursorList *head, int value){
    //use avail to add
    int Ndx = A->avail;
    
    if(Ndx != -1){
        A->avail = A->array[Ndx].link;
        A->array[Ndx].data = value;
        A->array[Ndx].link = *head;
        *head = Ndx;
    }

}

void insertCBlist(vheap *A, ArrayList AL, cursorList *head){

}
