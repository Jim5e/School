#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#define MAX 13 //10 prime elements
#define SYN (int)(MAX * 0.8) //synonym area
#define DELETED '$'
#define EMPTY '?'
#define SYN_DATA '#' //synonym data
#define WORD

typedef struct{
    char data;
    int link;
    
}node;

typedef struct{
    node array[MAX];
    int avail;
}Dictionary;

//----------------------------------
int hash(char elem);
void initDictionary(Dictionary *A);
void insertElem(Dictionary *A, char Elem);
void showDictionary(Dictionary A);
bool isMember(Dictionary *A, char Elem);
void deleteElem(Dictionary *A, char Elem);

//----------------------------------

int main(){
	//use words starting: A, B, C, D, E, F, G, H, I, J (10 prime elements)
	
    Dictionary A;
    initDictionary(&A);
    insertElem(&A, 'B');
    insertElem(&A, 'B');
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

int hash(char elem){
    return (int)((toupper(elem) - 65) % SYN);
}

void insertElem(Dictionary *A, char Elem){
	
	//ADD CHECK MEMBER HERE AFTER DONE WITH EVERYTHING
	if(A->array[hash(Elem)].data == EMPTY || A->array[hash(Elem)].data == DELETED){
		A->array[hash(Elem)].data = Elem;
	}else{
		int oldNdx = A->avail;
		
		if(oldNdx != -1){
		A->array[oldNdx].data = Elem; //add elem to the node
		A->avail = A->array[oldNdx].link; //ensure avail moves by getting the int value from oldNdx.link (you have to or else avail cant get updated due to having no reference to what will be its NEXT link (ma override ang value if not))
		A->array[oldNdx].link = A->array[hash(Elem)].link; //the avail.link connects to the oldnode by using hash.link
		A->array[hash(Elem)].link = oldNdx;	//hash.link can now connect to the newly added element
		}
	}
}

void deleteElem(Dictionary *A, char Elem){
	//ismember check
	if(!isMember(A, Elem)){
		printf("\"%c\" does not exist in the Dictionary.\n", Elem);
	}else{
		if(A->array[hash(Elem)].data == Elem){ //if the desired element is in the prime area
			A->array[hash(Elem)].data = DELETED;
		}else{
			
			//find the index of the deleted node
		int *current = &(A->array[hash(Elem)].link);
		
		while((*current) != -1 && (*current) != A->array[hash(Elem)].data){
			(*current) = A->array[(*current)].link;
			}
			
			//rewire connections
			int deleteNdx = (*current);
			A->avail = A->array[hash(Elem)].link;
			A->array[hash(Elem)].link = deleteNdx;
		}

	}
}

void showDictionary(Dictionary A){
    int i;

    printf("PRIME DATA\nNDX\tDATA\tLINK\t\tAvail: [%d]\n",A.avail);
    for(i = 0; i < SYN; i++){
		printf("%d\t%c\t%d\n", i, A.array[i].data, A.array[i].link);
    }
    printf("\nSYNONYM\n");
    while(i < MAX){ 
		printf("%d\t%c\t%d\n", i, A.array[i].data, A.array[i].link);
		i++;
    }
    
}

bool isMember(Dictionary *A, char Elem){
    bool result = false;
    int ndx = hash(Elem);
    
    do {
      if(A->array[ndx].data == Elem){
            result = true;
        }
        ndx = A->array[ndx].link;
        
    }while(A->array[ndx].link != -1 && A->array[ndx].data != EMPTY);
    
    return result;
}
