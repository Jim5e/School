#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 10
//SETS: ARRAY IMPLEMENTATION (1/3)
typedef unsigned int SET;

SET UNION(SET A, SET B);
SET INTERSECTION();
SET DIFFERENCE();

int main(){
	SET A[] = {7,6,5,4};
	SET B[] = {14, 10, 9, 8, 7, 2};

	UNION(A, B);
	

	
	
	return 0;
}

SET UNION(SET A, SET B){
	int countA = sizeof(A) / 4;
	int countB = sizeof(B) / 4;	
	
	printf("%d", A[0]);
	
	return 0;
}
