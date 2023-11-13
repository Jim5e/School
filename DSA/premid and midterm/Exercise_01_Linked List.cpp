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

void insertFirstUnique(StudList *orig, StudList *insertee);

int main(){
    
    StudList Friend1 = (StudList ) malloc (sizeof(struct node)) ;
    StudList Friend2 = (StudList ) malloc (sizeof(struct node)) ;
    Friend1->link = Friend2;
    Friend2->link = NULL;
    
    //ID
    Friend1->stud.ID = 11600030;
    Friend2->stud.ID = 11800120;
    
    //name
    strcpy(Friend1->stud.LN, "CLARIT");
    strcpy(Friend2->stud.LN, "SMITH");
    
    strcpy(Friend1->stud.FN, "LAWRENCE");
    strcpy(Friend2->stud.FN, "JOHN");    

    Friend1->stud.MI = 'A';
    Friend2->stud.MI = 'B';
    
    //course & year
    strcpy(Friend1->stud.course, "BSCS");
    strcpy(Friend2->stud.course, "BS MATH");
    Friend1->stud.yearLevel = 2;
    Friend2->stud.yearLevel = 4;
    
    //person to insert
    StudList newPerson = (StudList ) malloc (sizeof(struct node)) ;
    newPerson->stud.ID = 1816060;
    strcpy(newPerson->stud.LN, "DUMAGETE");
    strcpy(newPerson->stud.FN, "KARABASAN");
    newPerson->stud.MI = 'G';
    strcpy(newPerson->stud.course, "BS BIO");
    newPerson->stud.yearLevel = 4;
    
    //call
    insertFirstUnique(&Friend1, &newPerson);
    
    return 0;
}

void insertFirstUnique(StudList *orig, StudList *insertee){
//    printf("%s", (*orig)->stud.FN);
//    printf("%s", (*insertee)->stud.FN);
    
    StudList current;
    
    current = *orig;
    
//    printf("%s", (*current)->stud.FN);
    
    //check if unique
    while(current != NULL){
        if(current->stud.ID == (*insertee)->stud.ID){
            printf("This person already Exists.");
            return;
        }
        
        current = current->link;
    }
    
    //at this point current should be at the last node, verifying that insertee is UNIQUE and can be inserted
    (*insertee)->link = (*orig);
    orig = insertee;
    
    
}
