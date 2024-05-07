#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VERTICES 8
#define MAX_EDGES (MAX_VERTICES * (MAX_VERTICES - 1)) / 2
#define INFINITY 0XFFFF

/***** Data Structure Definition *****/
typedef int graphType[MAX_VERTICES][MAX_VERTICES]; // Adjacency matrix representation of the graph
typedef struct {
    int u, v;    // (u, v) represents an edge
    int weight;  // Weight of the edge
} edgetype;

typedef struct {
    edgetype edges[MAX_VERTICES - 1]; // Array to store edges of MST
    int edgeCount;                    // Actual number of edges in MST
    int minCost;                      // Total weight of MST
} kruskalMST;

/***** Function Prototypes *****/
void populateGraphExample(graphType G);
kruskalMST kruskalAlgo(graphType G); //give mst provided undirected graph
int findRep(int disjoint[], int member);
void sortEdges(graphType G, edgetype *sorted); //for sorting an array of edges
void displayKruskalMST(kruskalMST T);
void printMatrix(int dist[][MAX_VERTICES]);

int main()
{
    /*---------------------------------------------------------------------------------
    * 	Practice Problem: Implement Kruskal's Algorithm to find the Minimum Spanning Tree  *
    *                  of a given graph and compute its total weight.                  *
    *                                                                                 *
    * printf("\n\n\nPractice Problem: ");                                             *
    * printf("\n----------------------");                                             *
    *---------------------------------------------------------------------------------*/
    printf("\n\n\nPractice Problem: ");
    printf("\n----------------------");

    // Write code here
    // INITIALIZE//
    graphType G;

    // Populate the graph with example data

    populateGraphExample(G);
    // printMatrix(G);

    // // Find MST using Kruskal's Algorithm

    kruskalMST MST = kruskalAlgo(G);

    // // Display the resulting MST

    displayKruskalMST(MST);

    return 0;
}

/************************************************************
 * Function Definitions                                     *
 ************************************************************/
void populateGraphExample(graphType G)
{
    int graphData[MAX_VERTICES][MAX_VERTICES] = { //UNDIRECTED GRAPH
    //   0  1  2  3  4  5  6  7
        {0, 7, 0, 0, 0, 0, 0, 0},
        {7, 0, 0, 3, 0, 0, 3, 0},
        {0, 0, 0, 0, 2, 0, 0, 0},
        {0, 3, 0, 0, 0, 0, 0, 7},
        {0, 0, 2, 0, 0, 0, 0, 2},
        {0, 0, 0, 0, 0, 0, 5, 2},
        {0, 3, 0, 0, 0, 5, 0, 8},
        {0, 0, 0, 7, 2, 2, 8, 0},
    };

    // Copy the example data to the graph
    memcpy(G, graphData, sizeof(graphData));
}

kruskalMST kruskalAlgo(graphType G) //using disjoint SET
{
    //MST init
    kruskalMST K;
    K.edgeCount = 0;
    K.minCost = 0;


    //init disjoint SET, used for determining the components + #of vertices wihtin a component
    int disjoint[MAX_VERTICES];
    for(int i = 0; i < MAX_VERTICES; i++) {
        disjoint[i] = -1;
    }

    //init + sort edges
    edgetype sorted[MAX_EDGES]; //max edges because there can be WAY more edges than vertices, see formula above
    sortEdges(G, sorted);

     
    //while vertices are not under 1 component
    int index = 0;
    for(int components = MAX_VERTICES; components != 1;){ //decriment # of component, when 2 comps are connected
        //get representative
        edgetype edge = sorted[index];

        //check if same parents
        int u = findRep(disjoint, edge.u);
        int v = findRep(disjoint, edge.v);

        //determine whos repping via comparing # of members ALSO the lesser value = more members,
        //hence we use < (see below)

        if(u != v){
            if(disjoint[u] < disjoint[v]){ 
                disjoint[u] = disjoint[u] + disjoint[v];
                disjoint[v] = u; //point representative
            }else if(disjoint[v] <= disjoint[u]){ //using else if for clarity
                disjoint[v] = disjoint[v] + disjoint[u];
                disjoint[u] = v; //point representative 
            }
            components--; //decrease component count
            K.edges[K.edgeCount] = edge; 
            K.edgeCount++;
            K.minCost += edge.weight;            
        }
        index++;
    }

    return K;
}

int findRep(int disjoint[], int member)
{
    if(disjoint[member] < 0){ //its negative so it must be a parent now
        return member;
    }

    return findRep(disjoint, disjoint[member]);
}

void sortEdges(graphType G, edgetype sorted[]){
    int count = 0;
    //locate valid edges
    for(int i = 0 ; i < MAX_VERTICES; i++){

        for(int k = i + 1; k < MAX_VERTICES; k++){
            if(G[i][k] != INFINITY && G[i][k] != 0){
                //store in sorted
                sorted[count].u = i;
                sorted[count].v = k;
                sorted[count].weight = G[i][k];
                count++;
            }
        }
    }

    //bubble sort
    for(int i = 0; i < count - 1; i++){
        for(int k = 0; k < count - i - 1; k++){
            if(sorted[k].weight > sorted[k + 1].weight){
                //swap
                edgetype temp = sorted[k];
                sorted[k] = sorted[k + 1];
                sorted[k + 1] = temp;
            }
        }
    }
}

void displayKruskalMST(kruskalMST T)
{
    printf("\n%6s%12s", "Edge", "Cost");
    for (int i = 0; i < T.edgeCount; i++) {
        printf("\n%2d - %2d   %5d", T.edges[i].u, T.edges[i].v, T.edges[i].weight);
    }
    printf("\n\nTotal Minimum Cost: %d\n", T.minCost);
}

void printMatrix(int dist[][MAX_VERTICES])
{
    printf("\n");
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            if (dist[i][j] == INFINITY)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}
