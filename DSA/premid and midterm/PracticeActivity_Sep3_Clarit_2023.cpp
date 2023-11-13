#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

//======================================================
//Author: Lawrence James A. Clarit
//Goal of the Program: To display mastery of pointers, ADT, and array implementations
//Date Started: 9/3/23
//Date Finished: ?
//======================================================
typedef struct list{
	int count;
	char array[MAX];
	
}LIST;


//prototypes
LIST *initList(); // i prefer and used version #2: LIST * to struct
void insertFirst(LIST *A, char newElem);
void insertLast(LIST *A, char newElem);
void insertAt(LIST *A, char newElem, int index); //list to insert, what to insert, what index to insert at
void deleteAt(LIST *A, int index); //delete a char at a specific index
LIST *deleteOccurences(LIST *A, char given); // delete ALL occurences of a specific char in the lsit
...finish this please (add more functions)
void displayList(LIST *A);


int main(){
	//initialize list
	LIST *catcher = initList();
	
	//different operations
	insertFirst(catcher, 'E');
	insertFirst(catcher, 'E');
	insertFirst(catcher, 'X');
	insertFirst(catcher, 'B');
	insertFirst(catcher, 'X');

//	insertAt(catcher, 'c', 1);
//	deleteAt(catcher, 4);
	catcher = deleteOccurences(catcher, 'X');


	

	
	//display
	displayList(catcher);
	
}

//FUNCTION DEFINITIONS------------------------------------------------------------

LIST *initList(){
	
	LIST *pointer = (LIST *) calloc (1, sizeof(struct list));

	return pointer;
	
}

void insertFirst(LIST *A, char newElem){
    int i;
    
    //check if list exists
    if(A != NULL){ //checks if list exists
        if(A->count < MAX){ //checks if there is space to insert
        A->count++; //we know theres space, so we know we can add.
            for(i = A->count; i > 0;i--){
                A->array[i] = A->array[i-1];
            }
            
            A->array[0] = newElem;
        }
    }

}

void insertLast(LIST *A, char newElem){
	int i;
	
	if(A != NULL){ //checks if list exists
		if(A->count < MAX){ //checks if there is space to insert
			A->array[A->count] = newElem;
			A->count++; //we alr know there is space so we can ++ count ahead.
			
		}
	}
	

}

void insertAt(LIST *A, char newElem, int index){  //list to insert, what to insert, what index to insert at
int i;

 if(A != NULL){
 	if(A->count < MAX){
 		if(index == 0){ //if they want to insert at index 0
 			insertFirst(A, newElem);
		 }else if(index == A->count){ //if they want to insert at the last index aka "count"
		 	insertLast(A, newElem);
		 }else{
		 	for(i = A->count; i > index; i--){
		 		A->array[i] = A->array[i-1];	
			 }
		 	
		 	//
		 	A->array[index] = newElem;
		 	A->count++;
		 	
		 	
		 	
		 }
		 

	 }
 }


}

void deleteAt(LIST *A, int index){ //delete a char at a specific index
int i;
	
	if(A != NULL){ //checks if list exists
		for(i = index ; i < A->count ; i++){
			A->array[i] = A->array[i + 1]; //we start at index, then give it the value of the person next to it (person to its right)
		}
		
		A->count--;
	}



}

LIST *deleteOccurences(LIST *A, char given){
	int i = 0;
	int j = 0;
	
	
	//create new malloc array to store "not-to-delete character"
	LIST *newArray = (LIST *) malloc (sizeof(LIST));
	newArray->count = 0;
	
	
	//traverse old array then transfer to newNode
	while(i < A->count){
		if(A->array[i] != given){
			newArray->array[j] = A->array[i];
			newArray->count++; 
			j++;
		}
		
		i++;
		
	}
	
	//use realloc to adjust for size
	LIST *finalArray = (LIST *) realloc (newArray, sizeof(LIST) * j);
	finalArray->count = j;
	
	return finalArray;
}


void displayList(LIST *A){
	int i;
	printf("Count: %d\n\n", A->count);
	
	for(i = 0; i < A->count; i++){
		printf("[%c]", A->array[i]);
	}
	
}
