#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef struct{
    char Lname[16];
    char Fname[24];
    char mI;
}name_t;

typedef struct{
    int studID;
    name_t studName;
    char course[8];
    char yrlvl;
}studType;

typedef struct{
    studType Stud;
    int link;
}nodeType;

typedef struct{
    nodeType Nodes[MAX];
    int Avail; 
}VirtualHeap;

void initVheap(VirtualHeap*);
void displayVH(VirtualHeap);
void inStud(int,VirtualHeap*);

int main(){
    VirtualHeap Carlo;
    initVheap(&Carlo);    
    displayVH(Carlo);
    inStud(22102606,&Carlo);
    displayVH(Carlo);
    inStud(22102605,&Carlo);
    inStud(22102604,&Carlo);
    displayVH(Carlo);
    inStud(22102633,&Carlo);
    inStud(22102633,&Carlo);
    inStud(22102633,&Carlo);
    inStud(22102633,&Carlo);
    displayVH(Carlo);

}

void initVheap(VirtualHeap* ptr){
    ptr->Avail=MAX-1;
    int x;
    for( x= 0 ; x<MAX;x++){
        ptr->Nodes[x].link=x-1;
    }
}

void displayVH(VirtualHeap ptr){
    int x;
        printf("\n\nIndex\tData\t  Link\n");
    for(x=0;x<MAX;x++){
        printf("%3d\t%-8d%5d\n",x,ptr.Nodes[x].Stud.studID,ptr.Nodes[x].link);
    }
    printf("\n\tAvail\n\t%3d",ptr.Avail);
}

void inStud(int ID,VirtualHeap* ptr){
    if(ptr->Avail!=-1){
        ptr->Nodes[ptr->Avail].Stud.studID=ID;
        ptr->Avail=ptr->Nodes[ptr->Avail].link;       
    }
}
