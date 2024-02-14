    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    typedef struct node{
        int elem;
        struct node* link;
    }*LIST;

    void insertFirst(LIST *A, int x);
    bool deleteFirstInstance(LIST *A, int x);


    int main(){
        LIST main = NULL;
        insertFirst(&main, 6);
        insertFirst(&main, 3);
        insertFirst(&main, 7);
        insertFirst(&main, 8);
        printf("%d", deleteFirstInstance(&main, 623));

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

    bool deleteFirstInstance(LIST *A, int x){
        LIST *trav = NULL;
        bool isDeleted = false;

        for(trav = A; *trav != NULL && (*trav)->elem != x; trav = &(*trav)->link){}

        if(*trav != NULL){
            LIST temp = (*trav);
            (*trav) = temp->link;
            free(temp);
            isDeleted = true;
        }

        return isDeleted;
    }