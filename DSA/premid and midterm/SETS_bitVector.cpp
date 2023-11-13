#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 8

typedef unsigned char SET[MAX + 1];

SET *UNION(SET *A, SET *B);
void initSet(SET *A);
void displaySet(SET A);
void insertElem(SET *A, int Array[], int count);

int main(){
	
	//Initialize sets nga di kapoy (?) is there more faster way tho
    SET A;
    int Array[] = {1,3,5,7,8};
    int countA = sizeof(Array) / 4;
    initSet(&A);
    insertElem(&A, Array, countA);
    
    SET B;
    int Brray[] = {1,5,6,8};
    int countB = sizeof(Brray) / 4;
    initSet(&B);
    insertElem(&B, Brray, countB);
    
    printf("Initial Sets:\n");
    displaySet(A);
    displaySet(B);
    
    printf("------------------------------------OPERATION------------------------------\n\n");
    
    printf("UNION:\n");
    SET C = UNION(&A, &B);
    displaySet(C);
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
	
	while(i <= count){
		(*A)[Array[i]] = 1;
		i++;
	}

}

SET *UNION (SET *A, SET *B){
	SET *C =(SET *) malloc(sizeof(SET));
	initSet(C);
	
	int i;
	
	for(i = 1; i <= MAX;i++){
		(*C)[i] = (*A)[i] && (*B)[i];
	}
	
	return C;
}

