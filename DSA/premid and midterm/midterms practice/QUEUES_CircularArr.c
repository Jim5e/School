#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 5

typedef struct{
    char fname[8];
    int cash;
    
}info;


typedef struct {
    info customers[SIZE];
    int front;
    int rear;    
    
}queue;

void initQueue(queue *A);
void enQueue(queue *A, info Data);
void deQueue(queue *A);
void displayQ(queue A);
int isFull(queue A);
int isEmpty(queue A);
void makeNull();



int main(){
    //values
    info A = {"Alice", 11};
    info B = {"Burns", 22};
    info C = {"Courtny", 33};
    info D = {"Doug", 44};
    
    queue Wallmart;
    initQueue(&Wallmart);
//    printf("%d", isFull(Wallmart));
    enQueue(&Wallmart, A);
    enQueue(&Wallmart, B);
    enQueue(&Wallmart, C);
    enQueue(&Wallmart, D);
//    deQueue(&Wallmart);
    enQueue(&Wallmart, A);
//    deQueue(&Wallmart);
//    enQueue(&Wallmart, A);
    displayQ(Wallmart);
    
    return 0;
}

void initQueue(queue *A){
    //set front and rear
    A->front = 0;
    A->rear = 0;
}

void enQueue(queue *A, info Data){
    if(!isFull(*A)){
        A->customers[A->rear] = Data;
        A->rear = ((A->rear + 1) % SIZE);
    }else{
        printf("The queue is Full\n");
    }
}


void deQueue(queue *A){
    if(!isEmpty(*A)){
        A->front = ((A->front + 1) % SIZE);        
    }

}

int isEmpty(queue A){
    return (A.rear == A.front);
}

int isFull(queue A){
    return ((A.rear + 1) % SIZE) == A.front; //if rear is 1 less than front, it means theres no space to add.
}


void displayQ(queue A){
    int i;
    
    for(i = A.front; i != A.rear; i = (i + 1) % SIZE){
        printf("%s - %d\n", A.customers[i].fname, A.customers[i].cash);
    }
    
    printf("\n\nFront: %d\n", A.front);
    printf("Rear: %d", A.rear);
}
