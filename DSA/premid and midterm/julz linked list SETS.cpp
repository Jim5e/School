#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char data;
    struct node *link;
} c_type, *SET;

SET Difference(SET A, SET B);
SET Union(SET A, SET B);
SET Intersection(SET A, SET B);
void push(char data, SET *X);
void show(SET X);

int main() {
    SET A, B;
    int x;
    char stanlee[] = "LKIHGFEDCB";
    char carlo[] = "IHEB";

    for (x = 0; carlo[x] != '\0'; x++) {
        push(carlo[x], &A);
    }

    for (x = 0; stanlee[x] != '\0'; x++) {
        push(stanlee[x], &B);
    }

    show(A);
    show(B);

    SET C = Intersection(A, B);
    show(C);

    return 0;
}

void push(char data, SET *X) {
    SET new = (SET)malloc(sizeof(struct node));
    if (new != NULL) {
        new->data = data;
        new->link = (*X);
        (*X) = new;
    }
}

SET Union(SET A, SET B) {
    SET C = NULL;
    SET *C_end = &C;

    while (A != NULL && B != NULL) {
        *C_end = (SET)malloc(sizeof(c_type));

        if (C_end != NULL) {

            if (A->data < B->data) {
                (*C_end)->data = A->data;
                A = A->link;
            } else {
                if (A->data == B->data) {
                    A = A->link;
                }
                (*C_end)->data = B->data;
                B = B->link;
            }
            C_end = &(*C_end)->link;
        }
    }
    if (B != NULL) {
        A = B->link;
    }

    while (A != NULL) {
        *C_end = (SET)malloc(sizeof(c_type));

        if (C_end != NULL) {
            (*C_end)->data = A->data;
            A = A->link;
            C_end = &(*C_end)->link;
        }
    }
    *C_end = NULL;
    return C;
}

void show(SET X) {
    printf("\n\nSHOW\n");
    for (; X != NULL; X = X->link) {
        printf("%c", X->data);
    }
    printf("\n");
}
