#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char fname[20];
    char lname[30];
    char MI;
}StudName;

typedef struct{
    int year;
    char subjects[3];
}CourseDetails;

typedef struct{
    StudName name;
    CourseDetails course;
}StudRec;

typedef struct node{
    StudRec Person;
    struct node *link;
}*STACK;

void initStack(STACK *A);
void Pop(STACK *A);
void Push(STACK *A, StudRec User);
STACK Top(STACK *A);
int isEmpty(STACK *A);
void printStack(STACK *A);
StudRec initStudRec();

int main(){
    //values
    StudRec James;
     strcpy(James.name.fname, "James");
     strcpy(James.name.lname, "Clarit");
     James.name.MI = 'X';
     James.course.year = 2;
     strcpy(James.course.subjects, "CS");
    StudRec John;
     strcpy(John.name.fname, "John");
     strcpy(John.name.lname, "Vilagom");
     John.name.MI = 'R';
     John.course.year = 3;
     strcpy(John.course.subjects, "IT");
    //
    
    STACK A;
    initStack(&A);
    Push(&A, James);
    Push(&A, John);
    Push(&A, James);
    Push(&A, John);
    Pop(&A);
    STACK G = Top(&A);
    printStack(&A);
    
    printf("%d", isEmpty(&A));
    
    return 0;
}

void initStack(STACK *A){
    *A = NULL;
}

void Push(STACK *A, StudRec User){
     STACK newNode = (STACK ) malloc (sizeof(struct node));
     newNode->Person = User;
     newNode->link = NULL;
    
     //insert first
     if(*A != NULL){
         newNode->link  = *A;
         *A = newNode;
     }else{
         *A = newNode;
     }

 }
 
void Pop(STACK *A){
    (*A) = ((*A)->link);
}

STACK Top(STACK *A){
    STACK top = (*A);
    
    return top;
}

int isEmpty(STACK *A){
    return ((*A) == NULL)?(1):(0);
}

void printStack(STACK *A){
    STACK temp;
    initStack (&temp);
    
    //print top then transfer to temp
    while(isEmpty(A) != 1){
        STACK current = Top(A);
        printf("%s", current->Person.name.fname);
        Push(&temp, current->Person);
        Pop(A);
    }
    
    while(isEmpty(&temp) != 1){
    	STACK current = Top(&temp);
    	Push(A, current->Person);
    	Pop(&temp);
	}
    
}
