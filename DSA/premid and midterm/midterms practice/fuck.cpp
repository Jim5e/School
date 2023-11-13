#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

typedef enum { false, true } Bool;
typedef struct {
    int in;
    char by[24];
} pub_t;

typedef struct {
    char title[24];
    char author[24];
    char genre[24];
    unsigned short pages;
} desc_t;

typedef struct {
    unsigned ID;
    desc_t desc;
    double price;
    pub_t published;
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
    insorted(&Matt, (Book_t){2,
                             {"Harry Potter and carlo", "J.K tRolling",
                              "Non-Fiction", 2050},
                             200.00,
                             {2017, "carlo"}});
    insorted(&Matt, (Book_t){5,
                             {"all the words are yours", "tyler knott gregson",
                              "Poetry", 50},
                             500.00,
                             {2012, "me"}});
    insorted(&Matt, (Book_t){1,
                             {"Harry Potter and carlo", "J.K tRolling",
                              "Non-Fiction", 2050},
                             200.00,
                             {2017, "carlo"}});
    insorted(&Matt, (Book_t){3,
                             {"all the words are yours", "tyler knott gregson",
                              "Poetry", 50},
                             500.00,
                             {2012, "me"}});

    displayList(&Matt);
    shVH(&Matt);
    deleteSorted(&Matt, 3);
    deleteSorted(&Matt, 1);
    shVH(&Matt);

    insorted(&Matt, (Book_t){1,
                             {"Harry Potter and carlo", "J.K tRolling",
                              "Non-Fiction", 2050},
                             200.00,
                             {2017, "carlo"}});
    insorted(&Matt, (Book_t){3,
                             {"all the words are yours", "tyler knott gregson",
                              "Poetry", 50},
                             500.00,
                             {2012, "me"}});
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
    Book_t retBook = {0U, {"xxxxx", "xxxxx", "xxxxx", 0U}, 0.0, {0, "xxxxx"}};
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
