#include <stdlib.h>
#include <stdio.h>
#define SIZE 7
typedef struct node {
  int elem;
  struct node *link;
} *LIST;

typedef LIST listArr[SIZE];
typedef int Vertex;
typedef int Set[SIZE];
void initListArr(listArr A);
void insertSorted(listArr L, int elem, int v);
void dfscaller(listArr G, Vertex start, listArr result);
void dfs(listArr G, Vertex start, Set V, listArr result);
void displayDFS(listArr G);

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

 //init needed parameters
  listArr result;
  initListArr(result);

  dfscaller(L, 1, result);
  displayDFS(result);

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

void dfscaller(listArr G, Vertex start, listArr result){
    //init Set
    Set Visited = {0};
    dfs(G, start, Visited, result);

    for(int i = 0; i < SIZE; i++){
        if(Visited[i] == 0){
         dfs(G, i, Visited, result);  
        }
    }

    for(int i = 0; i < SIZE; i++){
        printf("%d", Visited[i]);
        }
        printf("\n");
}

void displayDFS(listArr G){
    printf("NDX---Connections\n");
    for(int i = 0; i < SIZE;i++){
        LIST trav;
        printf("[%d]   ", i);
        for(trav = G[i]; trav != NULL;trav = trav->link){
            printf("%d", trav->elem);
            if(trav->link != NULL){
                printf(" -> ");
            }
        }
        printf("\n");
    }
}

void dfs(listArr G, Vertex start, Set V, listArr result){
    //Set start
    V[start] = 1;

    //traverse the linked list
    LIST trav;
    for(trav = G[start] ;trav != NULL; trav = trav->link){
        if(V[trav->elem] == 0){
            //create new node in result
            LIST newNode = (LIST) malloc (sizeof(struct node));
            if(newNode != NULL){
                //insert first
                newNode->elem = trav->elem;
                newNode->link = result[start];
                result[start] = newNode;
            }
            dfs(G, trav->elem, V, result);
            // printf("%d ", trav->elem);

        }

    }

}

