#include <stdio.h>
#include <stdlib.h>
#define BITS 8

typedef unsigned char SET;

void displayBitPattern(SET A);
void displaySetElements(SET A);
//void initSet();
//void insert(int index); //inserts 
//void member();
//void deleteMember();


int main(){

	SET A = 149;
	//function calls
	displayBitPattern(A);
//	displaySetElements(A);

    
    return 0;
}

void displayBitPattern(SET num){
    SET mask = (sizeof(char) * BITS) - 1;
    mask = 1 << mask;


    while(mask > 0){
        printf("%d", (num & mask) == 0? 0:1);
        mask >>=1;
    } 
    
    printf("\n\n");
}

void displaySetElements(SET num){
    SET mask = (sizeof(char) * BITS) - 1;
    mask = 1 << mask;
    int i;
    
 	for(i = BITS - 1; mask > 0; mask >>= 1){
 		if(mask & num){
 			printf("%d",i);
 		}
 		i--;
	 }
	 
	printf("\n\n");
}
