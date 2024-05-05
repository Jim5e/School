#include <stdio.h>
#include <stdlib.h>
#define MAX 10

//DS needed in dijkstras are: SET, ARRAY, 2d ARRAY
#define GSIZE 4
#define INF 9999

typedef int SET[GSIZE]; // Bit-vector implementation of SET
typedef int Graph[GSIZE][GSIZE]; // 2D array
typedef int Vertex; // Chosen vertex
typedef int distances[GSIZE]; // Distances from the chosen vertex to all
void printSolution(int dist[][GSIZE]);
Graph *FloydWarshall(Graph A);


int main(){
    // Graph MAIN =      { { 0, 4, INF, 5, INF},
    //                     { INF, 0, 1, INF, 6},
    //                     { 2, INF, 0, 3, INF},
    //                     { INF, INF, 1, 0, 2},
    //                     { 1, INF, INF, 4, 0},
    //                      };

    Graph MAIN = {
        {INF, 3, INF, 5},
        {2, INF, INF, 8},
        {INF, 1, INF, INF},
        {INF, INF, 2, INF}
    };


    Graph *W = FloydWarshall(MAIN);
    printSolution(*W);

    return 0;
}

void printSolution(int dist[][GSIZE])
{
    printf(
        "The following matrix shows the shortest distances"
        " between every pair of vertices \n");
    for (int i = 0; i < GSIZE; i++) {
        for (int j = 0; j < GSIZE; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}




Graph *FloydWarshall(Graph A){
    Graph *W = (Graph *) malloc (sizeof(Graph));

    //copy data
    for(int i = 0; i < GSIZE; i++){
        for(int k = 0; k < GSIZE;k++){
            (*W)[i][k] = A[i][k];
        }
    }

    //Diagonal
    for(int i = 0; i < GSIZE; i++){
        (*W)[i][i] = 0;
    }

    //3  structure for loop
    for(int k = 0; k < GSIZE; k++){
        for(int row = 0; row < GSIZE; row++){ //i
            for(int col = 0; col < GSIZE; col++){ //j
                if((*W)[row][k] + (*W)[k][col] < (*W)[row][col]){
                    (*W)[row][col] = (*W)[row][k] + (*W)[k][col];
                }
            }
        }
    }

    return W;
}