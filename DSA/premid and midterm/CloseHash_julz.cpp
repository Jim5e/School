#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define PACKD (int)(MAX * 0.8)
#define DELETED '!'
#define EMPTY '?'
#define GARBAGE '_'

typedef struct {
    char Elem;
    int next;
} Node, Hspace[MAX];

typedef struct {
    Hspace table;
    int Avail;
} Dictionary;

bool isMember(Dictionary, char);
void initDictionary(Dictionary *);
void addElem(Dictionary *, char);
void deleteElem(Dictionary *, char);
void showDictionary(Dictionary);
int hash(char);

int main() {
    Dictionary Xander;
    char ch;
    initDictionary(&Xander);

    for (ch = 'A'; ch != 'Z'; ch++) {
        addElem(&Xander, ch);
    }
    deleteElem(&Xander,'J');
    addElem(&Xander, 'Q');
    addElem(&Xander, ch);

    showDictionary(Xander);
}

void addElem(Dictionary *Juan, char Elem) {
    if (!isMember(*Juan, Elem)) {
        int ndx = hash(Elem);
        if (Juan->table[ndx].Elem == EMPTY || Juan->table[ndx].Elem == DELETED) {
            Juan->table[ndx].Elem = Elem;
        } else {
            int new;
            new = Juan->Avail;

            if (new != -1) {
                Juan->Avail = Juan->table[new].next;
                Juan->table[new].Elem = Elem;
                Juan->table[new].next = Juan->table[ndx].next;
                Juan->table[ndx].next = new;
            }
        }
    }
}

void deleteElem(Dictionary *Eman, char Elem) {
    int ndx = hash(Elem);
    if (Eman->table[ndx].Elem == Elem) {
        Eman->table[ndx].Elem = DELETED;
    } else {
        int *x;
        for (x = &ndx; *x != -1 && Eman->table[*x].Elem != Elem ; x = &(Eman->table[*x].next)) {}

        if (*x != -1) {
            int del = *x;
            *x = Eman->table[del].next;
            Eman->table[del].next = Eman->Avail;
            Eman->Avail = del;
        }
    }
}

bool isMember(Dictionary Aisha, char Elem) {
    int ndx = hash(Elem);
    int x;
    if (Aisha.table[ndx].Elem != EMPTY && Aisha.table[ndx].Elem != DELETED) {
        for (x = ndx; x != -1 && Aisha.table[x].Elem != Elem;
             x = Aisha.table[x].next) {
        }
    }
    return Aisha.table[x].Elem == Elem;
}

void initDictionary(Dictionary *Carlo) {
    int x;
    for (x = 0; x < PACKD; x++) {
        Carlo->table[x].Elem = EMPTY;
        Carlo->table[x].next = -1;
    }
    for (; x < MAX - 1; x++) {
        Carlo->table[x].Elem = GARBAGE;
        Carlo->table[x].next = x + 1;
    }
    Carlo->Avail = PACKD;
    Carlo->table[x].Elem = GARBAGE;
    Carlo->table[x].next = -1;
}

void showDictionary(Dictionary Achille) {
    int x;
    printf(" Index | Elem | Next |\n");
    for (x = 0; x < MAX; x++) {
        printf(" [%02d]  |   %-3c|  %-3d |\n", x, Achille.table[x].Elem,
               Achille.table[x].next);
    }
    printf("\nAvail = %d", Achille.Avail);
}

int hash(char Elem) { return (toupper(Elem) - 65) % (int)(PACKD); }
