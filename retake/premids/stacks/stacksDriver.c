#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// #include "stacksArray.h"
#include "stacksLinkedList.h"

int main(){
    stack MAIN;
    initStack(&MAIN);
    push(&MAIN, 'X');
    push(&MAIN, 'X');
    push(&MAIN, 'X');
    push(&MAIN, 'X');


    displayStack(&MAIN);
    return 0;
}