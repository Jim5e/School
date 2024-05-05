#include <stdio.h>
#include <stdlib.h>
#define MAX 10

//DS needed in dijkstras are: SET, ARRAY, 2d ARRAY
#define GSIZE 5
#define INF 9999

typedef int SET[GSIZE]; // Bit-vector implementation of SET
typedef int Graph[GSIZE][GSIZE]; // 2D array
typedef int Vertex; // Chosen vertex
typedef int distances[GSIZE]; // Distances from the chosen vertex to all
distances *dijkstras(Graph A, Vertex V);
void displayArray(int array[]);
void displayMatrix(int array[][GSIZE]);
Graph *floyd(Graph A);

int main (){
    //examples
//    Graph MAIN = {{0, 10, 4, 15},
//                {INF, 0, 6, 2},
//                {INF, INF, 0, INF},
//                {INF, INF, 7, 0}};
//                
	// Graph MAIN = {
    //     {INF, INF, INF, INF, INF, INF, INF, INF},
    //     {INF, INF, 5, 9, INF, INF, 1, INF},
    //     {INF, 5, INF, INF, 2, INF, INF, INF},
    //     {INF, 9, INF, INF, INF, 6, INF, INF},
    //     {INF, INF, 2, INF, INF, INF, 8, INF},
    //     {INF, INF, INF, 6, INF, INF, 1, INF},
    //     {INF, 1, INF, INF, 8, 1, INF, 5},
    //     {INF, INF, INF, INF, INF, INF, 5, INF}
    // };
    Graph MAIN =      { { 0, 4, INF, 5, INF},
                        { INF, 0, 1, INF, 6},
                        { 2, INF, 0, 3, INF},
                        { INF, INF, 1, 0, 2},
                        { 1, INF, INF, 4, 0},
                         };
                         
//Graph MAIN = {
//    {INF, 3, INF, 5},
//    {2, INF, INF, 8},
//    {INF, 1, INF, INF},
//    {INF, INF, 2, INF}
//  };           
	
	//returened answers
//    distances *answer = dijkstras(MAIN, 0);
    Graph *matrix = floyd(MAIN);
    
    //display
//    displayArray(*answer);
	displayMatrix(*matrix);
	
    return 0;
}

Graph *floyd(Graph A){
    Graph *retval = (Graph *) malloc(sizeof(Graph));
    if(retval != NULL){
        for(int i = 0; i < GSIZE; i++){
            distances *returnee = dijkstras(A, i);

            for(int index = 0; index < GSIZE; index++){
                (*retval)[i][index] = (*returnee)[index];
            }

            free(returnee);
        }
    }

    return retval;
}

distances *dijkstras(Graph graph, Vertex V){
    //create Set for visitedNodes
    SET visited = {0}; //set all to 0
    visited[V] = 1; //set source vertex as visited

    //init distances array
    distances *distance = (distances *)calloc(GSIZE, sizeof(int));
    int i;
    for(i = 0; i < GSIZE; i++){
        (*distance)[i] = graph[V][i];
    }

    // Find shortest path for all vertices
    int count;
    for(count = 0; count < GSIZE; count++){

        //select a vertex by choosing the minimum in distance array that is unvisited
        int minimumD = 9999;
        int minimumNdx = -1;
        int x;

        for(x = 0; x < GSIZE; x++){
            if(visited[x] != 1 && ((*distance)[x]) < minimumD){
                minimumD = (*distance)[x];
                minimumNdx = x;
            }
        }
        visited[minimumNdx] = 1; //now we have min, set it to vistied

        //using minimum, aim to update the values in distance.
        //do this by: finding an edge that is unvisited, has a connectioned (edge), and when combined is smaller than the current...
        //...distance value in distance
        int index;
        for(index = 0; index < GSIZE; index++){
            if( visited[index] != 1 && //finding an edge that is unvisited,
                // graph[minimumNdx][index] != INF && //has a connectioned (edge),
                // graph[minimumNdx][index] != 0 &&
                minimumD + graph[minimumNdx][index] < (*distance)[index]){ //when combined is smaller than the current dist val in distance
                
                (*distance)[index] = graph[minimumNdx][index] + minimumD;
            }
        }
    }



    return distance;
}

void displayArray(int array[]){
	for(int i = 0; i < GSIZE; i++){
		printf("%d ", array[i]);
		
	}
}

void displayMatrix(int array[][GSIZE]){
	for(int i = 0; i < GSIZE; i++){
		for(int x = 0; x < GSIZE; x++){
			printf("%-5d ", array[i][x]);
		}
		
		printf("\n");
	}
}
