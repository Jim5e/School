#include <stdio.h>
#include <stdlib.h>
#define MAX 7
#define INF 9999999

void print(int *arr, int count);
void tournamentSort(int *arr);


int main(){
    int arr[] = {4, 3, 6, 1, 10, 5, 7};
    // int arr[] = {10, 2, 7, 6, 5, 9, 12, 1};

    printf("BEFORE: ");
    print(arr, MAX);

    tournamentSort(arr);
    printf("AFTER: ");
    print(arr, MAX);

    return 0;
}

void tournamentSort(int *arr){
    //create new array of size 2n-1
    
    int tourSize = (MAX % 2 == 0? MAX * 2 - 1: MAX * 2);
    int *tour = calloc(tourSize, sizeof(int));

    //transfer data from og to tournament array
    int x, y;
    for(x = MAX - 1, y = tourSize - 1; x >= 0; x--, y--){
        tour[y] = arr[x];
    }

    //set up the tree: build every node and parent
    int LLPndx = (tourSize / 2) - 1;
    int parentsWithNdxChildren = (LLPndx / 2) - 1;
    for(; LLPndx > parentsWithNdxChildren; LLPndx--){//traverse and compete via children
        //select smallest child ndx of that parent
        int LCndx = LLPndx * 2 + 1;
        int RCndx = LCndx + 1;

        tour[LLPndx] = ((RCndx <= tourSize - 1) && tour[RCndx] < tour[LCndx] ? RCndx : LCndx);
    }

    //comparing children with index innards
    for(;parentsWithNdxChildren >= 0; parentsWithNdxChildren--){
        int LCndx = parentsWithNdxChildren * 2 + 1;
        int RCndx = LCndx + 1;
        tour[parentsWithNdxChildren] = (tour[tour[RCndx]] < tour[tour[LCndx]]? tour[RCndx]: tour[LCndx]); //we can get away with direct comparison since we know L and R exists
    }

    //at this point the root should be established
    arr[0] = tour[tour[parentsWithNdxChildren + 1]];
    tour[tour[parentsWithNdxChildren + 1]] = INF;



    ///////let ONLY the winner subtree fight going up
    for(int sortedcount = 1 ; sortedcount < MAX; sortedcount++){
        int winnerndx = tour[0]; //previous winner

        //directly compare children (children here would be either INF vs INF, or INF vs X where X is a real number)
        int parentndx = (winnerndx / 2) - 1;
        int LCndx = (parentndx * 2) + 1;
        int RCndx = LCndx + 1;
        tour[parentndx] = ((RCndx <= tourSize - 1) && tour[RCndx] < tour[LCndx] ? RCndx : LCndx);

        //direct compare children (children here would be indexes now, NOT actual value. indexes.)
        int child = tour[parentndx];
        for(;parentndx >= 0; parentndx = (child / 2) - 1){
            int parentndx = (child / 2) - 1;
            int LCndx = parentndx * 2 + 1;
            int RCndx = LCndx + 1;
            tour[parentndx] = (tour[tour[RCndx]] < tour[tour[LCndx]]? tour[RCndx]: tour[LCndx]);

            //
            child = parentndx;
        }

        arr[sortedcount] = tour[tour[0]];
        tour[tour[0]] = INF;
    }
        


}

void print(int *arr, int count){

    printf("[");
    for(int i = 0; i < count; i++){
        printf("%d", arr[i]);
        if(i < count - 1){
            printf(", ");
        }
    }
    printf("]\n");
}