#include <stdio.h>
#include <stdlib.h>

#define MAX 8

typedef int Set[MAX];

void initSet(Set set);
void insertElem(Set set, int elem);
void deleteElem(Set set, int elem);
bool isMember(Set set, int elem);
Set *Union(Set a, Set b);
Set *Intersection(Set a, Set b);
Set *Difference(Set a, Set b);
void printSet(Set set);

void initSet(Set set) {
    int ndx;

    for (ndx = 0; ndx < MAX; ndx++) {
        set[ndx] = 0;
    }
}

void insertElem(Set set, int elem) {
    if (elem < MAX) {
        set[elem] = 1;
    }
}

void deleteElem(Set set, int elem) {
    if (elem < MAX) {
        set[elem] = 0;
    }
}

bool isMember(Set set, int elem) {
    return set[elem] == 1;
}

Set *Union(Set a, Set b) {
    Set *c = (Set *)calloc(1, sizeof(Set));
    int ndx;

    for (ndx = 0; ndx < MAX; ndx++) {
        (*c)[ndx] = a[ndx] || b[ndx];
    }

    return c;
}

Set *Intersection(Set a, Set b) {
    Set *c = (Set *)calloc(1, sizeof(Set));
    int ndx;

    for (ndx = 0; ndx < MAX; ndx++) {
        (*c)[ndx] = a[ndx] && b[ndx];
    }

    return c;
}

Set *Difference(Set a, Set b) {
    Set *c = (Set *)calloc(1, sizeof(Set));
    int ndx;

    for (ndx = 0; ndx < MAX; ndx++) {
        (*c)[ndx] = a[ndx] && (!b[ndx]);
    }

    return c;
}

void printSet(Set set) {
    int elem;

    for (elem = 0; elem < MAX; elem++) {
        if (set[elem]) {
            printf("%d ", elem);
        }
    }

    printf("\n");
}
