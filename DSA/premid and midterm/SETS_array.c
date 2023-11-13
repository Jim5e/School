#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define SIZE 10
//SETS: ARRAY IMPLEMENTATION (1/3)
typedef unsigned char SET; 

void displaySet(SET *set, int setCount);
void bubbleSort(SET *set, int size);
SET *UNION(SET *A, SET *B, int countA, int countB, int *countC);
SET *Intersection(SET *A, SET *B, int countA, int countB, int *countC);
SET *Difference(SET *A, SET *B, int countA, int countB, int *countC);


int main(){
    SET A[SIZE] = {63,10,22,20};
    SET B[SIZE] = {20,15,11,10,9,8,7,5,1,2};    
    int countA = 4;
    int countB = 10;
    int countC;
    //set
    printf("SET A: ");
    displaySet(A, countA);
    printf("SET B: ");
    displaySet(B, countB);
    
    printf("-----------------------------OPERATIONS--------------------------------\n\n\n");
    //UNION
    SET *x = UNION(A, B, countA, countB, &countC);
	printf("A U B (SET union):\n");
    displaySet(x, countC);
    
    //INTERSECTION
    SET *y = Intersection(A, B, countA, countB, &countC);
	printf("A n B (SET intersection):\n");
    displaySet(y, countC);

    //difference
    SET *z = Difference(A, B, countA, countB, &countC);
    printf("A - B (SET difference):\n");
    displaySet(z, countC);

    
    return 0;
}

SET *UNION(SET *A, SET *B, int countA, int countB, int *countC){
    SET *C = malloc(sizeof(SET) * SIZE);
    *countC = countB;
    //transfer (the entire) one of the sets to the C
    memcpy(C, B, (sizeof(SET) * countB));
    
    //compare A to B, if it doesnt exists, transfer to C
    int i, x;
    for(i = 0; i < countA; i++){
        
        int doesExist = 0;
        
        for(x = 0;x < countB;x++){
            if(A[i] == B[x]){
                doesExist = 1;
                break;
            }
        }
        
        if(doesExist != 1){
            if((*countC) >= SIZE){
              C = realloc(C, sizeof(SET) * ((*countC) * 1.5));
            }
            
            C[(*countC)] = A[i];
            (*countC)++;
        }
    }
    bubbleSort(C, *countC);
    
    return C = realloc(C, sizeof(SET) * (*countC));
}

SET *Intersection(SET *A, SET *B, int countA, int countB, int *countC){
    SET *C = malloc(sizeof(SET) * SIZE);	
    *countC = 0;
	int i, x;
	
	for( i = 0; i < countA; i++){
		
		for(x = 0; x < countB; x++){
			if(A[i] == B[x]){
				C[(*countC)] = A[i];
				(*countC)++;
			}
		}
	}
	
	return C = realloc(C, sizeof(SET) * (*countC));
}

SET *Difference(SET *A, SET *B, int countA, int countB, int *countC){
    SET *C = malloc(sizeof(SET) * SIZE);
    *countC = 0;
    int itExists;
    
    //get intersection
    int interCount;
	SET *intersect = Intersection(A, B, countA, countB, &interCount);

	
	//whatever doesnt intersect of A and intersect, transfer to C
	int i, x;
    for(i = 0; i < countA; i++){
    	itExists = 0;
    	
    	for(x = 0; x < interCount; x++){
    		if(A[i] == intersect[x]){
    			itExists = 1;
			}
		}
		
		
		if(itExists == 0){ //if it doesnt exist, transfer to C
			C[(*countC)] = A[i];
			(*countC)++;
		}
	}
    
    bubbleSort(C, *countC);
    return C = realloc(C, sizeof(SET) * (*countC));
}

void bubbleSort(SET *set, int size) {
    int i, j;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            // Swap if the element found is greater than the next element
            if (set[j] > set[j + 1]) {
                SET temp = set[j];
                set[j] = set[j + 1];
                set[j + 1] = temp;
            }
        }
    }
}

void displaySet(SET *set, int setCount){
	int i;
	
	printf("SET: ");
	for(i = 0; i < setCount;i++){
		printf("%u ", set[i]);
	}
	
	printf("\n\n");
}
