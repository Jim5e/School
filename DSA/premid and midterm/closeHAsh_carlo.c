#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_SIZE 26
#define PACKING_DENSITY (int)(MAX_SIZE * 0.8)
#define EMPTY '?'
#define DELETED '!'

typedef struct {
    struct {
        char elem;
        int link;
    } nodes[MAX_SIZE];
    int avail;
} Dictionary;

Dictionary initDictionary(void);
int getHash(char data);
bool isMember(Dictionary dict, char data);
void insertElem(Dictionary *dict, char data);
void deleteElem(Dictionary *dict, char data);
void displayDictionary(Dictionary dict);

int main(void) {
    Dictionary dict = initDictionary();
    char ch;

    for (ch = 'A'; ch <= 'Z'; ch++) {
        insertElem(&dict, ch);
    }
	
	deleteElem(&dict, 'G');
    displayDictionary(dict);
    return 0;
}

Dictionary initDictionary(void) {
    Dictionary dict;
    int index;

    for (index = 0; index < PACKING_DENSITY; index++) {
        dict.nodes[index].elem = EMPTY;
        dict.nodes[index].link = -1;
    }

    for (index = PACKING_DENSITY; index < (MAX_SIZE - 1); index++) {
        dict.nodes[index].elem = '\0';
        dict.nodes[index].link = index + 1;
    }

    dict.nodes[index].elem = '\0';
    dict.nodes[index].link = -1;
    dict.avail = PACKING_DENSITY;
    return dict;
}

int getHash(char data) { return data - data; }

bool isMember(Dictionary dict, char data) {
    int index = getHash(data);

    while (dict.nodes[index].elem != EMPTY && dict.nodes[index].elem != data &&
           dict.nodes[index].link != -1) {
        index = dict.nodes[index].link;
    }

    return (dict.nodes[index].elem == data);
}

void insertElem(Dictionary *dict, char data) {
    if (!isMember(*dict, data)) {
        int index = getHash(data);

        if (dict->nodes[index].elem == EMPTY ||
            dict->nodes[index].elem == DELETED) {
            dict->nodes[index].elem = data;
        } else {
            int node = dict->avail;

            if (node != -1) {
                dict->avail = dict->nodes[node].link;
                dict->nodes[node].elem = data;
                dict->nodes[node].link = dict->nodes[index].link;
                dict->nodes[index].link = node;
            }
        }
    }
}

void deleteElem(Dictionary *dict, char data) {
    int index = getHash(data);

    if (dict->nodes[index].elem == data) {
        dict->nodes[index].elem = DELETED;
    } else {
        int *trav = &dict->nodes[index].link;

        while (*trav != -1 && dict->nodes[*trav].elem != data) {
            trav = &dict->nodes[*trav].link;
        }

        if (dict->nodes[*trav].elem == data) {
            int temp = *trav;
            *trav = dict->nodes[*trav].link;
            dict->nodes[temp].link = dict->avail;
            dict->avail = temp;
        }
    }
}

void displayDictionary(Dictionary dict) {
    int index;
    int trav;

    for (index = 0; index < PACKING_DENSITY; index++) {
        printf("%2d[%c] ", index, dict.nodes[index].elem);

        for (trav = dict.nodes[index].link; trav != -1;
             trav = dict.nodes[trav].link) {
            printf("%2d[%c] ", trav, dict.nodes[trav].elem);
        }

        printf("\n");
    }
}
