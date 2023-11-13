#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void AND();
void leftShift();
void rightShift();
void XOR();
void printBinary(int decimal, int SIZE); //parameters: decimal you want to convert to binary, size of the binary e.g. 8-bit, 16-bit, 32-bit

int main(){
	//Bitwise Operators:
	//& "AND" -> binary operator, if both bits are 1, AND returns 1;
	//| "OR" -> binary operator, if either bits have 1, OR returns 1. AKA "INCLUSIVE" OR, meaning they make the result 1 if BOTH are 1
	//~ "NOT" -> UNARY operator, reverses the bit of the number. If 1, then turn to 0. if 0, then turn to 1;
	//<< "lEFT SHIFT" -> binary operator
	//>> "RIGHT SHIFT" ->
	//^ "XOR" -> Similar to or except for 1 scenario. AKA "EXCLUSIVE" OR, meaning they make the result 0 if BOTH are 1. 
	
	//calls
//	AND();
//	leftShift();
//	rightShift();
//	XOR();
	printBinary(25, 8);

}

void AND(){
	//AND
	char x = 1, y = 2; // x = 0000 0001, y = 0000 0010, this is represented as 8 bits because we are using CHAR datatype
	if (x&y){ //REMEMBER that & returns 1 if true, and 0 if false. If's condition evaluates  if the inside is TRUE, it fails. 
		printf("The value of x&y is 1"); 
	}	
}

void leftShift(){
	char val = 3; //val = 0000 0011
	int x = 1;
	val = val << x; // val now becomes 0000 0110 (notice how the entire 8bit gets "moved" to the right by "1" (aka x))
	printf("leftShift of val: %d", val);
	
	//Mathematical formula: [val * 2^x] -> [3 * 2^1] -> [6].  2 to the power of the rightOperand. Left shift is MULTIPLICATION
}

void rightShift(){
	char val = 3; //val = 0000 0011
	int x = 1;
	val = val >> x; // val now becomes 0000 0001 (notice how the entire 8bit gets "moved" to the right by "1" (aka x))
	printf("rightShift of val: %d", val);
	
	//Mathematical formula: [val / 2^x] -> [3 / 2^1] -> [1].  2 to the power of the rightOperand. right shift is DIVISION
}

void XOR(){
	char x = 3; //0000 0011
	char y = 7; //0000 0111
	
	char val = x ^ y; // val = 0000 0100 = 4
	printf("XOR value is: %d", val);
}

void printBinary(int decimal, int SIZE){
	int bit[SIZE];
	int index;
	int i;
	
	for(index = 0; index < SIZE; index++){
		bit[index] = decimal & 1; //get rightmost bit
		decimal = decimal >> 1; //shift right
	}
	
	
	for(i = index-1; i >= 0; i--){ //print starting from last index (since pabali dapat, least significant bit would be pushed to the last)
		printf("%d", bit[i]);
		
		if(i % 4 == 0){
			printf(" ");
		}
	}
}
