#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char value;
    struct node *link;
    
    
}*LIST, nodetype;


void insertLastUnique(char elem, LIST *A);
char askInput();
void printData(LIST *A);


int main(){
    LIST head = (LIST ) malloc (sizeof(nodetype)); //A
    LIST body1 = (LIST ) malloc (sizeof(nodetype)); //F
    LIST body2 = (LIST ) malloc (sizeof(nodetype)); //G
    
    //initializing values
    head->value = 'A';
    head->link = body1;
    body1->value = 'F';
    body1->link = body2;
    body2->value = 'G';
    body2->link = NULL;

//    printf("%p", body1->link); //checker for links/value
    
    //function call ----------------------------------------------------------------
    char catcher = askInput();
//    printf("%c", catcher); //checker if i got the correct letter back to main
    insertLastUnique(catcher, &head);
    printData(&head);
    
    return 0;
}

char askInput(){
    char X;
    
    printf("What letter do you want to check?");
    scanf("%c", &X);
    
    return X;
}

void insertLastUnique(char elem, LIST *A){
    //new node & initialize
    char taker = elem;
    
    LIST current;
    LIST newGuy = (LIST ) malloc (sizeof(nodetype));
    newGuy->value = taker;
    newGuy->link = NULL;
//    printf("%c\n", newGuy->value);
//    printf("%p\n", newGuy->link); //checkers if correct pag input sa value

    //actual code for checking whether naay unique or not
    current = *A; //idk why naay asterisk ang A but it works so
  
  int count;
  for(count = 0; count < 10;count++){ //count is just arbitrary
    if(current->value == taker){ //it is important that you check the value first before checking whether link is NULL, or else sayop ang edge cases
  		printf("Sorry that letter already exists. Try again.\n");
   		return;
  		 }else if(current->link != NULL){
   	 	 current = current->link;
    	}  
    }

    //once current becomes null, we have arrived at the last node, we can then adjust its link to connect to the new node.
    current->link = newGuy;
    
}

void printData(LIST *A){
    LIST current;
    current = *A;
    
    printf("\nList of Letters: \n");
        while(current != NULL){
        printf("%c ", current->value);
        printf("%p \n", current->link);        //PRINT THINGS
        current=current->link;
     }    
    
    
}
