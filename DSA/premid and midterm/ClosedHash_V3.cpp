#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 13 //10 prime elements
#define SYN (int)(MAX * 0.8) //synonym area
#define DELETED '$'
#define EMPTY '?'
#define SYN_DATA '#' //synonym data

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

//----------------------------------

int main(){
	//use words starting: A, B, C, D, E, F, G, H, I, J (10 prime elements)
	
    Dictionary A;
    initDictionary(&A);
    insertElem(&A, 'B');
    insertElem(&A, 'B');
	insertElem(&A, 'B');
    showDictionary(A);
    

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
	if(A->array[hash(Elem)].data == EMPTY || A->array[hash(Elem)].data == DELETED){
		A->array[hash(Elem)].data = Elem;
	}else{
		A->array[A->avail].data = Elem;
		A->array[hash(Elem)].link = A->avail;
		A->avail = A->array[A->avail].link;
		A->array[A->avail].link = -1;

	}
}

void showDictionary(Dictionary A){
    int i;

    printf("PRIME DATA\nNDX\tDATA\tLINK\n");
    for(i = 0; i < SYN; i++){
		printf("%d\t%c\t%d\n", i, A.array[i].data, A.array[i].link);
    }
    printf("\nSYNONYM\n");
    while(i < MAX){ 
		printf("%d\t%c\t%d\n", i, A.array[i].data, A.array[i].link);
		i++;
    }
    
}
