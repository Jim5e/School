#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct node{
    int elem;
    struct node *link = NULL;
} *SET;

typedef enum{TRUE,FALSE} Boolean;
typedef SET Dictionary[MAX];

void initDictionary(Dictionary A);
void displayDictionary(Dictionary A);
int hash(int elem);
void insert(Dictionary A, int elem);
void deleteElem(Dictionary A, int elem);
Boolean isMember(Dictionary A, int elem);

int main(){
    Dictionary MAIN;
    // initDictionary(MAIN);
    int given[] = {0, 13, 20, 28, 30, 33, 45, 48, 108};
    
    int i;
    for(i = 0; i < sizeof(given) / 4; i++){
    	insert(MAIN, given[i]);
	}
	
	deleteElem(MAIN, 20);
	deleteElem(MAIN, 20); //non existent
    
    displayDictionary(MAIN);
    return 0;
}

void insert(Dictionary A, int elem){
	int ndx = hash(elem);
	SET *trav;
	
	for(trav = &A[ndx]; *trav != NULL && (*trav)->elem < elem; trav = trav = &(*trav)->link){
	}
	
	if(*trav == NULL || (*trav)->elem != elem){
		SET newNode = (SET) malloc (sizeof(struct node));
		if(newNode != NULL){
			newNode->elem = elem;
			newNode->link = *trav;
			*trav = newNode;				
		}			
	}	
}

void deleteElem(Dictionary A, int elem){
	int ndx = hash(elem);
	SET *trav;
	for(trav = &A[ndx]; *trav != NULL && (*trav)->elem != elem; trav = &(*trav)->link){
	}
	
	if(*trav != NULL){
		SET temp = *trav;
		*trav = temp->link;
		free(temp);
	}else{
		printf("%d DOES NOT EXIST\n\n", elem);
	}
}

void initDictionary(Dictionary A){
	int i;
    for(i= 0 ; i < MAX; i++){
        A[i] = NULL;
    }
}

void displayDictionary(Dictionary A){
    printf("SET #\tELements\n");
    int i;
    for(i = 0; i < MAX; i++){
        printf("%d   -->\t", i);
        SET trav = A[i];
        
        if(trav == NULL){
        	printf("EMPTY");
		}
	    for(; trav != NULL; trav = trav->link){
	          printf("[%d] ", trav->elem);
		}
		
        printf("\n");
    }
}

int hash(int elem){
	return elem % 10;
}

Boolean isMember(Dictionary A, int elem){
	int ndx = hash(elem);
	SET trav;
	for(trav = A[ndx]; trav != NULL && trav->elem != elem; trav = trav->link){
	}
	
	return trav != NULL ? TRUE : FALSE;
}
