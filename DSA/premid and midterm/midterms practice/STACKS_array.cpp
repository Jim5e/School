#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 3

typedef struct{
    char fname[10];
    char lname[10];
    char MI;
}StudName;

typedef struct{
    int year;
    char subjects[3];
}CourseDetails;

typedef struct{
    StudName name;
    CourseDetails course;
}Studrec;


typedef struct node{
    Studrec *people;
    int size;
    int count;
    int top;
    
}*stack, STACK;

void initStack(stack *A); 
void push(stack *A, Studrec info);
void pop(stack *A);
int top(stack A);
void printStack(stack A);
int isFull(stack A);
int isEmpty(stack A);
void isNull();


int main(){
    stack USC;
    initStack(&USC);
    
    //values
    Studrec A = {{"Arnold", "Arin", 'A'}, {1,"CS"}};
    Studrec B = {{"Benigno", "Borig", 'B'}, {2,"IT"}};
    Studrec C = {{"Carlo", "Cloaks", 'C'}, {3,"CE"}};
    
    //calls
    push(&USC, A);
    push(&USC, B);
    push(&USC, C);
    printStack(USC);
    push(&USC, C);
    push(&USC, C);
    pop(&USC);
    pop(&USC);
    pop(&USC);
    pop(&USC);
    pop(&USC);
    
    printStack(USC);
}

void initStack(stack *A){
    *A = (stack) calloc (1, (sizeof(struct node)));
    (*A)->size = SIZE;
    (*A)->people = (Studrec *)calloc(SIZE, sizeof(Studrec));
    (*A)->count = 0;
    (*A)->top = -1;
}

void push(stack *A, Studrec info){
    int i = (*A)->top;
   
    if(isFull(*A)){
    	(*A)->size = (int)((*A)->size * 1.5);
    	Studrec *ptr = (Studrec *) realloc ((*A)->people, ((*A)->size) * (sizeof(Studrec)));
    		if(ptr != NULL){
    			(*A)->people = ptr;	
			}else{
			printf("Memory Allocation Failed.");	
			}
	}
	
	(*A)->people[i + 1] = info;
    (*A)->count++;
    (*A)->top++;
}

void pop(stack *A){
	if(!isEmpty(*A)){
	(*A)->top--;
	(*A)->count--;			
	}
}

int top(stack A){
    return A->top;
}

int isFull(stack A){
    return (A->count == (A->size));
}

int isEmpty(stack A){
    return (A->count == 0);
}

void printStack(stack A) {
	stack temp;
	initStack(&temp);
	
	int i, r;
	if(isEmpty(A)){
		printf("Top: NONE\n");
	}else{
		printf("Top: %s\n", A->people[A->top].name.fname);
	}
	printf("Count: %d | Size: %d\n", A->count, A->size);

	for(i = A->top;A->count != 0;pop(&A)){
		push(&temp, A->people[i]);
		printf("\t%s\n", A->people[i--].name.fname);
	}

	for(r = temp->top ; temp->count != 0; pop(&temp)){
		push(&A, temp->people[r]);
		r--;		
	}
	
	printf("\n\n");
}


