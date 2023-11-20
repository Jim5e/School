#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node *left;
    struct node *right;
}treenode;

treenode *createNode(int value);
void printTree_post(treenode *root);
void printTree_pre(treenode *root);
void printTree_inorder(treenode *root);
void insertNode(treenode **root, int value);
treenode *deleteNode(treenode *root, int value);
treenode *findMax(treenode *root);
void findMin();

int main(){
    treenode *tree = NULL;
    insertNode(&tree, 7);
    insertNode(&tree, 2);
    insertNode(&tree, 8);
    insertNode(&tree, 6);
    insertNode(&tree, 12);
    insertNode(&tree, 3);
    // deleteNode(tree, 8);
    // deleteNode(tree, 12);


    //print
    printf("POST_order: ");
    printTree_post(tree);
    printf("\nPRE_order: ");
    printTree_pre(tree);
    printf("\nIN_order: ");
    printTree_inorder(tree);
    return 0;
}

treenode *createNode(int value){
    treenode *result = malloc(sizeof(treenode));


    if(result != NULL){
        result->value = value;
        result->right = NULL;
        result->left = NULL;
    }

    return result;
}

void insertNode(treenode **root, int value){
    if(*root == NULL){
        *root = createNode(value);
        return;
    }

    if(*root != NULL){
        if(value < (*root)->value){
            insertNode(&(*root)->left, value);
        }else if(value > (*root)->value){
            insertNode(&(*root)->right, value);
        }else{
            //equal, no dupes allowed, do nothing
        }
    }

}

treenode *deleteNode(treenode *root, int value){
    if(root == NULL){
        printf("Nothing to Delete");
        return root;
    }else if(value < root->value){
        root->left = deleteNode(root->left, value);
        return root;
    }else if(value > root->value){
        root->right = deleteNode(root->right, value);
        return root;
    }else{
        if(root->left == NULL && root->right == NULL){ //case 1: no child
            free(root);
            root = NULL;
    
        }else if(root->left == NULL && root->right != NULL){ //case 2: 1 child, only right
            treenode *temp = root;
            root = root->right;
            free(temp);
        
        }else if(root->left != NULL && root->right == NULL){ //case 2: 1 child, only left
            treenode *temp = root;
            root = root->left;
           free(temp);
        }else{ //case 3: 2 children
            treenode *temp = findMax(root->left);// find max in left side
            root->value = temp->value;
            root->left = deleteNode(root->left, temp->value); // kill the duplicate node in that left subtree, after its deleted the return would be null so therefore the root->left is now null
        }

    }

    return root;
}

treenode *findMax(treenode *root){
    treenode *max = NULL;


    if(root->right != NULL){
        return findMax(root->right);
    }else{
        max = root;
        return max;
    }
}

void printTree_pre(treenode *root){
    if(root == NULL){
        return;
    }
    printf("%d ", root->value);
    printTree_pre(root->left);
    printTree_pre(root->right);
}

void printTree_inorder(treenode *root){
    if(root == NULL){
        return;
    }
    printTree_inorder(root->left);
    printf("%d ", root->value);
    printTree_inorder(root->right);
}

void printTree_post(treenode *root){
    if(root == NULL){  
        return;
    }
    printTree_post(root->left);
    printTree_post(root->right);
    printf("%d ", root->value);
}