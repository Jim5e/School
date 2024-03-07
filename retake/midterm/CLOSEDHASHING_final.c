#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#define EMPTY '@'
#define DELETED '!'

typedef enum {TRUE, FALSE} Boolean; // TRUE = 0, FALSE = 1
typedef char Dictionary[MAX];

void initDic(Dictionary A);
void displayDic(Dictionary A);
int hash(char elem);
Boolean isMember(Dictionary A, char elem);
void insert(Dictionary A, char elem);
void deleteElem(Dictionary A, char elem);


int main(){
	//1
    Dictionary MAIN;
    initDic(MAIN);
    
    //2
    char values[] = {'a','b','c','d','e','f'};
    int x = 0;
    while(x < sizeof(values)){
    	insert(MAIN, values[x]);
    	x++;
	}
	
	//3, call isMember() twice, 1.) Elem is found, 2.) Elem is not found
	printf("%d\n", isMember(MAIN,'c'));
	printf("%d\n", isMember(MAIN,'g'));
    
    //4, call deleteElem() twice, 1.) Elem exists, 2.) Elem does not exist
//    deleteElem(MAIN, 'c');
//    deleteElem(MAIN, 'f');

    
	displayDic(MAIN);

//	printf("%d", (0-3 ) % 10);
    return 0;
}

int hash(char elem){
    char characters[] = {'a', 'b', 'c', 'd', 'e','f', 'g', 'h', 'i', 'j', 'x', 'r'};
    int values[] = {3,9,4,3,9,0,1,3,0,3, 8, 9};
    int i;
    for(i = 0; i < sizeof(values)/4 && characters[i] != elem; i++){}
    return values[i];
}

void insert(Dictionary A, char elem) {
    int ndx = hash(elem);
    int comparisons;
    int relativeNDX;
    int flag = 999;
    
    for (comparisons = 0, relativeNDX = ndx; comparisons < MAX && A[relativeNDX] != elem; relativeNDX = (relativeNDX + 1) % MAX) {
        if (flag == 999 && (A[relativeNDX] == EMPTY || A[relativeNDX] == DELETED)) {
			flag = relativeNDX;
        }
        comparisons++;
    }
    
    if(comparisons == MAX){
    	A[flag] = elem;
	}

}


void deleteElem(Dictionary A, char elem){
	int ndx = hash(elem);
	int comparisons;
	
	for(comparisons = 0; comparisons < MAX && A[ndx] != elem;  ndx = (ndx + 1) % MAX, comparisons++){
	}
	
	if(A[ndx] == elem){
		A[ndx] = DELETED;
	}
}

Boolean isMember(Dictionary A, char elem){
	int ndx = hash(elem);
	int cmp;
	
	for(cmp = 0; A[ndx] != EMPTY && cmp < MAX && A[ndx] != elem; ndx = (ndx + 1) % MAX, cmp++){}
	
	return A[ndx] == elem ? TRUE: FALSE;
}

void displayDic(Dictionary A){
	printf("INDEX\tELEMENTS\n");
	int x;
	
	for(x = 0; x < MAX; x++){
        if(A[x] == EMPTY){
            printf("%d\t\tEMPTY\n", x);
        }else if(A[x] == DELETED){
            printf("%d\t\tDELETED\n", x);
        }else{
          printf("%d\t\t%c\n", x, A[x]);  
        }
	}
}

void initDic(Dictionary A){
    int x;
    for(x = 0; x < MAX; x++){
        A[x] = EMPTY;
    }
}
