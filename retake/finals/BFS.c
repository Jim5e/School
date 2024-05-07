#include <stdlib.h>
#include <stdio.h>
#define SIZE 7

typedef struct node {
  int elem;
  struct node *link;
} *LIST;

typedef struct{
  int arr[SIZE];
  int front;
  int rear;
}queue;

typedef LIST listArr[SIZE];
typedef int Vertex;
typedef int Set[SIZE];
void initListArr(listArr A);
void insertSorted(listArr L, int elem, int v);
void bfscaller(listArr G, Vertex start);
void BFS(listArr G, Set V, Vertex start);

int main (){

    //creation of Graph List Representation
  listArr L;
  initListArr(L);
  insertSorted(L, 1, 0);
  insertSorted(L, 2, 0);

  insertSorted(L, 2, 1);
  insertSorted(L, 3, 1);
  
  insertSorted(L, 0, 2);

  insertSorted(L, 2, 3);
  insertSorted(L, 0, 3);

  insertSorted(L, 6, 4);
  insertSorted(L, 5, 4);

  insertSorted(L, 1, 5);

  insertSorted(L, 5, 6);
  insertSorted(L, 3, 6);

  bfscaller(L, 5);

 return 0;
}


void initListArr(listArr A) {
  int indx;
  for (indx = 0; indx < SIZE; indx++) {
    A[indx] = NULL;
  }
}

void insertSorted(listArr L, int elem, int v) {
  LIST temp = (LIST)malloc(sizeof(struct node));
  if (temp != NULL) {
    LIST *trav;
    for (trav = &L[v]; *trav != NULL && (*trav)->elem < elem; trav = &(*trav)->link) {}
    temp->elem = elem;
    temp->link = *trav;
    *trav = temp;
  }
}
  
void bfscaller(listArr G, Vertex start){
    //init Set
    Set Visited = {0};
    BFS(G, Visited, start);  

    for(int i = 0; i < SIZE; i++){
        if(Visited[i] == 0){
         BFS(G, Visited, i);  
        }
    }
}

void BFS(listArr G, Set V,Vertex start){
    //Queue array
    queue Q;
    Q.front = 0;
    Q.rear = SIZE - 1;
    V[start] = 1;

    //Enqueue start
    Q.rear = (Q.rear + 1) % SIZE;
    Q.arr[Q.rear] = start;
    printf("\n\n");
    printf("Start Vert: %d", start);


  while((Q.rear + 1 )% SIZE != Q.front){ //while queue is not empty
    //find adjacent
    int item = Q.arr[Q.front];
    LIST trav;
    for(trav = G[item]; trav != NULL && (Q.rear + 2) % SIZE != Q.front; trav = trav->link){ // while not at the end of list and not full ang queue
      if(V[trav->elem] == 0){ //enqueue adjacents if unvisited
        V[trav->elem] = 1; //set to true
        Q.rear = (Q.rear + 1) % SIZE; 
        Q.arr[Q.rear] = trav->elem;
      }
    }
    //dequeue
   Q.front = (Q.front + 1) % SIZE;
  }

  //SET verifier
  printf("\n");;
  for(int i = 0; i < SIZE; i++){
    printf("%d ", V[i]);
  }
}