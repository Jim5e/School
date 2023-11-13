#include <stdio.h>
#include<stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX 32
#define EMPTY '-'
#define DELETED '.'

typedef struct{
    char elem[MAX];
    int size;
}Dictionary;


Dictionary initDict();
int Hash(char data);
void insertElem(Dictionary *D, char data);
void deleteElem(Dictionary *D, char data);
bool isMember(Dictionary D, char data);
void display(Dictionary D);

const char *alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(void){
    Dictionary D;

    D = initDict();
    int i;
    for(i = 0; alpha[i] != '\0'; i++){
        insertElem(&D, alpha[i]);
    }

    
    
    deleteElem(&D, 'A');
    deleteElem(&D, 'T');
    deleteElem(&D, 'F');
    deleteElem(&D, 'J');
    deleteElem(&D, 'K');

display(D);



}

Dictionary initDict(){
    Dictionary D;
    int index;
    for(index = 0; index < MAX; index++){
        D.elem[index] = EMPTY;
    }
    return D;
}

int Hash(char data){
    return (toupper(data) - 'A') % MAX;
}

bool isMember(Dictionary D, char data){
    int count;
    int i;
    for(count = 0, i = Hash(data);
    count < MAX && D.elem[i] != EMPTY && D.elem[i]!= data;
    count++, i = (i+1) % MAX){}
    return(D.elem[i] == data);
}

void insertElem(Dictionary *D, char data){
    if(D->size < MAX && !isMember(*D, data)){
        int i;

        for(i = Hash(data); D->elem[i]!= DELETED && D->elem[i]!= EMPTY;i = (i+1) % MAX){}

        D->elem[i] = data;
        D->size++;
    }
}

void deleteElem(Dictionary *D, char data){
    if(D->size > 0){
        int count;
        int i;
        for (count = 0, i = Hash(data);count < MAX && D->elem[i] != data && D->elem[i] != EMPTY;count++, i = (i + 1) % MAX) {}
        if(D->elem[i] == data){
            D->elem[i] =DELETED;
            D->size--;
        }
    }
}

void makeNull(Dictionary *D){
    D->size = 0;
    int i;
    for(i = 0; i < MAX;i++){
        D->elem[i] = EMPTY;
    }
}

void display(Dictionary D){
    int i;
    for(i = 0; i < MAX; i++){
        printf("[ %c ]\n", D.elem[i]);
    }
}
