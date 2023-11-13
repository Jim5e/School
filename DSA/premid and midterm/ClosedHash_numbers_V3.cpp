#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#define MAX 13 //10 prime elements
#define SYN (int)(MAX * 0.8) //synonym area
#define DELETED 666
#define EMPTY 0
#define SYN_DATA 999 //synonym data
#define WORD 6

typedef struct{
    int data;
    int link;
    
}node;

typedef struct{
    node array[MAX];
    int avail;
}Dictionary;

//----------------------------------
int hash(int elem);
void initDictionary(Dictionary *A);
void insertElem(Dictionary *A, int Elem);
void showDictionary(Dictionary A);
bool isMember(Dictionary *A, int Elem);
void deleteElem(Dictionary *A, int Elem);

//----------------------------------

int main(){
    Dictionary A;
    initDictionary(&A);
    insertElem(&A, 1);
    insertElem(&A, 111);
    insertElem(&A, 121);

//	deleteElem(&A, 111);
	
//    showDictionary(A);
    deleteElem(&A, 121);
    showDictionary(A);
    
    return 0;
}

void initDictionary(Dictionary *A){
    int i;
    
    for(i = 0; i < SYN; i++){
        A->array[i].data = EMPTY;
        A->array[i].link = -1;
    }
    
    while(i < MAX - 1){ 
        A->array[i].data = SYN_DATA;
        A->array[i].link = i+1; //make everything connect
        i++; 
    }
    
    A->avail = SYN;
    A->array[i].data = SYN_DATA;
    A->array[i].link = -1;
}

int hash(int elem){
    return ((elem % 10) % SYN);
}

void insertElem(Dictionary *A, int Elem){
	if(isMember(A, Elem)){
        printf("Duplicates are not allowed.\n", Elem);
        
	}else{	
	    if(A->array[hash(Elem)].data == EMPTY || A->array[hash(Elem)].data == DELETED){
        A->array[hash(Elem)].data = Elem;
    	}else{
        int oldNdx = A->avail;
        
        if(oldNdx != -1){
            A->array[oldNdx].data = Elem; //add elem to the node
            A->avail = A->array[oldNdx].link; //ensure avail moves by getting the int value from oldNdx.link (you have to or else avail cant get updated due to having no reference to what will be its NEXT link (ma override ang value if not))
            A->array[oldNdx].link = A->array[hash(Elem)].link; //the avail.link connects to the oldnode by using hash.link
            A->array[hash(Elem)].link = oldNdx;    //hash.link can now connect to the newly added element
        }
    	}		
	}
}

void deleteElem(Dictionary *A, int Elem){
    if(!isMember(A, Elem)){
        printf("\"%d\" does not exist in the Dictionary.\n", Elem);
    }else{
        if(A->array[hash(Elem)].data == Elem){ //if the desired element is in the prime area
            A->array[hash(Elem)].data = DELETED;
        }else{
            int *current = &(A->array[hash(Elem)].link);
        	
            while(A->array[(*current)].data != Elem){ //find deleted index
                current = &A->array[(*current)].link;
            }
            
//            printf("%d\n", *current);
//			A->array[*current].data = DELETED;
//			A->avail = *current;
//			A->array[hash(Elem)].link = A->array[*current].link;
			
			if(A->array[*current].data == Elem ){
         	int temp = *current;
            *current = A->array[*current].link;
            A->array[temp].link = A->avail;
            A->avail = temp;				
			}
        }
    }
}

void showDictionary(Dictionary A){
    int i;

    printf("PRIME DATA\nNDX\tDATA\tLINK\t\tAvail: [%d]\n",A.avail);
    for(i = 0; i < SYN; i++){
        printf("%d\t%d\t%d\n", i, A.array[i].data, A.array[i].link);
    }
    printf("\nSYNONYM\n");
    while(i < MAX){ 
        printf("%d\t%d\t%d\n", i, A.array[i].data, A.array[i].link);
        i++;
    }
    
}

bool isMember(Dictionary *A, int Elem){
    bool result = false;
    int ndx = hash(Elem);
    
    do {
      if(A->array[ndx].data == Elem){
            result = true;
        }
        ndx = A->array[ndx].link;
        
    }while(ndx != -1 && A->array[ndx].data != EMPTY); //?? what
    
    return result;
}


