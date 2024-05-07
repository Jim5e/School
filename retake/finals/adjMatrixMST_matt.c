#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define V 6
#define INF INT_MAX

typedef int Graph[V][V];
typedef int set[V];

typedef struct edge {
	int head, tail, weight;
} edgeType;

typedef struct tree {
	edgeType edges[V];
	int edgeCount;
	int minCost;
} MST;

typedef struct node {
	int dest;
	struct node *link;
}*LL, nodeType;

typedef struct graph {
	LL graph[V];
	int edgeCount;
} listGraph;

typedef struct queue {
	int front;
	int rear;
	int queue[V];
} Queue;

void pause();

void initGraph(Graph *G);

void addEdge(Graph *G, int u, int v, int weight);
void populateUndirectedGraph(Graph *G);

void printGraph(Graph G);

MST primMST(Graph G, int startVertex);
MST kruskalMST(Graph G);
void printMST(MST T);

void addArc(Graph *G, int u, int v, int weight);
void populateDirectedGraph(Graph *G);

int *dijkstraPath(Graph G, int startVertex);
void floydPath(Graph G, Graph *floyd);
void printDijkstra(int *D);

void initAdjGraph(listGraph *G);
void addEdgeList(listGraph *G, int src, int dest);
void populateAdjGraph(listGraph *G);
void printListGraph(listGraph G);
void DFS(listGraph G, int start, set visited);
void BFS(listGraph G, int start, set visited);


int main() {

	printf("Test Case #1: Undirected, Weighted Graphs and MST\n\n");
	Graph graph;
	initGraph(&graph);
	populateUndirectedGraph(&graph);
	printf("Initial Graph:\n");
	printGraph(graph);
	MST prims = primMST(graph, 0);
	MST kruskal = kruskalMST(graph);

	printf("After Prim's Algorithm:\n");
	printMST(prims);
	printf("After Kruskal's Algorithm:\n");
	printMST(kruskal);
	pause();

	printf("Test Case #2: Directed, Weighted Graphs and Shortest Paths\n\n");
	Graph graph2;
	initGraph(&graph2);
	populateDirectedGraph(&graph2);
	printf("Initial Graph:\n");
	printGraph(graph2);
	int *D = dijkstraPath(graph2, 0);
	printf("After Dijkstra's Algorithm:\n");
	printDijkstra(D);

	Graph floyds;
	initGraph(&floyds);
	floydPath(graph2, &floyds);
	printf("After Floyd's Algorithm:\n");
	printGraph(floyds);
	pause();

	printf("Test Case #3: Directed, Unweighted Graphs and Traversal\n\n");
	listGraph list;
	initAdjGraph(&list);
	populateAdjGraph(&list);
	printListGraph(list);
	set DFSvisited = {0};
	set BFSvisited = {0};
	printf("After Depth First Search\n");
	DFS(list, 0, DFSvisited);
	printf("\n");
	printf("After Breadth First Search\n");
	BFS(list, 2, BFSvisited);

}

void pause() {
	printf("\n\nPress any key to continue...");
	getch();
	system("cls");
}

void initGraph(Graph *G) {
	int i, j;
	for(i = 0; i < V; i++) {
		for(j = 0; j < V; j++) {
			(*G)[i][j] = INF;
		}
	}
}

void addEdge(Graph *G, int u, int v, int weight) {
	if(u < V && v < V) {
		if((*G)[u][v] == INF) {
			(*G)[u][v] = weight;
			(*G)[v][u] = weight;
		} else {
			printf("Vertex %d--%d already has a weight of %d\n\n", u, v, (*G)[u][v]);
		}
	} else {
		printf("Vertex %d--%d does not exist!\n\n", u, v);
	}
}

void populateUndirectedGraph(Graph *G) {
	initGraph(G);
	addEdge(G, 0, 2, 3);
	addEdge(G, 0, 3, 23);
	addEdge(G, 1, 2, 55);
	addEdge(G, 1, 5, 29);
	addEdge(G, 3, 2, 4);
	addEdge(G, 5, 2, 11);
	addEdge(G, 4, 1, 2);
	addEdge(G, 4, 3, 77);
	printf("Finished edge populating\n");
}

void printGraph(Graph G) {
	printf("Displaying the Matrix:\n\n");
	printf("  ");
	int i, j;
	for(i = 0; i < V; i++) {
		printf("%5d", i);
	}
	printf("\n\n");
	for(i = 0; i < V; i++) {
		printf("%d ", i);
		for(j = 0; j < V; j++) {
			G[i][j] != INF ? printf("%5d", G[i][j]) : printf("%5s", "X");
		}
		printf("\n\n");
	}
}

MST primMST(Graph G, int startVertex) {
	set visited = {0};
	visited[startVertex] = 1;
	MST retval;
	retval.edgeCount = 0;
	retval.minCost = 0;

	while(retval.edgeCount < V - 1) {
		int i, j;
		int head, tail, weight = INF;
		for(i = 0; i < V; i++) {
			if(visited[i]) {
				for(j = 0; j < V; j++) {
					if(!visited[j] && G[i][j] < weight) {
						head = i;
						tail = j;
						weight = G[i][j];
					}
				}
			}
		}
		if(weight != INF) {
			visited[tail] = 1;
			retval.edges[retval.edgeCount].head = head;
			retval.edges[retval.edgeCount].tail = tail;
			retval.edges[retval.edgeCount].weight = weight;
			retval.minCost += weight;
			retval.edgeCount++;
		} else {
			weight = INF;
		}
	}
	return retval;
}

MST kruskalMST(Graph G) {
	MST retval;
	retval.edgeCount = 0;
	retval.minCost = 0;

	edgeType sortEdge[V*V];
	int edgeCounter = 0;
	int i, j;
	for(i = 0; i < V; i++) {
		for(j = 0; j < V; j++) {
			if(G[i][j] != INF) {
				sortEdge[edgeCounter].head = i;
				sortEdge[edgeCounter].tail = j;
				sortEdge[edgeCounter].weight = G[i][j];
				edgeCounter++;
			}
		}
	}
	for(i = 0; i < edgeCounter - 1; i++) {
		for(j = 0; j < edgeCounter - 1 - i; j++) {
			if(sortEdge[j].weight > sortEdge[j+1].weight) {
				edgeType temp = sortEdge[j];
				sortEdge[j] = sortEdge[j+1];
				sortEdge[j+1] = temp;
			}
		}
	}
	set visited;
	for(i = 0; i < V; i++) {
		visited[i] = i;
	}

	for(i = 0; i < edgeCounter && retval.edgeCount < V - 1; i++) {
		edgeType newEdge = sortEdge[i];
		int head = newEdge.head;
		int tail = newEdge.tail;
		int weight = newEdge.weight;

		while(visited[head] != head) {
			head = visited[head];
		}
		while(visited[tail] != tail) {
			tail = visited[tail];
		}
		if(head != tail) {
			retval.edges[retval.edgeCount] = newEdge;
			retval.edgeCount++;
			retval.minCost += weight;
			visited[tail] = head;
		}
	}
	return retval;
}

void printMST(MST T) {
	int i;
	printf("\nPrinting THE MST:\n\n");
	printf("%s%10s", "Edges", "Cost");
	for(i = 0; i < T.edgeCount; i++) {
		printf("\n%d-%d", T.edges[i].head, T.edges[i].tail);
		printf("%10d", T.edges[i].weight);
	}
	printf("\n\nThe MST cost is %d\n\n", T.minCost);
}
void addArc(Graph *G, int u, int v, int weight) {
	if(u < V && v < V) {
		if((*G)[u][v] == INF) {
			(*G)[u][v] = weight;
		} else {
			printf("An Arc already exists between vertices %d--%d with a weight of %d", u, v, (*G)[u][v]);
		}
	} else {
		printf("Cannot add arc to vertices %d--%d because it is out of range!", u, v);
	}
}
void populateDirectedGraph(Graph *G) {
	addArc(G, 0, 1, 50);
	addArc(G, 2, 1, 5);
	addArc(G, 1, 5, 8);
	addArc(G, 5, 4, 20);
	addArc(G, 5, 2, 3);
	addArc(G, 2, 0, 11);
	addArc(G, 0, 3, 77);
	addArc(G, 3, 1, 12);
	addArc(G, 4, 3, 1);
	printf("Finished arc populating\n");
}

int *dijkstraPath(Graph G, int startVertex) {
	int *retval = (int*)malloc(sizeof(int)*V);
	int i;
	for(i = 0; i < V; i++) {
		retval[i] = INF;
	}
	retval[startVertex] = 0;
	set visited = {0};

	for(i = 0; i < V - 1; i++) {
		int min = INF;
		int minIndex;
		int v;
		for(v = 0; v < V; v++) {
			if(!visited[v] && retval[v] <= min) {
				min = retval[v];
				minIndex = v;
			}
		}
		visited[minIndex] = 1;
		for(v = 0; v < V; v++) {
			if(!visited[v] && G[minIndex][v] != INF && retval[minIndex] != INF && retval[minIndex] + G[minIndex][v] < retval[v]) {
				retval[v] = retval[minIndex] + G[minIndex][v];
			}
		}
	}
	return retval;
}

void floydPath(Graph G, Graph *floyd) {
	int i, j, k;
	for(i = 0; i < V; i++) {
		for(j = 0; j < V; j++) {
			(*floyd)[i][j] = G[i][j];
		}
	}
	for(i = 0; i < V; i++) {
		(*floyd)[i][i] = 0;
	}
	for(k = 0; k < V; k++) {
		for(i = 0; i < V; i++) {
			for(j = 0; j < V; j++) {
				if((*floyd)[k][j] != INF && (*floyd)[i][k] != INF && (*floyd)[i][j] > (*floyd)[i][k] + (*floyd)[k][j]) {
					(*floyd)[i][j] = (*floyd)[i][k] + (*floyd)[k][j];
				}
			}
		}
	}
}

void printDijkstra(int *D) {
	int i;
	int startVertex;
	for(i = 0; i < V; i++) {
		if(D[i] == 0) {
			startVertex = i;
		}
	}
	printf("Printing Shortest Path starting from vertex %d:\n", startVertex);
	printf("%5s", "DEST");
	printf("%5s", "COST");
	for(i = 0; i < V; i++) {
		printf("\n%5d", i);
		D[i] != INF ? printf("%5d", D[i]) : printf("%5s", "NO");
	}
	printf("\n");
}

void initAdjGraph(listGraph *G) {
	int i;
	for(i = 0; i < V; i++) {
		G->graph[i] = NULL;
	}
	G->edgeCount = 0;
}

void addEdgeList(listGraph *G, int src, int dest) {
	if(src < V && dest < V) {
		LL *trav, temp;
		for(trav = &G->graph[src]; *trav != NULL; trav = &(*trav)->link) {}
		temp = (LL)malloc(sizeof(nodeType));
		if(temp != NULL) {
			temp->dest = dest;
			temp->link = *trav;
			*trav = temp;
		}
	}
}

void populateAdjGraph(listGraph *G) {
	addEdgeList(G, 0, 2);
	addEdgeList(G, 0, 3);
	addEdgeList(G, 4, 1);
	addEdgeList(G, 4, 3);
	addEdgeList(G, 2, 1);
	addEdgeList(G, 1, 3);
	addEdgeList(G, 3, 5);
	addEdgeList(G, 5, 0);
	addEdgeList(G, 5, 2);
	addEdgeList(G, 2, 4);
}
void printListGraph(listGraph G) {
	printf("Displaying the Adjacency List: \n");
	printf("%5s", "SRC");
	printf("%5s", "->");
	printf("%5s", "DEST");
	printf("\n");
	LL trav;
	int i;
	for(i = 0; i < V; i++) {
		printf("%5d", i);
		for(trav = G.graph[i]; trav != NULL; trav = trav->link) {
			printf("%5s", "->");
			printf("%5d", trav->dest);
		}
		printf("\n");
	}
	printf("\n");
}

void DFS(listGraph G, int start, set visited) {
	visited[start] = 1;
	printf("(DFS)Visiting Vertex: %d\n", start);

	LL current;
	for(current = G.graph[start]; current != NULL; current = current->link) {
		int connection = current->dest;
		if(!visited[connection]) {
			DFS(G, connection, visited);
		}
	}
}

void BFS(listGraph G, int start, set visited) {
	Queue Q = {0, -1, {0}};
	Q.rear++;
	Q.queue[Q.rear] = start;
	visited[start] = 1;

	LL current;
	while(Q.front <= Q.rear) {
		int currentVertex = Q.queue[Q.front];
		Q.front++;
		printf("(BFS)Visiting Vertex: %d\n", currentVertex);
		for(current = G.graph[currentVertex]; current != NULL; current = current->link) {
			int connection = current->dest;
			if(!visited[connection]) {
				Q.rear++;
				Q.queue[Q.rear] = connection;
				visited[connection] = 1;
			}
		}
	}
}

