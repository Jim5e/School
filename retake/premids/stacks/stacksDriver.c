#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stacksArray.h"
// #include "stacksLinkedList.h"

int main(){
    identifier();
    stack MAIN;
    initStack(&MAIN);
    push(&MAIN, 'X');
    push(&MAIN, 'J');
    // push(&MAIN, 'X');
    // push(&MAIN, '2');


    displayStack(&MAIN);
    return 0;
}