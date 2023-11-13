#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10


typedef struct{
    char data;
    int link;    
    
}Bag;

typedef struct{
    Bag Nodes[MAX];
    int avail;
    
}VirtualHeap;

void initVH(VirtualHeap *A); //using version 1
void populateVH(VirtualHeap *A); //hard coded values so it seems more "natural", i.e. theres gaps between datas
void displayVH(VirtualHeap A);
int allocSpace(VirtualHeap *A);
void deallocSpace(VirtualHeap *A, int index);
void insertFirst(VirtualHeap *A, char newElem);
void updateAvail(VirtualHeap *A);

int main(){
    VirtualHeap L;
    
    //setup calls
    initVH(&L);
    populateVH(&L); //initial jumbles list is "[G][][O][O][][D][][B][O][Y]" (nay spaces)
    printf("The VH is currently: \n");
    displayVH(L);
    
    //managing calls
//    allocSpace(&L); //confused about what this does with regards to the elements tbh if like it just deletes the thing or what limot nako || ask pena
//    deallocSpace(&L, 3); //confused about this also, like mu delete sad ni?? ask mam pena
	insertFirst(&L, 'J'); //the next four lines is to show that despite the gaps of elements, the newElem gets inserted at the first available cell (cell which is NULL) AND avail gets updated properly (accounting for the gaps)
	displayVH(L);
	insertFirst(&L, 'K'); 
	insertFirst(&L, 'R'); 
	displayVH(L);

    
    //**notes: i assume if given kay a jumbled list (.link is not consecutive), traversal would be by A->Nodes[A->Nodes[X].link] ?? or something like that di ko sure, but it def wouldnt be by [1][2][3][...]
    return 0;
}

void initVH(VirtualHeap *A){ //this is version1 btw
    int i;
    
    //set avail to index 0 since its the first available
    A->avail = 0;
    
    for(i = A->avail ; i < MAX - 1 ; i++){ //this for loop STOPS right before the LAST node. (since the last node needs to be -1 and not whatever i currently is)
        A->Nodes[i].data = NULL;
        A->Nodes[i].link = i + 1; 
    }
    
    A->Nodes[i].data = NULL;
    A->Nodes[i].link = -1;

}

void populateVH(VirtualHeap *A){
    
    //MAX = 10
    A->avail = 1;
    A->Nodes[0].data = 'G';
    A->Nodes[2].data = 'O';
    A->Nodes[3].data = 'O';
    A->Nodes[5].data = 'D';
    A->Nodes[7].data = 'B';
    A->Nodes[8].data = 'O';
    A->Nodes[9].data = 'Y';
    
}

void displayVH(VirtualHeap A){
	int i;
	
	printf("Avail = [%d]\n", A.avail);
	printf("INDEX\tDATA\tLINK\n");
	
	for(i = 0; i < MAX; i++ ){
		printf("%d\t%c\t%d\n", i, A.Nodes[i].data, A.Nodes[i].link);
		
	}
	
}

int allocSpace(VirtualHeap *A){
	int retval = -1;
	
	if (A->avail != -1){
		retval = A->avail;
		A->avail = A->Nodes[A->avail].link;
	}
	
	return retval;
}

void deallocSpace(VirtualHeap *A, int index){
	
	if(index >= 0 && index <= MAX){ //checks if index is within the range of the nodes, kay basig ang index imo e hatag wasad sa lista ba
		A->Nodes[index].link = A->avail;
		A->avail = index;
	}

}

void insertFirst(VirtualHeap *A, char newElem){
	int i;
	
	if(A->avail != -1){
		A->Nodes[A->avail].data = newElem;
		updateAvail(A);
	}else{
		//something here to allocate more space? unsure yet
	}
	
}

void updateAvail(VirtualHeap *A){
	int i;
	
	for(i = 0; i < MAX && A->Nodes[i].data != NULL; i++){
	}
	
	if(i >= MAX){ //the loop above checks the nearest empty cell, if i >= MAX then that means all cells are occupied so -1
		A->avail = -1;
	}else{	// if there is space, then the loop above stops i at the nearest empty cell
		A->avail = i;	
	}

}

