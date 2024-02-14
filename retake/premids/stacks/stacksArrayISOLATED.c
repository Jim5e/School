#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX 10

typedef struct{
    char elem[MAX];
    int top;
}stack;

void initStack(stack *A);
void push(stack *A, char elem);
char pop(stack *A);
char peek(stack A);
bool isEmpty(stack A);
bool isFull(stack A);
void makeNull(stack *A);
void displayStack(stack *A);

int main(){
    stack MAIN;
    initStack(&MAIN);
    push(&MAIN, 'X');
    push(&MAIN, 'X');
    push(&MAIN, 'X');
    push(&MAIN, 'X');


    displayStack(&MAIN);
    return 0;
}

void initStack(stack *A){
    A->top = -1;
}

void push(stack *A, char elem){
    if(!isFull(*A)){
        A->top++;
        A->elem[A->top] = elem;
    }else{
        printf("STACK IS FULL.\n");        
    }
}

char pop(stack *A){
    char deleted = '\0';
    if(!isEmpty(*A)){
        deleted = A->elem[A->top];
        A->top--;
    }else{
        printf("STACK IS EMPTY.\n");
    }

    return deleted;
}

char peek(stack A){
    return A.elem[A.top];
}

bool isEmpty(stack A){
    return (A.top == -1)? true : false;
}

bool isFull(stack A){
    return (A.top == MAX-1)? true : false;
}

void makeNull(stack *A){
    A->top = -1;
}

void displayStack(stack *A){
    stack temp;
    initStack(&temp);
    while(!isEmpty(*A)){
        push(&temp, pop(A));
    }

    while(!isEmpty(temp)){
        printf("%c", pop(&temp));
    }
}