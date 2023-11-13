#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10

typedef struct node{
    char data;
    struct node* link;
    
}*SET;

void insertLast(SET *A, char data);
void populateLL(SET *set, char *value);
void displaySet(SET set);
SET *UNION(SET *A, SET *B);
SET *Intersection(SET *A, SET *B);
SET *Difference(SET *A, SET *B);

int main(void){
    SET A = NULL;
    SET B = NULL;
    
    char listA[] = {"abcdefgh"}; 
    char listB[] = {"defghijkl"};
    
    printf("Initial Sets: \n");
    populateLL(&A, listA);
    populateLL(&B, listB);
    displaySet(A);
    displaySet(B);
    
    printf("-------------------------------OPERATIONS----------------------------------\n\n");
    
    printf("Union of A and B Sets: \n");
    SET *X = UNION(&A, &B);
    displaySet(*X);
    
    printf("Intersection of A and B Sets: \n");
    SET *Y = Intersection(&A, &B);
    displaySet(*Y);
    
    printf("Set Difference of A and B Sets: \n");
    SET *Z = Difference(&A, &B);
    displaySet(*Z);
    
    return 0;
}

SET *UNION(SET *A, SET *B){
    SET *C = (SET*)malloc(sizeof(struct node)); // Allocate memory for C
    *C = NULL;
    SET Aptr, Bptr;
    Aptr = *A;
    Bptr = *B;

    while(Aptr != NULL && Bptr!= NULL){
        if(Aptr->data == Bptr->data){ //if same both, copy A to C, then move both ptrs
            insertLast(C, Aptr->data);
            Aptr = Aptr->link;
            Bptr = Bptr->link;
        }else if(Aptr->data < Bptr->data){ //if A less than B, copy A to C, move A
            insertLast(C, Aptr->data);
            Aptr = Aptr->link;
        }else{//if B less than A, copy B to C, move B
            insertLast(C, Bptr->data);
            Bptr = Bptr->link;
        }
        
        if(Aptr == NULL){
            Aptr = Bptr;
        }
        if(Bptr == NULL){
            Bptr = Aptr;
        }        
    }

    return C;
}

SET *Intersection(SET *A, SET *B){
    SET *C = (SET*)malloc(sizeof(struct node)); // Allocate memory for C
    *C = NULL;
    SET Aptr, Bptr;
    Aptr = *A;
    Bptr = *B;

    while(Aptr != NULL && Bptr != NULL){
        if(Aptr->data == Bptr->data){ //if same both, copy A to C, then move both ptrs
            insertLast(C, Aptr->data);
            Aptr = Aptr->link;
            Bptr = Bptr->link;
        }else if(Aptr->data < Bptr->data){ //if A less than B, move A
            Aptr = Aptr->link;
        }else{//if B less than A, move B
            Bptr = Bptr->link;
        }
    }

    return C;
}

SET *Difference(SET *A, SET *B){ //we use B as the basis in comparing, NOT A
    SET *resultSet = (SET*)malloc(sizeof(struct node)); // Allocate memory for resultSet
    *resultSet = NULL;
    SET Aptr, Bptr;
    Aptr = *A;
    Bptr = *B;

    while(Aptr != NULL){ //run through a
        while(Bptr != NULL && Bptr->data < Aptr->data){ //use B as the basis for checking, if B is < than A then that means A is not in B, ready to sent to resultSet
            Bptr = Bptr->link;
        }
        if(Bptr == NULL || Bptr->data != Aptr->data){ //if A val is not equal to Bptrs, that means it doenst get minused, and transfer to resultSet
            insertLast(resultSet, Aptr->data);
        }
        Aptr = Aptr->link;
    }

    return resultSet;
}


void populateLL(SET *A, char *value) {
    int len = strlen(value); //access teh eend
    SET newNode = NULL;
    int i;

    for (i = len - 1; i >= 0; i--) { // we can reach the end of the string by use of strlen
        newNode = (SET)malloc(sizeof(struct node));

        if (newNode != NULL) {
            newNode->data = value[i];
            newNode->link = *A; // Set the link to the current head of the list
            *A = newNode; // Update the head of the list to the new node
        }
    }
}

void displaySet(SET set){
    SET current;
    current = set;
    
    printf("SET: ");
    while(current != NULL){
        printf("%c", current->data);
        current = current->link;
    }
    
    printf("\n");
}

void insertLast(SET *A, char data){
    SET newNode = (SET ) malloc (sizeof(struct node));
    newNode->data = data;
    newNode->link = NULL;
    
    if(*A == NULL){
        *A = newNode;
    }else{
        SET current = *A;
        
        while(current->link != NULL){
        current = current->link;
        }
        
        current->link = newNode;
    }
}

