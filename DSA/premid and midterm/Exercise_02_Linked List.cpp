#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
   int ID;
   char  LN[16], FN[24], MI;  //Lastname, Firstname, Middle Initial
   char course[8];          
   int yearLevel;
}Studrec;
typedef struct node {
    Studrec stud;
    struct node *link;
}*StudList;   //Definition of the List

Studrec deleteElementbyID(StudList *orig, int deletedID);

int main(){
    
    StudList Friend1 = (StudList ) malloc (sizeof(struct node)) ;
    StudList Friend2 = (StudList ) malloc (sizeof(struct node)) ;
    StudList Friend3 = (StudList ) malloc (sizeof(struct node)) ;
    Friend1->link = Friend2;
    Friend2->link = Friend3;
    Friend3->link = NULL;
    
    //ID
    Friend1->stud.ID = 11600030;
    Friend2->stud.ID = 11700120;
    Friend3->stud.ID = 11900620;
    
    //name
    strcpy(Friend1->stud.LN, "CLARIT");
    strcpy(Friend2->stud.LN, "SMITH");
    strcpy(Friend3->stud.LN, "CAMERON");
    
    strcpy(Friend1->stud.FN, "LAWRENCE");
    strcpy(Friend2->stud.FN, "JOHN");    
    strcpy(Friend3->stud.FN, "DOVE");

    Friend1->stud.MI = 'A';
    Friend2->stud.MI = 'B';
    Friend3->stud.MI = 'C';
    
    //course & year
    strcpy(Friend1->stud.course, "BSCS");
    strcpy(Friend2->stud.course, "BS MATH");
    strcpy(Friend3->stud.course, "BSTourism");
    Friend1->stud.yearLevel = 2;
    Friend2->stud.yearLevel = 4;
    Friend3->stud.yearLevel = 6;
    
    //ID to delete
    int toVanishID = 11900620;


    
    //call
    Studrec whoGotDeleted= deleteElementbyID(&Friend1, toVanishID);
    
    printf("%s", whoGotDeleted.FN);
    
    return 0;
}



Studrec deleteElementbyID(StudList *orig, int deletedID){
//  Write the code of the function that will delete the element bearing the given ID number from the given list if it exist.
// In addition, the deleted element will be returned to the calling function.
// If no such element exists, return a dummy element whose string fields are set to XXXXX and integer fields to 0.
    
    StudList current;
    StudList currentRight;
    StudList deletedNode;
    int count = 0;
    int pos = 1;
    int i = 1;
    current = *orig;
    currentRight = *orig;
    
    //get count
    while(current != NULL){
        count++;
        current = current->link;
    }
    
    //finding position
    for(current = (*orig); current != NULL && current->stud.ID != deletedID; current = current->link){ //locating the node to be deleted
        pos++;
    }
    
    //code
    if (pos <= 1){ //if located at first node
        current = *orig;
        *orig = (*orig)->link;
        return current->stud;
        
    }else if(pos >= count){ // if located at last node
        current = *orig;
        StudList previous;
        
        while(current->link != NULL){
            previous = current;
            current = current->link;
        }
        previous->link = NULL;
        
        return current->stud;
    }else{ //if somewhere in teh middle
        while(i < pos - 1){
            current = current->link;
            i++;
        }
    currentRight = current->link->link;
    free(current->link);
    current->link = currentRight;
    
    return current->stud;
    }

}
