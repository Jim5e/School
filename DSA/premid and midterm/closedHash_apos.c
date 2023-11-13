#include <stdio.h>
#define MAX 10
#define EMPTY 0

typedef int DICTIONARY[MAX];

void initialize(DICTIONARY myDict);
void displayDictionary(DICTIONARY myDict);
void insert(DICTIONARY myDict, int elem);
void searchLength(DICTIONARY myDict);
float aveSL(DICTIONARY myDict);
int hash(int elem);

int main() {
    DICTIONARY myDict;
    initialize(myDict);
    insert(myDict, 11);
    insert(myDict, 14);
    insert(myDict, 19);
    insert(myDict, 19);
    insert(myDict, 10);
    insert(myDict, 13);
    insert(myDict, 24);
    insert(myDict, 23);
    displayDictionary(myDict);

    searchLength(myDict);
    float averageSearchLength = aveSL(myDict);
    printf("Average Search Length: %.3f\n", averageSearchLength);

    return 0;
}

float aveSL(DICTIONARY myDict) {
    int i;
    int count = 0;
    int SL = 0;
    for (i = 0; i < MAX; i++) {
        if (myDict[i] != EMPTY)  {
            SL += ((i - hash(myDict[i]) + 1) % 10 + 10) % 10;
            count++;
        }
    }

    printf("TOTAL SL: %d\n", SL);
    return ((float)SL / (float)count);
}

void searchLength(DICTIONARY myDict) {
    int i;
    int SL = 0;
    for (i = 0; i < MAX; i++) {
        if (myDict[i] != EMPTY)  {
            SL = ((i - hash(myDict[i]) + 1) + 10) % 10;
            printf("SEARCH LENGTH OF INDEX[%d] %d: %d\n", i, myDict[i], SL);
        }
    }
}

void initialize(DICTIONARY myDict) {
    int i;
    for (i = 0; i < MAX; i++) {
        myDict[i] = EMPTY;
    }
}

int hash(int elem) {
    return elem % 10;
}

void insert(DICTIONARY myDict, int elem) {
    int index = hash(elem);
    int i;
    for (i = 0; myDict[index] != EMPTY; i++) {
        index = (hash(elem) + i ) % 10;
    }
    myDict[index] = elem;
}

void displayDictionary(DICTIONARY myDict) {
    int i;
    for (i = 0; i < MAX; i++) {
        printf("INDEX[%d]: %d\n", i, myDict[i]);
    }
}
