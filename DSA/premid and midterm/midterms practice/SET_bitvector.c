#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10

typedef struct node {
    int *data;
    int count;
    int size;
} *SET;

void populateSET(SET *A, int arr[], int arrSize);
void initSet(SET *A);
void insertElem(SET *A, int elem);
void deleteElem(SET *A, int elem);
void printSet(SET A);
SET UNION(SET A, SET B);
SET INTERSECTION(SET A, SET B);
SET DIFFERENCE(SET A, SET B);

int main() {
    SET A, B;
    int Arr[] = {1, 2, 4, 7, 9, 3};
    int Brr[] = {1, 2, 5, 6, 7, 8};
    int arrSize = (sizeof(Arr) / 4);
    int brrSize = (sizeof(Brr) / 4);
    initSet(&A);
    initSet(&B);
    populateSET(&A, Arr, arrSize);
    populateSET(&B, Brr, brrSize);
    
	printf("Initial Sets:\n");    
    printSet(A);
    printSet(B);

	printf("-------------------------------OPERATIONS----------------------------------\n\n");
	printf("Union of A and B Sets: \n");
	SET X = UNION(A, B);
	printSet(X);
	
	printf("Intersection of A and B Sets: \n");
	SET Y = INTERSECTION(A, B);
	printSet(Y);
	
	printf("Difference of A and B Sets: \n");
	SET Z = DIFFERENCE(A, B);
	printSet(Z);
	
	//utilizy func
//	deleteElem(&Z, 9);
//	printSet(Z);
	
	return 0;
}

void initSet(SET *A) {
    *A = (SET)malloc(sizeof(struct node));
    (*A)->count = 0;
    (*A)->size = SIZE;
    (*A)->data = (int *)calloc(SIZE, sizeof(int));
}

void insertElem(SET *A, int elem) {
    (*A)->data[elem] = 1;
    (*A)->count++;
}

void populateSET(SET *A, int arr[], int arrSize){
    int i = 0;
    
    while(i < arrSize){
        insertElem(A, arr[i]);
        i++;
    }
}

void printSet(SET A){
    int i  = 0;
    while (i < A->size){
        printf("%d", A->data[i]);
        i++;
    }
    
    printf("\n");
}

SET UNION(SET A, SET B){
	SET C;
	int i = 0;
	initSet(&C);
	
	while(i < SIZE){
		if(A->data[i] || B->data[i]){
		C->data[i] = 1;	
		}
		i++;
	}
	
	return C;
}

SET INTERSECTION(SET A, SET B){
	SET C;
	int i = 0;
	initSet(&C);
	
	while(i < SIZE){
		if(A->data[i] && B->data[i]){
			C->data[i] = 1;
		}
		i++;
	}
	
	return C;
}

SET DIFFERENCE(SET A, SET B){
	SET C;
	int i = 0;
	initSet(&C);
	
	while(i < SIZE){
		if(A->data[i] & ~B->data[i]){
			C->data[i] = 1;
		}
		i++;
	}
	
	return C;
}

void deleteElem(SET *A, int elem){
	(*A)->data[elem] = 0;
	(*A)->count--;
}
