#ifndef stacksLinkedList
#define stacksLinkedList

typedef struct node{
    char elem;
    struct node* link;
}*stack;

void identifier();
void initStack(stack *A);
void push(stack *A, char elem);
char pop(stack *A);
char peek(stack A);
bool isEmpty(stack A);
void makeNull(stack *A);
void displayStack(stack *A);

void identifier(){  
    printf("---LINKED LIST STACK---\n");
}

void initStack(stack *A){
    *A = NULL;
}

void push(stack *A, char elem){
    stack newNode = (stack) malloc (sizeof(struct node));

    if(newNode != NULL){
        newNode->elem = elem;
        newNode->link = *A;
        *A = newNode;
    }
}

char pop(stack *A){
    char deleted = '\0';
    if(!isEmpty(*A)){
        stack temp = *A;
        (*A) = temp->link;
        deleted = temp->elem;
        free(temp);
    }
    return deleted;
}

char peek(stack A){
    return A->elem;
}

bool isEmpty(stack A){
    return (A == NULL)? true : false;
}

void makeNull(stack *A){
    *A = NULL;
}

void displayStack(stack *A){
    stack temp;
    initStack(&temp);

    while(!isEmpty(*A)){
        push(&temp,pop(A));
    }

    while(!isEmpty(temp)){
        char val = peek(temp);
        printf("[%c]", val);
        push(A,pop(&temp));
    }
}

#endif