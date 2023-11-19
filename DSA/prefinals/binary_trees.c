#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//based on: https://youtu.be/hfwwaNNJ-0A?si=dHH5z0HcR2OQ9hnq || print(), insert(), find()

typedef struct treenode {
    int data;
    struct treenode *left;
    struct treenode *right;

} treenode;

treenode *createNode(int value);
void printTree(treenode *root);
void printTab(int numtabs);

void printTree_PRE(treenode *A, int level); //preorder traversal
void printTree_INORDER(treenode *tree, int level);
void printTree_POST(treenode *tree, int level);
void insertTree(treenode **root, int value);
bool findNum(treenode *root, int value);
treenode *deleteTree(treenode *root, int value);
treenode *findMin(treenode *root);

int main(){
    treenode *n1 = NULL;
    insertTree(&n1, 7);
    insertTree(&n1, 2);
    insertTree(&n1, 8);
    insertTree(&n1, 6);
    insertTree(&n1, 12);
    insertTree(&n1, 3);
 


    // // findNum(n1, 12);
    // deleteTree(n1, 12);
    printTree(n1); //curently using preorder
    free(n1);

    return 0;
}

treenode *createNode(int value){
    treenode *result  = malloc (sizeof(treenode));

    if(result != NULL){
    result->data = value;
    result->left = NULL;
    result->right = NULL;
    }

    return result;
}

void insertTree(treenode **root, int value){
    if(*root == NULL ){
        *root = createNode(value); //connects the link of the parent to the child if the child area (left or right) is empty.
        return;
    }

    if(*root != NULL){
        if(value < (*root)->data){
            insertTree(&(*root)->left, value);
        }else if (value > (*root)->data){
            insertTree(&(*root)->right, value);
        }else{
            //its  equal, so nothing (no dupes allowed)
        }
    }
}

treenode *deleteTree(treenode *root, int value){ //https://youtu.be/gcULXE7ViZw?si=0xxeqcyUSIhEzGFT & https://youtu.be/DkOswl0k7s4?si=PxpfTxrCnKpscWRI
    if(root == NULL){ // tree is empty
        return root;
    }else if(value < root->data){
        root->left = deleteTree(root->left, value); //if less, go left
        return root;
    }else if(value > root->data){
        root->right = deleteTree(root->right, value); //if greater, go right
        return root;

    }else{ //at this point, we should have found the node with the value

        if(root->left == NULL && root->right == NULL){ //case 1: no children
            free(root); //delete whatver node root was pointing too
            root = NULL; //set the pointer of root to be null. since we dont want it pointing at empty space
            

        }else if(root->left == NULL && root->right != NULL){ //case 2: left is empty, right has child || i.e. 1 child
            treenode *temp = root;
            root = root->right;
            free(temp);

        }else if(root->right == NULL && root->left != NULL){ //case 2.5: right is empty, left has child || i.e. 1 child
            treenode *temp = root;
            root = root->left;
            free(temp);

        }else{//case 3: both children
            treenode* temp = findMin(root->right); //find smallest in right subtree
            root->data = temp->data;
            root->right = deleteTree(root->right, temp->data); // delete the duplicate node from the right subtree, the return value of this should be null. thereby deleting the link to the old node
        }

        
    }


    return root;
}

treenode *findMin(treenode *root){
    treenode *smallest;

    if(root->left == NULL){ //the moment left is empty meaning we have reached a leaf node, indicating it is the smallest
        smallest = root;
        return smallest;
    }else if(root->left != NULL){ //if left still exists then that means there is POTENTIAL for something left of that node to be smaller. so we keep going
        return findMin(root->left);
    }

}


bool findNum(treenode *root, int value){
    if(root != NULL){
        if(value < root->data){
            findNum(root->left, value);
        }else if(value > root->data){
            findNum(root->right, value);
        }       
    }else{ //if it is NULL i.e. we reached leaf node
        printf("%d does NOT exist within the tree", value);
        return false; 
    }

        printf("%d exists within the tree", value);
        return true;

}

void printTree_PRE(treenode *A, int level){

    if(A == NULL){
        printTab(level);
        printf("--empty--\n");
        return;
    }

    printTab(level);
    printf("value = %d\n", A->data); //ROOT

    printTab(level);
    printf("LEFT: \n");
    printTree_PRE(A->left, level + 1); //L

    printTab(level);
    printf("RIGHT: \n");
    printTree_PRE(A->right, level + 1); //R
}

void printTree_INORDER(treenode *A, int level){

    if(A == NULL){
        printTab(level);
        printf("--empty--\n");
        return;
    }
    printTab(level);
    printf("LEFT: \n");
    printTree_PRE(A->left, level + 1); //L

    printTab(level);
    printf("value = %d\n", A->data); //ROOT

    printTab(level);
    printf("RIGHT: \n");
    printTree_PRE(A->right, level + 1); //R
}

void printTree_POST(treenode *A, int level){

    if(A == NULL){
        printTab(level);
        printf("--empty--\n");
        return;
    }

    printTab(level);
    printf("LEFT: \n");
    printTree_PRE(A->left, level + 1); //L

    printTab(level);
    printf("RIGHT: \n");
    printTree_PRE(A->right, level + 1); //R

    printTab(level);
    printf("value = %d\n", A->data); //ROOT
}

void printTree(treenode *root){
    printTree_PRE(root, 0);
}

void printTab(int numtabs){
    for(int i = 0; i < numtabs; i++){
        printf("\t");
    }

}