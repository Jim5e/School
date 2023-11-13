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
void deleteElem(SETptr *A, int elem);
void printSet(SETptr A);
int isMember(SETptr A, int elem);
SETptr UNION(SETptr A, SETptr B);
SETptr INTERSECTION(SETptr A, SETptr B);
SETptr DIFFERENCE(SETptr A, SETptr B);

int main(){
    SETptr A;
    initSETptr(&A);
    insertElem(&A, 3);
    insertElem(&A, 1);
    insertElem(&A, 7);
    insertElem(&A, 2);
    insertElem(&A, 5);

	SETptr B;
    initSETptr(&B);
    insertElem(&B, 7);
    insertElem(&B, 1);
    insertElem(&B, 2);
    insertElem(&B, 4);
    insertElem(&B, 9);
    
    deleteElem(&A, 2);
    
	printf("Initial Sets:\n");
	printSet(A);
	printSet(B);
	
	printf("-------------------------------OPERATIONS----------------------------------\n\n");
	printf("Union of A and B Sets: \n");	
	SETptr X = UNION(A, B);
	printSet(X);
	
	printf("Intersection of A and B Sets: \n");
	SETptr Y = INTERSECTION(A, B);
	printSet(Y);
	
	printf("Difference of A and B Sets: \n");
	SETptr Z = DIFFERENCE(A, B);
	printSet(Z);	
	
  return 0;
  
}

void initSETptr(SETptr *A){
  A->head = NULL;
  A->rear = NULL;
}

void insertElem(SETptr *A, int elem) {
  SET *newNode = (SET *)malloc(sizeof(struct node));
  newNode->data = elem;
	
	if(isMember(*A, elem)){
		printf("This element already exists.\n\n");
	}else if (A->head == NULL) { // if no nodes yet
    	A->head = newNode;
    	A->head->link = NULL;
    	A->rear = newNode;
  	}else if (elem > A->rear->data) { // if elem needs to be added to last, i.e. no more traversing
    	A->rear->link = newNode;
    	A->rear = A->rear->link;
    	A->rear->link = NULL;
  	}else{
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

void printSet(SETptr A){
	SET *trav = A.head;
	
	while (trav != NULL){
		printf("%d", trav->data);
		trav = trav->link;
	}
	
	printf("\n\n");
}

int isMember(SETptr A, int elem){
	int retval = 0;
	SET *trav = A.head;
	
	while(trav != NULL){
		if(trav->data == elem){
			retval = 1;
		}
		trav = trav->link;
	}
	
	return retval;
}

void deleteElem(SETptr *A, int elem) {
    SET **trav = &((A)->head);

	if(!isMember((*A), elem)){
		printf("This element does not exist.");
	}else{
    while (*trav != NULL && (*trav)->data != elem) {
        trav = &((*trav)->link);
    }

    if (*trav != NULL) {
        SET *temp = *trav;
        *trav = (*trav)->link; // Remove the node from the linked list.
        free(temp); // Free the memory of the removed node.
        (A)->rear = NULL; // Reset rear to NULL to indicate the end of the list.
    }		
}
}


SETptr UNION(SETptr A, SETptr B){
	SETptr C;
	initSETptr(&C);
	
	while(A.head != NULL && B.head != NULL){
		if(A.head->data < B.head->data){
			insertElem(&C, A.head->data);
			A.head = A.head->link;
		}else if(B.head->data < A.head->data){
			insertElem(&C, B.head->data);
			B.head = B.head->link;
		}else{
			insertElem(&C, A.head->data);
			A.head = A.head->link;
			B.head = B.head->link;
		}
		
	}
	
	//for empty sets
	if(A.head == NULL){
		while(B.head != NULL){
		insertElem(&C, B.head->data);
		B.head = B.head->link;	
		}	
	}
	
	if(B.head == NULL){
		while(A.head != NULL){
		insertElem(&C, A.head->data);
		A.head = A.head->link;	
		}	
	}	
	
	return C;
}

SETptr INTERSECTION(SETptr A, SETptr B){
	SETptr C;
	initSETptr(&C);
	
	while(A.head != NULL && B.head !=NULL){
		if(A.head->data <  B.head->data){
			A.head = A.head->link;
		}else if(B.head->data < A.head->data){
			B.head = B.head->link;
		}else{
			insertElem(&C, A.head->data);
			A.head = A.head->link;
			B.head = B.head->link;
		}
		
	}
	
	return C;
}

SETptr DIFFERENCE(SETptr A, SETptr B) {
    SETptr C;
    initSETptr(&C);

    while (A.head != NULL) {
        if (B.head == NULL || A.head->data < B.head->data) {
            insertElem(&C, A.head->data);
            A.head = A.head->link;
        } else if (B.head->data < A.head->data) {
            B.head = B.head->link;
        } else {
        	A.head = A.head->link;
            B.head = B.head->link;
        }
    }

    return C;
}





