#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    int elem;
    struct node *link;
}*SET;

SET SortedUnion(SET A, SET B);

int main(){



    return 0;
}

SET SortedUnion(SET Aptr, SET Bptr){
    SET C = NULL;
    for(SET *rear = &C; Aptr != NULL || Bptr != NULL; ){
        SET temp = (SET) malloc (sizeof(struct node)); //new node
        if(temp != NULL){
            temp->link = NULL;

            if(Aptr->elem > Bptr->elem){
                temp->elem = Bptr->elem;
                Bptr = Bptr->link;
            } else if(Bptr->elem > Aptr->elem){
                temp->elem = Aptr->elem;
                Aptr = Aptr->link;            
            }else{ //if both are the same
                Aptr = Aptr->link;   
                Bptr = Bptr->link;
                temp->elem = Aptr->elem;
            }
            *rear = temp; //utilize insertLast()
            rear = &(*temp)->link;            
        }

        if(Aptr ==  NULL){
            Aptr = Bptr;
        } else if(Bptr ==  NULL){
            Bptr = Aptr;
        }
    }
    return C;
}

SET UnsortedUnion(SET Aptr, SET Bptr){
    SET C = NULL;
    SET *trav;

    for(trav = &C; Aptr != NULL; Aptr = Aptr->link){ //Transfer all of A to C
        SET temp = (SET) malloc (sizeof(struct node));
        if(temp != NULL){
            temp->elem = Aptr->elem;
            temp->link = NULL;
            *trav = temp;
            trav = &temp->link;
        }
    }

    for( ; Bptr != NULL; Bptr = Bptr->link){ // compare B with C
        for(trav = &C; *trav != NULL && (*trav)->elem != Bptr->elem; trav = &(*trav)->link){} //empty for loop

        if(*trav == NULL){ //i.e. the element doesnt exist / has no duplicate
            SET newNode = (SET) malloc (sizeof(struct node));
                if(newNode != NULL){
                    newNode->elem = Bptr->elem;
                    newNode->link = C; //utilize insertFirst()
                    C = newNode;
                }
            }
        }
        return C;
}

