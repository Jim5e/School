#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int elem;
    struct node* link;
}*LIST;


void insertFirst(LIST *A, int x);
void mergeSortedLL(LIST *A, LIST *B);
void printList(LIST A);

int main(){
    LIST A = NULL;
    LIST B = NULL;

    insertFirst(&A, 5);
    insertFirst(&A, 3);
    insertFirst(&A, 1);

    insertFirst(&B, 6);
    insertFirst(&B, 4);
    insertFirst(&B, 2);    


    mergeSortedLL(&A, &B);
    printList(A);

    return 0;
}

void insertFirst(LIST *A, int x){
    LIST newNode = (LIST) malloc (sizeof(struct node));
    if(newNode != NULL){
        newNode->elem = x;
        newNode->link = *A;
        *A = newNode;
    }
}

void mergeSortedLL(LIST *A, LIST *B){
    LIST *Atrav = A;
    LIST *Bptr = B;

    while(*Bptr != NULL){
        if(*Atrav == NULL || (*Atrav)->elem > (*Bptr)->elem){
            LIST temp = *Bptr;
            *Bptr =  temp->link;
            temp->link = *Atrav;
            *Atrav = temp;
        }
        if(*Atrav != NULL){
            Atrav = &(*Atrav)->link;
        }
    }
}

void printList(LIST A){
    LIST trav = A;

    while(trav != NULL){
        printf("%d", trav->elem);
        trav = trav->link;
        if(trav != NULL){
         printf("->");           
        }
    }
}