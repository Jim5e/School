#include <stdio.h>
#include <stdlib.h>
#define MAX 10


typedef struct node{
    int data;
    int link;
}LIST;

typedef struct heap{
    LIST array[MAX];
    int avail;
}vheap;

typedef struct{
    int array[MAX];
    int count;
}arrayList;

typedef int cursorList;
typedef int SET; //we use a set so that we avoid having to search in the ArrayList

//-----------------------------
void initVheap(vheap *A);
void initSet(SET *set, arrayList values);
void insertElement(vheap *A, arrayList *source, SET* set, int value, cursorList *head); //given a value, check if it exists in source? insert in vheap + delete in source: do nothing
void deleteElement(vheap *A, int value, cursorList *head);
void deleteinSource(arrayList *source, int value);
void printHeap(vheap A, cursorList head);


int main (){
    //initialize
    arrayList data = {{5,7,2,6,3,4,2,1,9}, 9};
    SET *set_for_arrayList = (SET *) calloc(MAX, sizeof(SET));
    cursorList head = -1; //-1 is basically the NULL equivalent
    vheap main;
    initVheap(&main);
    initSet(set_for_arrayList, data);


    //operations
    insertElement(&main, &data, set_for_arrayList, 3, &head);
    insertElement(&main, &data, set_for_arrayList, 7, &head);
    insertElement(&main, &data, set_for_arrayList, 2, &head);
    insertElement(&main, &data, set_for_arrayList, 5, &head);
    deleteElement(&main, 7, &head);
    insertElement(&main, &data, set_for_arrayList, 6, &head);
    insertElement(&main, &data, set_for_arrayList, 4, &head);
    deleteElement(&main, 3, &head);
    insertElement(&main, &data, set_for_arrayList, 1, &head);



    printHeap(main, head);
    return 0;
}

void insertElement(vheap *A, arrayList *source, SET* set, int value, cursorList *head){
    //check if val exists in set (set in relation to the ArrayList, so we dont waste time searching in arrayList)
    if(set[value] == 0){
        printf("Value %d doesnt exist in ArrayList.\n", value);
    }else{
        set[value] = 0; //remove it
        deleteinSource(source, value); //remove in source

        //add value to vheap (check if there is space first)s
        int Ndx = A->avail;
        if(Ndx != -1){
            A->avail = A->array[Ndx].link;
            A->array[Ndx].data = value;
            A->array[Ndx].link = *head;
            *head = Ndx;            
        }
    }
}

void deleteElement(vheap *A, int value, cursorList *head){
    int trav = *head;
    int prev = -1;

    // Iterate until the end of the list or the node with the value to delete is found
    while (trav != -1 && A->array[trav].data != value) {
        prev = trav;
        trav = A->array[trav].link;
    }

    // If the value is found
    if (trav != -1) {
        // If the value is at the head of the list, update the head
        if (trav == *head) {
            *head = A->array[trav].link;
        }
        // Otherwise, update the 'link' of the previous node
        else {
            A->array[prev].link = A->array[trav].link;
        }

        // Add the deleted node to the available space list
        A->array[trav].link = A->avail;
        A->avail = trav;
    }
    else {
        printf("Value %d doesnt exist in vheap.", value);
    }
}

void deleteinSource(arrayList *source, int value){
    int i;
    for(i = 0; source->array[i] != value;i++){} //we know it exists so 1 condition will do
    while(i < source->count){
        source->array[i] = source->array[i+1];
        i++;
    }
    source->count--;
}

void initVheap(vheap *A){
    //set links
    int i;
    for(i = 0; i < MAX - 1; i++){
        A->array[i].link = i + 1;
    }

    //set last to be -1
    A->array[i].link = -1;
    A->avail = 0;
}

void initSet(SET *set, arrayList values){
    int i = 0;
    while(i < values.count){
        set[values.array[i]] = 1;
        i++;
    }
}

void printHeap(vheap A, cursorList head){
    printf("\nHEAD: %d\n", head);
    printf("AVAIL: %d\n", A.avail);
     printf("INDEX\tDATA\tLINK\n");
     int index = head;
    for(int i = head; i != -1; i = A.array[i].link){
        printf("\t%d \t\t%d -\t%d\n", index, A.array[i].data, A.array[i].link);
        index = A.array[i].link;
    }
}