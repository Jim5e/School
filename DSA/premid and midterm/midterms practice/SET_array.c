#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 10

typedef char collection;

typedef struct node{
    collection *elem;
    int count;
    int size;
    
}*SETptr, SET;

void initSet(SETptr *A);
SET *UNION(SETptr *A, SETptr *B);
void resize (SETptr *A);
SET *INTERSECTION(SETptr *A, SETptr *B);
SET *DIFFERENCE(SETptr *A, SETptr *B);
int isMember(SETptr A, collection Elem);
void deleteElem(SETptr *A, collection Elem);
void insertElem(SETptr *A, collection Elem);
void displaySet(SETptr A);

int main() {
    SETptr A,B;
    initSet(&A);
    initSet(&B);
    strcpy(A->elem, "abdefgh");
    A->count = strlen(A->elem);
    strcpy(B->elem, "defghijkl");
    B->count = strlen(B->elem);
	
	printf("Initial Sets:\n");
	displaySet(A);
	displaySet(B);
	
	//functionality
//	deleteElem(&A, 'd');
//	insertElem(&A, 'c');
//	//

	printf("-------------------------------OPERATIONS----------------------------------\n\n");
	printf("Union of A and B Sets: \n");
	SETptr X = UNION(&A, &B);
	displaySet(X);
	
	printf("Intersection of A and B Sets: \n");
	SETptr Y = INTERSECTION(&A, &B);
	displaySet(Y);
	
	printf("Set Difference of A and B Sets: \n");
	SETptr Z = DIFFERENCE(&A, &B);
	displaySet(Z);
	
	return 0;
}


void initSet(SETptr *A){
  (*A) = (SETptr ) malloc (sizeof(SET));
  (*A)->count = 0;
  (*A)->size = SIZE;
  (*A)->elem = (collection *) malloc (sizeof(char) * SIZE);
}

SET *UNION(SETptr *A, SETptr *B){
    SETptr C;
    initSet(&C);
    int aNdx = 0;
    int bNdx = 0;
    int cNdx = 0;
    
    //compare
    while((*A)->elem[aNdx] != '\0' && (*B)->elem[bNdx] != '\0'){
        if(C->count == C->size){
          resize(&C);
        }
        
        if((*A)->elem[aNdx] < (*B)->elem[bNdx]){
            C->elem[cNdx] = (*A)->elem[aNdx];
            aNdx++;
        }else if((*B)->elem[bNdx] < (*A)->elem[aNdx]){
            C->elem[cNdx] = (*B)->elem[bNdx];
            bNdx++;            
        }else{
            C->elem[cNdx] = (*A)->elem[aNdx];
            aNdx++;
            bNdx++;
        }
        
        C->count++;
        cNdx++;
    }
    
    if((*A)->elem[aNdx] == '\0'){
        while((*B)->elem[bNdx] != '\0'){
            if(C->count == C->size){
              resize(&C);
               }  
               
            C->elem[cNdx] = (*B)->elem[bNdx];
            cNdx++;
            C->count++;
            bNdx++;                
        }
    }
    
    if((*B)->elem[bNdx] == '\0'){
        while((*A)->elem[aNdx] != '\0'){
            if(C->count == C->size){
              resize(&C);
               }  
               
            C->elem[cNdx] = (*A)->elem[aNdx];
            cNdx++;
            C->count++;
            aNdx++;                
        }        
    }    
    
    C->elem = (collection *) realloc (C->elem, sizeof(char) * C->count);
    
    return C;
}

void resize (SETptr *C){
        (*C)->size = ((*C)->size * 1.5);
        (*C)->elem = (collection *) realloc ((*C)->elem, sizeof(char) * (*C)->size);
}

SET *INTERSECTION(SETptr *A, SETptr *B){
    SETptr C;
    initSet(&C);
    int aNdx = 0;
    int bNdx = 0;
    int cNdx = 0;
    
    //compare
    while((*A)->elem[aNdx] != '\0' && (*B)->elem[bNdx] != '\0'){
        if(C->count == C->size){
          resize(&C);
        }
        
        if((*A)->elem[aNdx] < (*B)->elem[bNdx]){
            aNdx++;
        }else if((*B)->elem[bNdx] < (*A)->elem[aNdx]){
            bNdx++;            
        }else{
            C->elem[cNdx] = (*A)->elem[aNdx];
            aNdx++;
            bNdx++;
            C->count++;
            cNdx++;
        }

    }  
    
    C->elem = (collection *) realloc (C->elem, sizeof(char) * C->count);
    
    return C;
}

//SET *DIFFERENCE(SETptr *A, SETptr *B){
//    SETptr C;
//    initSet(&C);
//    int aNdx = 0;
//    int bNdx = 0;
//    int cNdx = 0;	
//	
//    while((*A)->elem[aNdx] != '\0' && (*B)->elem[bNdx] != '\0'){
//    	if((*A)->elem[aNdx] == (*B)->elem[bNdx]){
//    	    aNdx++;
//            bNdx++;	
//		}else if((*A)->elem[aNdx] < (*B)->elem[bNdx]){
//			C->elem[cNdx] = (*A)->elem[aNdx];
//            C->count++;
//            cNdx++;
//			aNdx++;		
//		}else if((*A)->elem[aNdx] > (*B)->elem[bNdx]){
//			bNdx++;
//		}
//		
//		if((*B)->elem[bNdx] == '\0'){
//			while((*A)->elem[aNdx] != '\0'){
//				C->elem[cNdx] = (*A)->elem[aNdx];
//				C->count++;
//				cNdx++;
//				aNdx++;					
//			}
//
//		}
//	}	
//    C->elem = (collection *) realloc (C->elem, sizeof(char) * C->count);
//    
//    return C;	
//	
//}

SET *DIFFERENCE(SETptr *A, SETptr *B){
    SETptr C;
    initSet(&C);
    int aNdx = 0;
    int bNdx = 0;
    int cNdx = 0;	
	
    while((*A)->elem[aNdx] != '\0'){
		if((*B)->elem[bNdx] != '\0' &&  (*A)->elem[aNdx] < (*B)->elem[bNdx]){
			insertElem(&C, (*A)->elem[aNdx]);
			aNdx++;
		}else if((*B)->elem[bNdx] < (*A)->elem[aNdx]){
			bNdx++;
		}else{
			aNdx++;
			bNdx++;
		}
	}	
	
    C->elem = (collection *) realloc (C->elem, sizeof(char) * C->count);
    
    return C;	
	
}

void displaySet(SETptr A){
	int i;
	
	for(i = 0; i < A->count;i++){
		printf("%c ", A->elem[i]);
	}
	printf("\n\n");
}

void deleteElem(SETptr *A, collection Elem){
    if(isMember((*A), Elem) == 0){
        printf("Member does not exist.\n");
    }else{
        //find elem
        int i;
        for(i = 0; (*A)->elem[i] != Elem; i++){}
        int elemNdx = i;
        
        int r = elemNdx;
        while(r < (*A)->count){
            (*A)->elem[r] = (*A)->elem[r + 1];
            r++;
        }
        
        (*A)->count--;
    }
}

void insertElem(SETptr *A, collection Elem){
    if(isMember((*A), Elem)){
        printf("Member exists => Set cannot have duplicates\n");
    }else{
        int i = 0, elemNdx = -1, r;  
        
        //resize checker
        if((*A)->count == (*A)->size){
            resize(&(*A));
        }
        
        //find elem
        for (i = 0; i < (*A)->count && Elem > (*A)->elem[i] ; i++) {}
        elemNdx = i;
        
        //transfer
        for(r = (*A)->count + 1 ; r > elemNdx; r--){
            (*A)->elem[r] = (*A)->elem[r - 1];
        }
        
        (*A)->elem[elemNdx] = Elem;
        (*A)->count++;
    }
}

int isMember(SETptr A, collection Elem){
    int retval = 0, i = 0;
    
    while(i < A->count){
        if(A->elem[i] == Elem){
            retval = 1;
        }
        i++;
    }
    
    return retval;
}



