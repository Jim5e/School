#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int data;
    struct node *link;
    
}SET;

typedef struct{
    SET *head;
    SET *rear;
    
}SETptr;

void initSETptr(SETptr *A);
void insertElem(SETptr *A, int elem);
SET *UNION(SETptr *A, SETptr *B);

int main(){
    SETptr A;
    initSETptr(&A);
    insertElem(&A, 3);
    insertElem(&A, 1);
    insertElem(&A, 2);
    insertElem(&A, 4);
    insertElem(&A, 5);

	SETptr B;
    initSETptr(&B);
    insertElem(&B, 3);
    insertElem(&B, 1);
    insertElem(&B, 2);
    insertElem(&B, 4);
    insertElem(&B, 5);
    


  return 0;
  
}

void initSETptr(SETptr *A){
  A->head = NULL;
  A->rear = NULL;
}

void insertElem(SETptr *A, int elem) {
  SET *newNode = (SET *)malloc(sizeof(struct node));
  newNode->data = elem;

  if (A->head == NULL) { // if no nodes yet
    A->head = newNode;
    A->head->link = NULL;
    A->rear = newNode;
  } else if (elem > A->rear->data) { // if elem needs to be added to last, i.e. no more traversing
    A->rear->link = newNode;
    A->rear = A->rear->link;
    A->rear->link = NULL;
  } else {
    SET **trav = &(A->head);

    while (*trav != NULL && (*trav)->data <= elem) {
      trav = &((*trav)->link); //trav itself is moving
    }

    if (*trav != NULL && (*trav)->data > elem) {
      // Insert the new node before the current node
      newNode->link = *trav;
      *trav = newNode; //the thing trav is pointing to is moving
    }
  }
}



