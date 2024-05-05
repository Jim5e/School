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
void BFS(listArr G, Vertex start);
void queueElem();
void dequeue();

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

void BFS(listArr G, Vertex start){
    //Set
    Set V = {0};
    V[start] = 1;
    
    //Queue array
    queue Q;
    Q.front = NULL;
    Q.rear = &Q.front;

    for(int count = 0; count != SIZE;){
        //find adjacent
        
    }
}
