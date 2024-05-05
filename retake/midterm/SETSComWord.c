#include <stdio.h>
#include <stdbool.h>

typedef char SET;

void displayBitPattern(char A);
void printSet(char A);
SET UNION(SET A, SET B);
SET INTERSECTION(SET A, SET B);
SET DIFFERENCE(SET A, SET B);
void insertBit(SET *A, char elem);
void deleteBit(SET *A, char elem);


int main (){
    char A = 5;
    SET B = 13;
    // displayBitPattern(B);

    // SET X = UNION(A, B);s
    // SET Y = INTERSECTION(A,B);
    // SET Z = DIFFERENCE(A,B);
    
    //bit manipulation
    // insertBit(&A, 1);
    // deleteBit(&A, 2);
    return 0;
}


void displayBitPattern(char A){
    unsigned char mask = 1 << (sizeof(char) * 8)-1;
    while(mask > 0){
        printf("%d", (A & mask) == 0? 0:1);
        mask = mask >> 1;
    }
    printf("\n");
}

SET UNION(SET A, SET B){
    printf("Union:\n");
    printf("%6s","A:");
    displayBitPattern(A);
    printf("%6s","B:");
    displayBitPattern(B);
    SET C = A | B;
    printf("%6s","C:");
    displayBitPattern(C);
    return C;
}

SET INTERSECTION(SET A, SET B){
    printf("Intersection:\n");
    printf("%13s","A:");
    displayBitPattern(A);
    printf("%13s","B:");
    displayBitPattern(B);
    SET C = A & B;
    printf("%13s","C:");
    displayBitPattern(C);
    return C;
}

SET DIFFERENCE(SET A, SET B){
    printf("Difference:\n");
    printf("%10s","A:");
    displayBitPattern(A);
    printf("%10s","B:");
    displayBitPattern(B);
    SET C = A & ~B;
    printf("%10s","C:");
    displayBitPattern(C);
    return C;
}

void insertBit(SET *A, char elem){
    printf("%-8s","Before: ");
    displayBitPattern(*A);

    unsigned char mask = 1 << elem;
    *A = *A | mask;

    printf("%-8s","After: ");
    displayBitPattern(*A);
}

void deleteBit(SET *A, char elem){
    printf("%-8s","Before: ");
    displayBitPattern(*A);

    unsigned char mask = ~(1 << elem);
    *A = *A & mask;

    printf("%-8s","After: ");
    displayBitPattern(*A);    
}