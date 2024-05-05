#include <stdlib.h>
#include <stdio.h>
#define GSIZE 4
#define INF 9999


typedef enum {FALSE, TRUE} Boolean; // TRUE = 1, FALSE = 0
typedef int Graph[GSIZE][GSIZE];
typedef Boolean BoolGraph[GSIZE][GSIZE];


BoolGraph *warshall(Graph G);
void displayMatrix(BoolGraph array);

int main(){
    Graph MAIN = {{1, 1, 0, 1},
                {0, 1, 1, 0},
                {0, 0, 1, 1},
                {0, 0, 0, 1}
                };
    
    BoolGraph *B = warshall(MAIN);
    	displayMatrix(*B);

    return 0;
}

BoolGraph *warshall(Graph G){
    BoolGraph *ptr = (BoolGraph *)malloc(sizeof(BoolGraph));
    int i, j, k;

    //copy initial data to boolG from Graph
    for(i = 0; i < GSIZE; i++){
        for(j = 0; j < GSIZE; j++){
            (*ptr)[i][j] = (G[i][j] > 0 && G[i][j] < INF) ? 1: 0; //for non boolean data
            // (*ptr)[i][j] = G[i][j]; //boolean data
        }
    }

    for(k = 0; k < GSIZE; k++){
        for(i = 0; i < GSIZE; i++){
            for(j = 0; j < GSIZE; j++){
                (*ptr)[i][j] = (*ptr)[i][j] || ((*ptr)[i][k] && (*ptr)[k][j]); //geeks for geeks

                // if((*ptr)[i][j] == 0){ //xander
                //     (*ptr)[i][j] = ((*ptr)[i][k] == 0 && (*ptr)[k][j] == 0) ? 1: 0;
                // }

                // if((*ptr)[i][j] == 0) //saidus
                // {
                //     (*ptr)[i][j] = (*ptr)[i][k] && (*ptr)[k][j];
                // }
            }
        }
    }

    return ptr;
}

void displayMatrix(BoolGraph array){
    int i, j;
	for(i = 0; i < GSIZE; i++){
		for(x = 0; x < GSIZE; x++){
			printf("%-5d ", array[i][x]);
		}
		
		printf("\n");
	}
}
