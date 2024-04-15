#include <stdio.h>
#include <stdlib.h>

typedef int node;

typedef struct node{
    node label;
    struct node *RC;
    struct node *LC;
}*BST;

typedef enum{TRUE,FALSE}Boolean;

void initBST(BST *A);
void displayBST(BST A); // Ascending Order
Boolean Member(BST A, node Elem); // return TRUE or FALSE
void insertNode(BST *A, node Elem);
void deleteNode(BST *A, node Elem);
// Min(); // return min value
// Max(); // return max value

int main(){

    BST ptr;
    initBST(&ptr);

    //test
    insertNode(&ptr, 23);
    insertNode(&ptr, 8);
    insertNode(&ptr, 47);
    insertNode(&ptr, 6);
    insertNode(&ptr, 0);
    insertNode(&ptr, 5);
    insertNode(&ptr, 12);
    insertNode(&ptr, 7);


    //
    deleteNode(&ptr, 23);
    displayBST(ptr);

    return 0;
}

void initBST(BST *A){
    *A = NULL;
}

void displayBST(BST A){ // Ascending Order, i.e. L->Root->R i.e inorder
    if(A == NULL){
        return;
    }
    displayBST(A->LC);
    printf("%d ", A->label);
    displayBST(A->RC);
}

void insertNode(BST *A, node Elem){
    BST *trav;
    for(trav = A; *trav != NULL && Elem != (*trav)->label; trav = (Elem > (*trav)->label) ? &(*trav)->RC: &(*trav)->LC){} //empty for loop. If *trav is not yet at a leaf node, keep goin L or R
                                                                       // or if it finds same elem
    
    if(*trav == NULL) {
        BST temp = calloc (1, sizeof(struct node));
        if(temp != NULL){
            temp->label = Elem;
            *trav = temp;
        }
    }
}

Boolean Member(BST A, node Elem){ // return TRUE or FALSE
    BST trav;
    for(trav = A; trav != NULL && trav->label != Elem;){
        trav = (Elem > trav->label) ? trav->RC: trav->LC;
    }

    if(trav == NULL){
        return TRUE;
    }

    return FALSE;
}

void deleteNode(BST *A, node Elem){
    //locate Elem
    BST *trav;
    for(trav = A; *trav != NULL && (*trav)->label != Elem; ){
        trav = (Elem > (*trav)->label) ? &(*trav)->RC: &(*trav)->LC;
    }

    //if found, delete
    if(*trav != NULL){
        if((*trav)->LC == NULL){
            *trav = (*trav)->RC;
        }else if((*trav)->RC == NULL){
            *trav = (*trav)->LC;
        }else{  
            //2 children
            BST *successor;
            for(successor = &(*trav)->RC; (*successor)->LC != NULL; ){
                successor = &(*successor)->LC;
            }

            (*trav)->label = (*successor)->label;
            BST temp = *successor;
            free(temp);
            (*successor) = temp->RC;
        }
    }
}