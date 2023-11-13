#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

typedef struct node{
    int data;
    struct node *link;
    
}*LIST;

typedef LIST Dictionary[MAX];

int hash(int num);
void initDict(Dictionary *A);
void insertElem(Dictionary *A, int Elem);
void displayHashGroup(Dictionary A, int groupNum);
void displayDict(Dictionary A);
int isMember(Dictionary A, int num);
void deleteMember(Dictionary *A, int num);


int main(){
    Dictionary A;
    initDict(&A);
    insertElem(&A, 56);
    insertElem(&A, 16);
    insertElem(&A, 36);
    insertElem(&A, 46);
    displayDict(A);


    
    return 0;
}

int hash(int num){
    
    return (num % MAX); //categorizing by tens place, since MAX = 10
}

void initDict(Dictionary *A){
    int i = 0;
    
    while(i < MAX){
        (*A)[i] = NULL;
        i++;
    }
    
}

void insertElem(Dictionary *A, int Elem) {
    LIST *current;
    
    current = &((*A)[hash(Elem)]);
    
    while ((*current) != NULL) {
        current = &((*current)->link); // Updated while loop to correctly move the current pointer to the next node in the linked list

    }
    
    LIST newNode = malloc(sizeof(struct node));
    (*current) = newNode;
    (*current)->data = Elem;
    (*current)->link = NULL;
    
}



void displayHashGroup(Dictionary A, int groupNum){
    LIST *current;
    current = &(A[groupNum]);
    
    printf("[%d] =>", groupNum);
    while((*current) != NULL){
        printf(" %d", (*current)->data);
        
            if((*current)->link == NULL){
                
            }else{
                printf(" =>");
            }
            
        current = &((*current)->link); // Updated while loop to correctly move the current pointer to the next node in the linked list

    }
    printf("\n");
}

void displayDict(Dictionary A){
    int i = 0;
    
    while (i < MAX){
        displayHashGroup(A, i);
        i++;
    }
}

int isMember(Dictionary A, int Num) {
    LIST *current;
    int val = 0;
    
    current = &(A[hash(Num)]);
    
    while ((*current) != NULL ) {
        if((*current)->data == Num){
            val = 1;
        }
        current = &((*current)->link); // Updated while loop to correctly move the current pointer to the next node in the linked list
    }
    
    val == 1 ? printf("\n%d is a Member!\n", Num) : printf("\n%d is NOT a Member!\n", Num);
    
    return val;
}

void deleteMember (Dictionary *A, int num){
    LIST *current;
    current = &((*A)[hash(num)]);
    
    if(!isMember(*A, num)){
    	//
	}else{
	    while ((*current) != NULL && (*current)->data != num) {
        current = &((*current)->link); // Updated while loop to correctly move the current pointer to the next node in the linked list
    	}
    }	
	
	if((*current) != NULL){
		LIST temp = (*current);
		(*current) = temp->link;
		free(temp);
	} //yeah figure this out tomorrow dumbass
    
}
