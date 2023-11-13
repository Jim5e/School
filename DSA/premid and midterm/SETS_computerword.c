#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef unsigned char SET;
void displayBINARY(SET A);
void displayElem(SET A);
SET UNION(SET A, SET B);
SET INTERSECTION(SET A, SET B);
SET DIFFERENCE(SET A, SET B);

int main(){
	SET A = 25;
	SET B = 122;
	
	printf("Initial Sets:\n");	
	displayBINARY(A);
	displayBINARY(B);
	displayElem(B);


	printf("-------------------------------OPERATIONS----------------------------------\n\n");	
	//
	printf("Union of A and B Sets: \n");
	SET X = UNION(A,B);
	displayBINARY(X);
	
	printf("Intersection of A and B Sets: \n");
	SET Y = INTERSECTION(A,B);
	displayBINARY(Y);
	
	printf("Differnce of A and B Sets: \n");
	SET Z = DIFFERENCE(A,B);
	displayBINARY(Z);
	return 0;
}

void displayBINARY(SET A){
	SET mask = 1 << ((sizeof(SET) * 8) - 1);
	
	while(mask != 0){
		if(A & mask){
		printf("1");	
		}else{
		printf("0");
		}
		mask = mask >> 1;
	}
	printf("\n");
}

void displayElem(SET A){
	int i = (sizeof(SET) * 8) - 1;
	SET mask = 1 << ((sizeof(SET) * 8) - 1);
	
	while(mask != 0){
		if(A & mask){
			printf("[%d]", i);
		}else{
			printf("[-]");
		}
		
		i--;
		mask = mask >> 1;
}
	printf("\n\n");	
}

SET UNION(SET A, SET B){return A | B;}
SET INTERSECTION(SET A, SET B){return A & B;}
SET DIFFERENCE(SET A, SET B){return A & ~B;}
