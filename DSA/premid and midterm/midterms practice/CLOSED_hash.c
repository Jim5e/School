#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string.h>
#define MAX 13
#define DELETED '!'
#define EMPTY '?'
#define SYN_data '@'
#define SYN_area (int) (MAX * (0.8))

typedef struct node{
    char data;
    int link;
    
}cursorbase;

typedef struct{
    cursorbase array[MAX];
    int avail;
    
}Dictionary;

void initDictionary(Dictionary *A);
int hash(char elem);
void insertDictionary(Dictionary *A, char elem);
void deleteElem(Dictionary *A, char elem);
int isMember(Dictionary A, char elem);
void showDictionary(Dictionary A);

int main(){
        Dictionary A;
        initDictionary(&A);
        insertDictionary(&A, 'D');
        insertDictionary(&A, 'b');
        insertDictionary(&A, 'N');
    	showDictionary(A);
    return 0;
}

void initDictionary(Dictionary *A){
    int i = 0;
    
    while(i < SYN_area){
        A->array[i].data = EMPTY;
        A->array[i].link = -1;
        i++;
    }

    while(i < MAX - 1){
        A->array[i].data = SYN_data;
        A->array[i].link = i + 1;
        i++;
    }
    
    A->array[i].data = SYN_data;
    A->array[i].link = -1;
    
    A->avail = SYN_area;
}

int hash(char elem){return (elem % SYN_area);}

void insertDictionary(Dictionary *A, char elem){
    int hashNdx = hash(elem);
    
    if(isMember(*A, elem)){
    	printf("NO DUPLICATES\n");
	}else{
    if(A->array[hashNdx].data == DELETED || A->array[hashNdx].data == EMPTY){
        A->array[hashNdx].data = elem;
    }else{
        int avail = A->avail;
        int temp;
        
        A->array[avail].data = elem;
        temp = A->array[hashNdx].link;
        A->array[hashNdx].link = avail;
        A->array[avail].link = temp;
        A->avail += 1;
        
    }
	}
}

void deleteElem(Dictionary *A, char elem){
    int hashNdx = hash(elem);
    
    if(!isMember(*A, elem)){
    	printf("%c DOES NOT EXIST\n", elem);
	}else{
    if(A->array[hashNdx].data == elem){
        A->array[hashNdx].data = DELETED;
    }else{
        //locate
        int *trav = &A->array[hashNdx].link;
        
        while(A->array[*trav].data != elem){
          trav = &(A->array[*trav].link);
          }
         
            if(A->array[*trav].data == elem ){
             int temp  = *trav;
             *trav = A->array[temp].link;
             A->array[temp].link = A->avail;
             A->avail = temp;
            }
    }
	}
}

int isMember(Dictionary A, char elem){
	int hashNdx = hash(elem), retval = 0;
	
	int trav = A.array[hashNdx].link;
	
	if(A.array[hashNdx].data == elem){
		retval = 1;
	}else{
		//locate
		while(trav != -1){
			if(A.array[trav].data == elem){
				retval = 1;
			}
			trav = A.array[trav].link;
		}
	}
	
	return retval;
}

void showDictionary(Dictionary A){
    int i;

    printf("PRIME DATA\nNDX\tDATA\tLINK\t\tAvail: [%d]\n",A.avail);
    for(i = 0; i < SYN_area; i++){
        printf("%d\t%c\t%d\n", i, A.array[i].data, A.array[i].link);
    }
    printf("\nSYNONYM\n");
    while(i < MAX){ 
        printf("%d\t%c\t%d\n", i, A.array[i].data, A.array[i].link);
        i++;
    }
    
}
