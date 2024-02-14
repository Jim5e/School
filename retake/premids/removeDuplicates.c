#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int elem;
    struct node* link;
}*LIST;

void insertFirst(LIST *A, int x);
void removeDuplicates(LIST *A);
void printList(LIST A);

int main(){
        LIST main = NULL;


        insertFirst(&main, 8);
        insertFirst(&main, 8);
        insertFirst(&main, 8);
        insertFirst(&main, 8);
        insertFirst(&main, 8);
        insertFirst(&main, 3);
        insertFirst(&main, 1);


        
        // printList(main);
        removeDuplicates(&main);
        printList(main);

    return 0;
}

void insertFirst(LIST *A, int x){
    LIST newNode = (LIST) malloc (sizeof(struct node));
    if(newNode != NULL){
        newNode->elem = x;
        newNode->link = *A;
        *A = newNode;
    }
}

void removeDuplicates(LIST *A){
  LIST *ahead = NULL;
  LIST *behind = NULL;
  
  for(behind = A, ahead = &(*behind)->link; *ahead != NULL; ahead = &(*ahead)->link){
    if((*ahead)-> elem == (*behind)->elem){
          LIST temp = (*behind);
          *behind  = temp->link;
      }else{
          behind = &(*behind)->link;
        }
    }
  
}

void printList(LIST A){
    LIST trav = A;

    while(trav != NULL){
        printf("%d", trav->elem);
        trav = trav->link;
        if(trav != NULL){
         printf("->");           
        }
    }
}