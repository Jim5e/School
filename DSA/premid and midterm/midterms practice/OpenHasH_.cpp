#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10
#define word 10


typedef struct node{
    char fruits[word];
    struct node *link;
    
}*LIST;

typedef LIST Dictionary[SIZE];


unsigned int hash(char fruit[]);
void initDictionary(Dictionary *A);
void insertElem(Dictionary *A, char elem[]);
void printDict(Dictionary A);
void printHashgrp(Dictionary A, int hashNdx);
void deleteElem(Dictionary *A, char elem[]);


int main(){
    //fruit table
    char apple[] = "lkofs";
    char banana[] = "banana";
    char cunt[] = "cunt";
    char drop[] = "drop";
    char ecki[] = "ecki";
    
    Dictionary A;
    initDictionary(&A);
    insertElem(&A, cunt);
    insertElem(&A, ecki);
    deleteElem(&A, ecki);
//    printHashgrp(A, 3);
    printDict(A);
    return 0;
}
void initDictionary(Dictionary *A){
    int i = 0;
    
    while (i < SIZE){
        (*A)[i] = NULL;
         i++;
    }
    
}

unsigned int hash(char fruit[]){
    int i = 0;
    int sum = 0;
    
    while(i < strlen(fruit)){
        sum += fruit[i];
        i++;
    }
    
    return sum % SIZE;
}

void insertElem(Dictionary *A, char elem[]){
    int hashNdx = hash(elem);
    LIST newNode = (LIST) malloc(sizeof(struct node));
    strcpy(newNode->fruits, elem);
    
    if((*A)[hashNdx] == NULL){
        (*A)[hashNdx] = newNode;
        newNode->link = NULL;
    }else{
        newNode->link = (*A)[hashNdx];
        (*A)[hashNdx] = newNode;
    }
}

void deleteElem(Dictionary *A, char elem[]) {
    int hashNdx = hash(elem);
    LIST *trav = &(*A)[hashNdx];
    
    // Find the element in the linked list
    while (*trav != NULL) {
        if (strcmp((*trav)->fruits, elem) == 0) {
            break;
        }
        trav = &(*trav)->link;
    }
    
    if (*trav != NULL) {
        LIST temp = *trav;
        *trav = temp->link;
        free(temp);
    }
}


void printHashgrp(Dictionary A, int hashNdx){
    int i  = 0;
    
    if(A[hashNdx] == NULL){
        printf("[%d] => NULL", hashNdx);
    }else{
        printf("[%d] =>", hashNdx);
        while(A[hashNdx] != NULL){
            printf(" %s =>", A[hashNdx]->fruits);
            A[hashNdx] = A[hashNdx]->link;
        }
        
    }
    
    printf("\n");
}


void printDict(Dictionary A){
    int i  = 0;
    
    while (i < SIZE){
        printHashgrp(A, i);
        i++;
    }
}
