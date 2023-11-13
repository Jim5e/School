#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

typedef enum { false, true } Bool;

typedef struct {
    unsigned ID;
} Book_t;

typedef struct {
    Book_t book;
    int link;
} Node;

typedef struct {
    Node nodes[MAX];
    int Avail;
} VirtualHeap;

typedef struct {
    VirtualHeap VH;
    int head;
} List;

void initList(List *);
void insorted(List *, Book_t);
void deleteSorted(List *, unsigned);
Book_t retrieve(List *, unsigned);
Bool isEmpty(List *);
void makeNull(List *);
void shVH(List *Q);
void displayList(List *);
int allocSpace(List *);
void deallocSpace(List *, int);

int main() {
    List Matt;
    initList(&Matt);
    insorted(&Matt, (Book_t){2});
    insorted(&Matt, (Book_t){5});
    insorted(&Matt, (Book_t){1});
    insorted(&Matt, (Book_t){3});

    displayList(&Matt);
    shVH(&Matt);
    deleteSorted(&Matt, 3);
    deleteSorted(&Matt, 1);
    shVH(&Matt);

    insorted(&Matt, (Book_t){1});
    insorted(&Matt, (Book_t){3});
    shVH(&Matt);
}

void initList(List *B) {
    int x;
    for (x = 0; x < MAX; x++) {
        B->VH.nodes[x].link = x - 1;
    }
    B->VH.Avail = MAX - 1;
    B->head = -1;
}

void insorted(List *C, Book_t new) {
    if (C->VH.Avail != -1) {
        int ndx = allocSpace(C);
        if (ndx != -1) {
            int *trav;
            for (trav = &C->head;
                 *trav != -1 && new.ID > C->VH.nodes[*trav].book.ID;
                 trav = &C->VH.nodes[*trav].link) {
            }
            C->VH.nodes[ndx].link = *trav;
            C->VH.nodes[ndx].book = new;
            *trav = ndx;
        }
    }
}

void deleteSorted(List *D, unsigned ID) {
    if (!isEmpty(D)) {
        int *trav;
        for (trav = &D->head; *trav != -1 && ID != D->VH.nodes[*trav].book.ID;
             trav = &D->VH.nodes[*trav].link) {
        }
        if (*trav != -1) {
            int temp = *trav;
            *trav = D->VH.nodes[temp].link;
            deallocSpace(D, temp);
        }
    }
}

Book_t retrieve(List *L, unsigned ID) {
    int trav;
    Book_t retBook = {0U};
    for (trav = L->head; trav != -1 && ID != L->VH.nodes[trav].book.ID;
         trav = L->VH.nodes[trav].link) {
    }
    if (ID == L->VH.nodes[trav].book.ID) {
        retBook = L->VH.nodes[trav].book;
    }
    return retBook;
}

Bool isEmpty(List *X) { return X->head == -1; }

void makeNull(List *X) { initList(X); }

void displayList(List *Q) {
    if (!isEmpty(Q)) {
        printf("\n\nBookStore: ");
        int trav;
        for (trav = Q->head; trav != -1; trav = Q->VH.nodes[trav].link) {
            printf("\nBook#%d", Q->VH.nodes[trav].book.ID);
        }
    } else {
        printf("\n\nBookStore Empty :(\n");
    }
}

void shVH(List *Q) {
    int x;
    printf("\n\nLogical View:\n");
    printf("Avail=%d | ", Q->VH.Avail);
    for (x = Q->VH.Avail; x != -1; x = Q->VH.nodes[x].link) {
        printf("[%d] %d ", x, Q->VH.nodes[x].link);
    }
    printf("\nList=%d  | ", Q->head);
    for (x = Q->head; x != -1; x = Q->VH.nodes[x].link) {
        printf("[%d] %d ", x, Q->VH.nodes[x].link);
    }
}

int allocSpace(List *D) {
    int ndx = D->VH.Avail;
    if (ndx != -1) {
        D->VH.Avail = D->VH.nodes[ndx].link;
    }
    return ndx;
}

void deallocSpace(List *V, int node) {
    if (node >= 0 && node < MAX) {
        V->VH.nodes[node].link = V->VH.Avail;
        V->VH.Avail = node;
    }
}
