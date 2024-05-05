#include <stdio.h>
#include <stdlib.h>
#define SENTINEL 999
#define MAX_VERTEX 10
#define ARRAY_SIZE 0X2D

typedef struct{
    int u, v; //vertices representing the edge
    int weight; //edge weight

}edgetype;


typedef struct node{
    edgetype edges[ARRAY_SIZE];
    int lastEdge; //index of last existing edge, -1 if empty
}*edgelist;

typedef int adjMatrix[MAX_VERTEX][MAX_VERTEX];


edgelist createEdgelist(adjMatrix M)

int main(){


    return 0;
}



edgelist createEdgelist(adjMatrix M){
    edgelist ptr = (edgelist) malloc (sizeof(struct node));

    if(ptr != NULL){
        ptr->lastEdge = -1;

        //traverse matrix ,upper half only since its mirrored
        for(int row = 0; row < MAX_VERTEX; row++){
            for(int column = row + 1; column < MAX_VERTEX; column++){
                //check validity of cell
                if(M[row][column] != SENTINEL && ptr->lastEdge < MAX_VERTEX - 1){ //check for space as well
                    ptr->lastEdge++;
                    edgetype newEdge = {row, column, M[row][column]};

                    //look for proper position in edgelist
                    int index;
                    for(index= 0; index < ptr->lastEdge && newEdge.weight > ptr->edges[index].weight; index++){
                    }

                    //shift
                    for(int k = ptr->lastEdge; k > index; k--){
                        //swap
                        ptr->edges[k] = ptr->edges[k-1];
                    }

                    //insert at space
                    ptr->edges[index] = newEdge;
                }
            }
        }
    }
    return ptr;
}

    //2
    //0 1 2 3 4 5
    //3 5 6 7 8 9