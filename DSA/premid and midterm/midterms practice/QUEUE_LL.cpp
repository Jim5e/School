#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1

typedef struct{
    char fname[8];
    int cash;
    
}info;

typedef struct node {
    info customers[SIZE];
    struct node *link;  
    
}LIST;

typedef struct{
    LIST *front;
    LIST *rear;
    
}queue;

void initQueue(queue *A);
void enQueue(queue *A, info Data);
void deQueue(queue *A);
void displayQ(queue A);
int isEmpty(queue A);


int main(){
    //values
    info A = {"Alice", 11};
    info B = {"Burns", 22};
    info C = {"Courtny", 33};
    info D = {"Doug", 44};    
    
    
    queue brothers;
    initQueue(&brothers);
    enQueue(&brothers, A);
    enQueue(&brothers, B);
    enQueue(&brothers, C);
    enQueue(&brothers, D);
    deQueue(&brothers);
    deQueue(&brothers);
    deQueue(&brothers);
    deQueue(&brothers);
    displayQ(brothers);
    
    
}

void initQueue(queue *A){
    A->front = NULL;
    A->rear = NULL;
}

void enQueue(queue *A, info Data){
	LIST *newNode = (LIST *) malloc (sizeof(LIST));
	newNode->link = NULL;
	
    if(isEmpty(*A)){
        A->front = newNode;
        A->front->customers[0] = Data;
        A->rear = A->front;        
    }else if(!isEmpty(*A)){
        newNode->customers[0] = Data;
        A->rear->link = newNode;
        A->rear = newNode;
    }

}

void deQueue(queue *A){
	if(A->front != NULL){	
		A->front = A->front->link;	
	}
	
	if(A->front == NULL){
		printf("No more people to deQueue");
	}
}


int isEmpty(queue A){
    return (A.front == NULL);
}

void displayQ(queue A){
	while(A.front != NULL){
		printf("%s - %d\n",A.front->customers[0].fname, A.front->customers[0].cash);
		A.front = A.front->link;
	}
}
