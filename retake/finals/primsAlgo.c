/************************************************************************
 * Prim's Algorithm : It grows a spanning tree, one edge at a time.     *
 * Given:                                                               *
 *   1)  Graph G = (V, E)                                               *
 *   2)  V = {0, 1, 2, 3, 4}                                            *
 *                                                                      *
 * Steps of Prim�s Algorithm:                                           *
 *   1) Initialize set U to contain { 0 }                               *
 *      //In the program, starting vertex will be inputted by the user  *
 *   2) While (U != V)                                                  *
 *       a) Find the minimum cost edge (u, v) such that                 *
 *          u is an element  U and   v is not yet in U                  *
 *       b)  Add v to U                                                 *
 ************************************************************************/
 
#include <unistd.h>    // for sleep(), to add in code if display leaves blank screen  
#include <stdio.h> 
#include <string.h>   

                 
#define MAX  6              // Number of vertices in the graph  
#define INFINITY  0XFFFF    
   
/***** Data Structure Definition *****/  
typedef int graphType[MAX][MAX];    // A[x][y] = INFINITY  if there is not edge ;  A[x][y] = weight of the edge (x,y)
typedef int set[MAX];               // Bit-vector implementation of Set

typedef struct {
int u, v;     // (u,v) represents the edge  
int weight;   // weight of the edge
}edgetype;

typedef struct {
    edgetype edges[MAX];
    int edgeCount;   //actual number of edges
int minCost; //Cost of the MST
}primMST;

/***** Function Prototypes *****/

void populateGraph(graphType G);
primMST primAlgo(graphType graph, int startVertex);
void displayPrimMST(primMST tree);

int main() 
{ 
     /*---------------------------------------------------------------------------------
    * Problem #2 ::  a) Allows user to input from keyboard the starting vertex      *
    *                  b) Calls populateGraph() to populate the given graph           *
    *                  c) Calls primAlgo() and displayPrimMST()                       *
    *                                                                                 *
    * printf("\n\n\nProblem #2:: ");                                                  *  
    * printf("\n------------");                                                       *
    *---------------------------------------------------------------------------------*/
 printf("\n\n\nProblem #2:: "); 
   printf("\n------------");
   graphType G;
   populateGraph(G);

   primMST P = primAlgo(G, 0);
   displayPrimMST(P);
 
    return 0; 
} 

/************************************************************
 * Function Definitions                                     *
 ************************************************************/
void populateGraph(graphType G)
{
graphType graph = {  INFINITY, 1, 5, 4, 6, 5, 1, INFINITY, 5, INFINITY, INFINITY, 6, 5, 5, INFINITY, 2, INFINITY, INFINITY, 4,
                             INFINITY, 2, INFINITY, 1, INFINITY, 6, INFINITY,INFINITY, 1, INFINITY, 3, 5, 6, INFINITY, INFINITY, 3, INFINITY} ;   //5

memcpy(G, graph, sizeof(graph));
}

 

primMST primAlgo(graphType graph, int startVertex)
{
 //Write code here
 primMST P;
 P.edgeCount = 0;
 P.minCost = 0;

 //init SET
 set V = {0};
 V[startVertex] = 1;

 //find minimum from vistied to the unvisited nodes
    int min = INFINITY;
    int minDx;
    int u,v;

    while(P.edgeCount < MAX - 1){
        min = INFINITY;
        for(int i = 0; i < MAX; i++){
            if(V[i] == 1){
                for(int j = 0; j < MAX && V[i] == 1; j++){
                    if(V[j] == 0 && graph[i][j] < min){ //visited to the unvisited node, look for minimum
                        //CHECK IF MIN
                            min = graph[i][j];
                            minDx = j;
                            u = i;
                            v = j;
                    }
                }
            }
            
        }
                    //add to minDx to V and its data to MST
            if(min != INFINITY){
            V[minDx] = 1; //set minimum to true
            P.minCost = P.minCost + min;
            P.edges[P.edgeCount].weight = min; 
            P.edges[P.edgeCount].u = u;
            P.edges[P.edgeCount].v = v;
            P.edgeCount++;
            }
    }

    return P;
}

void displayPrimMST(primMST T)
{
int x;

printf("\n%5s%5s\n", "Edge", "Cost");
 
    //Write code here
    for(int i  = 0; i < T.edgeCount; i++){
        printf("(%d,%d) ", T.edges[i].u, T.edges[i].v);
        printf("%-4d\n", T.edges[i].weight);
    }

    printf("\n\nTotal: %d", T.minCost);

}
