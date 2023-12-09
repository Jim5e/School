#include <stdio.h>
#include <stdlib.h>

//this is not a standard way of making linked list, I am trying to exercise my understanding of PPN
//at the same time, have a struct that has the actual list and its corresponding count

typedef struct node{
    int data;
    struct node *link;

}*LIST;

typedef struct list{
    LIST head;
    int count;
} *LinkedList;

//operations
void initLL(LinkedList *L);
void insertFirst(LinkedList *L, int value);
void insertAt(LinkedList *L, int value, int pos);
void deleteValue(LinkedList *L, int value);
void printLL(LinkedList L);


int main(){
    LinkedList L;
    initLL(&L);
    insertFirst(&L, 10);
    insertFirst(&L, 2);
    insertFirst(&L, 5);
    insertFirst(&L, 3);
    insertFirst(&L, 98);
    insertAt(&L, 8, 6);
    deleteValue(&L, 12313);


    printLL(L);
    return 0;
}

void initLL(LinkedList *L){
    *L = (LinkedList) malloc (sizeof(struct list));
    (*L)->count = 0;
    (*L)->head = NULL;
}

void insertFirst(LinkedList *L, int value){
    LIST temp = (*L)->head;
    LIST newNode = (LIST) malloc (sizeof(struct node));
    newNode->data = value;
    (*L)->head = newNode;
    newNode->link = temp;
    (*L)->count++;
}

void insertAt(LinkedList *L, int value, int pos){
    LIST *trav = &(*L)->head;
    for(int currentPos = 1; currentPos < pos && *trav != NULL; currentPos++){
        trav = &(*trav)->link;
    }

    LIST newNode = (LIST) malloc (sizeof(struct node));
    newNode->data = value;
    newNode->link = *trav;
    *trav = newNode;
    (*L)->count++;
}

void deleteValue(LinkedList *L, int value){
    LIST *trav = &(*L)->head;
    for(;*trav != NULL && (*trav)->data != value; trav = &(*trav)->link){}  //utilize /short circuiting so that if the values isnt found, the 2nd condition
                                                                            // will not get checked, thereby causiing the program NOT to crash due to 
                                                                            //accessing inaccesible data (if we reach last node, meaning *trav == NULL,
                                                                            //then the condition (*trav)->data would be trying to reach non-existent data)
    if(*trav != NULL){
        LIST temp = *trav;
        *trav = temp->link;
        free(temp);
        (*L)->count--;        
    }

}

void printLL (LinkedList L){
    printf("CURRENT LIST:\n");
    printf("\t POSITION:\t");
    for(int location = 1; location <= L->count; location++){
        printf("%d", location); //pa chot choy sa dash format
        if(location != L->count){
            printf(" - ");
        }
    }

    printf("\n\t VALUE:\t\t");
    for(LIST trav = L->head; trav != NULL; trav = trav->link){
        printf("%d\t", trav->data);
    }

    printf("\n\n# of Items: %d\n", L->count);
}