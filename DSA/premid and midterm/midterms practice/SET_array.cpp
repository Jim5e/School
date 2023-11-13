#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 10

typedef unsigned char collection;

typedef struct node{
    collection *elem;
    int count;
    int size;
    
}*SETptr, SET;

void initSet(SETptr *A);
SET *UNION(SETptr *A, SETptr *B);
void INTERSECTION();
void DIFFERENCE();
void isMember();
void deleteElem();
void insertElem();
void displaySet();

int main(){
    SETptr A,B;
    initSet(&A);
    initSet(&B);
    
    
    A->elem[0] = {'c'};
}

void initSet(SETptr *A){
  (*A) = (SETptr ) malloc (sizeof(SET));
  (*A)->count = 0;
  (*A)->size = SIZE;
  (*A)->elem = (collection *) malloc (sizeof(char) * SIZE);
}
