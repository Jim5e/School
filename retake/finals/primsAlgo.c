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
Graph *Prim(Graph A, Vertex V);


int main(){


    return 0;
}

Graph *Prim(Graph A, Vertex V){
    //
}
