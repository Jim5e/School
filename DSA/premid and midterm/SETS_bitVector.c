#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 8

typedef unsigned char SET[MAX + 1];

void initSet(SET *A);
void displaySet(SET A);
void insertElem(SET *A, int Array[], int count);
SET *UNION(SET *A, SET *B);
SET *Intersection(SET *A, SET *B);
SET *Difference(SET *A, SET *B);

int main(){
	
	//Initialize sets nga di kapoy (?) is there more faster way tho
    SET A;
    int Array[] = {};
    int countA = sizeof(Array) / 4;
    initSet(&A);
    insertElem(&A, Array, countA);
    
    SET B;
    int Brray[] = {};
    int countB = sizeof(Brray) / 4;
    initSet(&B);
    insertElem(&B, Brray, countB);
    
    printf("Initial Sets:\n");
    displaySet(A);
    displaySet(B);
    
    printf("------------------------------------OPERATION------------------------------\n\n");
    
    printf("UNION:\n");
    SET *X = UNION(&A, &B);
    displaySet(*X);
    
    printf("\nINTERSECTION:\n");
    SET *Y = Intersection(&A, &B);
    displaySet(*Y);
    
    printf("\nDifference:\n");
    SET *Z = Difference(&A, &B);
    displaySet(*Z);
}

void initSet(SET *A){
    int i;
    for(i = 0; i <= MAX; i++){
        (*A)[i] = 0;
    }
}

void displaySet(SET A){
    int count = 1;
    printf("Set: ");
    while(count <= MAX){
        printf("%u", A[count]);
        count++;
    }
    
    printf("\n");
}

void insertElem(SET *A, int Array[], int count){
	int i = 0;
	
	while(i < count){
		(*A)[Array[i]] = 1;
		i++;
	}

}

SET *UNION (SET *A, SET *B){
	SET *C =(SET *) malloc(sizeof(SET));
	initSet(C);
	
	int i;
	
	for(i = 1; i <= MAX;i++){
		(*C)[i] = (*A)[i] || (*B)[i];
	}
	
	return C;
}

SET *Intersection (SET *A, SET *B){
	SET *C =(SET *) malloc(sizeof(SET));
	initSet(C);
	
	int i;
	
	for(i = 1; i <= MAX;i++){
		(*C)[i] = (*A)[i] && (*B)[i];
	}
	
	return C;
}

SET *Difference (SET *A, SET *B){
	SET *C =(SET *) malloc(sizeof(SET));
	initSet(C);
	
	int i;
	
	for(i = 1; i <= MAX;i++){
		if((*A)[i] && (*B)[i] == 0){
			(*C)[i] = 1;
		}
	}
	
	return C;
}

