#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

typedef struct node{
	int data;
	struct node *link;
	
}*LIST;

typedef LIST Dictionary[MAX];

int hash(int num);
void initDict(Dictionary *A);

int main(){
	Dictionary A;
	initDict(&A);

	return 0;
}

int hash(int num){
	
	return (num % MAX); //categorizing by tens place, since MAX = 10
}

void initDict(Dictionary *A){
	int i;
	
	while (i < MAX){
		LIST newNode = malloc(sizeof(struct node));	
		(*A)[i] = newNode;
		i++;
	}
	
	
}

