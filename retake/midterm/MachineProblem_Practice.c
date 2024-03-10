/******************************************************************
 * Project Name:  List, Set and Dictionary                        *
 * Programmer  :  Lawrence James A. Clarit                        *
 * Date Completed: ?                                 *
 ******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VH_SIZE     0XC    //size of Virtual Heap
#define OPEN_DSIZE  0XA    //size of Open Hash Table
#define CLOSE_DSIZE 0XC    //size of Close Hash Table
#define LIST_SIZE   0XF    //size of the array implementation of List
/******************************************************************************
 * Data Structure Definition:                                                 *
 ******************************************************************************/
typedef struct {  
	char name[24];          // Chocolate name  
 	int  weight;            // Chocolate weight in grams  
}chocoDesc;
 
typedef struct {
   char prodID[8];          //  product ID uniquely identifies the products; EMPTY or DELETED   
  	chocoDesc prodDesc;     //  product description 
 	float prodPrice;        //  product price 
  	int prodQty;            //  product count or quantity   
}product;                   //  product record  

typedef struct {
	product elem;            
	int next;                
}prodNode;                 // Product node, used in cursor-based implementation of Set  


/************************
 * Virtual Heap         *
 ************************/
typedef struct {
   prodNode VH_node[VH_SIZE];
   int avail;
}VHeap;

/******************************************
 * Cursor-Based Implementation of SET     *
 ******************************************/
typedef struct {
   int elemIndex;        // index of the 1st element in the set  
   int count;            // holds the actual number of elements in the set  
   VHeap *VHptr;         // holds the pointer to the virtual heap  
}cursorSet;            

/********************************************
 * Open Hashing Implementation of Dictionary*
 ********************************************/
typedef struct {
	int header[OPEN_DSIZE];  // array of sets   
	int count;               // total number of elements in the dictionary  
	VHeap *dicVHptr;         // holds the pointer to the virtual heap  
}openDic;


/**********************************************
 * Closed Hashing with 2 pass loading          *
 **********************************************/
#define EMPTY   "empty"     // stored in product ID field  
#define DELETED  "del"      // stored in product ID field * 
 
typedef product closeDic[CLOSE_DSIZE];   //Definition of the closed hash dictionary
  
typedef struct {
	product prod[LIST_SIZE];
	int last;   //index of the last element; -1 if list is empty	
}List;



/**********************************************************
 * Function Prototypes                                    *
 *********************************************************/
//---Problem #1 ---
void initVHeap(VHeap *VH);
cursorSet initCursorSet(VHeap *VH);
void displayVHeap(VHeap V);
void displaySet(cursorSet A);

//---Problem #2 ---
int mallocInVHeap(VHeap *VH);
void insertSorted(cursorSet *A, product P);
void populateSet(cursorSet *A);

//---Problem #3 ---
int openHash(char *IDen);                
openDic initOpenDict(VHeap *VH);
openDic convertToOpenDict(cursorSet *A);
void displayOpenDict(openDic D);

//---Problem #4 ---
void freeInVHeap(VHeap *VH, int ndx);
void deleteDict(openDic *D, char *IDen);

//---Problem #5 ---
int closeHash(char *ID);
void initCloseDict(closeDic CD);
closeDic * convertToCloseDict(openDic *D);	
void displayCloseDict(closeDic CD);


 
/************************************************************************************
 * READ ME FIRST before ANSWERING                                                   *
 *   1)  To facilitate the checking of the machine problem, follow the instructions *
 *       in each PROBLEM #.                                                         *
 *   2)  To accomplish the task for each PROBLEM, a series of function calls may be *
 *       necessary.                                                                 *  
 *   3)  Write you answer BELOW THE COMMENTS. DO NOT DELETE COMMENTS                *
 *                                                                                  *
 ***********************************************************************************/
 int main( ) 
 {	
 /*---------------------------------------------------------------------------------
 * 	Problem #1 ::  1) Initializes the virtual heap and the cursor Set             *
 *                 2) Displays the contents  virtual heap and cursor Set          *
 *--------------------------------------------------------------------------------*/
 	printf("\n\n\nProblem #1:: "); 
 	printf("\n------------");
 	//Declare variables needed for Problem #1
 	VHeap MAIN;
	
 	//Function Calls for Problem #1
	initVHeap(&MAIN);
	cursorSet catcher = initCursorSet(&MAIN);

	displayVHeap(MAIN);
	displaySet(catcher);
/*---------------------------------------------------------------------------------
 * 	Problem #2 ::  1) Populates the Cursor set which is sorted in ascending order *
 *                    according to ID                                             *
 *                 2) Displays the Cursor set                                     * 
 *--------------------------------------------------------------------------------*/	 
 	printf("\n\n\nProblem #2:: "); 
 	printf("\n------------");
	//Declare variables needed for Problem #2
	
 	//Function Calls for Problem #2
	populateSet(&catcher);
	displaySet(catcher);

/*---------------------------------------------------------------------------------
 * 	Problem #3 ::  1) Converts the Cursor set into an Open Hash Dictionary        *      
 *                 2) Displays the Open Hash Dictionary                           *
 *                 3) Displays the empty Cursor set.                              * 
 *--------------------------------------------------------------------------------*/	
	printf("\n\n\nProblem #3:: "); 
 	printf("\n------------");
	//Declare variables needed for Problem #3

	
 	//Function Calls for Problem #3
	openDic OPENDICT = convertToOpenDict(&catcher);
	displayOpenDict(OPENDICT);
	displaySet(catcher);

/*---------------------------------------------------------------------------------
 * 	Problem #4 ::  1) Perform 3 delete operations on the Open Hash Dictionary     *
 *                 2) Displays the Open Hash Dictionary                           *
 *                 3) Displays the Virtual Heap                                   * 
 *--------------------------------------------------------------------------------*/	
 	printf("\n\n\nProblem #4:: "); 
 	printf("\n------------");	
 //Declare variables needed for Problem #4
    char delete01[] = "1703";
    char delete02[] = "1358";    
	char delete03[] = "1601";

 
//Function Calls for Problem #4	    
    deleteDict(&OPENDICT, delete01);
	deleteDict(&OPENDICT, delete02);
	deleteDict(&OPENDICT, delete03);
	displayOpenDict(OPENDICT);
	displayVHeap(MAIN);
    

/*------------------------------------------------------------------------------------
 * 	Problem #5 :: 1) Converts the Open Hash Dictionary into a Closed Hash Dictionary *
 *                2) Displays the Closed Hash Dictionary                             * 
 *                3) Displays the virtual heap  
 *                                     *
 *---------------------------------------------------------------------------------*/	
	printf("\n\n\nProblem #5:: ");
    printf("\n------------");
    //Declare variables needed for Problem #5
	closeDic *CLOSED = convertToCloseDict(&OPENDICT);
    
    
    //Function Calls for Problem #5
	displayCloseDict(*CLOSED);
	displayVHeap(MAIN);

	return 0;
}

/************************************************************
 *  Problem 1:: Function Definitions                          *
 ************************************************************/
 void initVHeap(VHeap *V)
 {
 	V->avail = VH_SIZE-1;

	//Link each node
	for(int i = V->avail; i >= 0; i--){
		V->VH_node[i].next = i-1;
		strcpy(V->VH_node[i].elem.prodID, "    ");
	}
 }

cursorSet initCursorSet(VHeap *VH)
{
	cursorSet newSet;

	newSet.elemIndex = -1;
	newSet.count = 0;
	newSet.VHptr = VH;
    
	return newSet;
}

void displayVHeap(VHeap V)
{
	//Variable Declaration here
	int i,j;

    printf("\n\nDetails of the Virtual Heap :: ");
    printf("\n------------------------------");
    printf("\nAvailable Index  ::  %d", V.avail  );       //Complete this statement
	printf("\nVHeap Address    ::  %p" , &V.VH_node );       //Complete this statemet
	
    printf("\n\n%10s", "Index");
    printf("%10s", "Prod ID");
    printf("%15s", "Next Field");
	printf("\n%10s%10s%15s", "-----", "-------","----------");	
     
    //Write your code here 
	 for(int i = 0; i < VH_SIZE; i++){
		printf("\n\n%10d", i);
		printf("%10s", V.VH_node[i].elem.prodID);
		printf("%15d", V.VH_node[i].next);
	 }


	printf("\n\n"); system("Pause");
}

void displaySet(cursorSet A)
{
	int x;
	product p;
	
	printf("\n\nDetails of the Set :: ");
	printf("\n---------------------");
	printf("\nNo. of elements ::  %d", A.count );      //Complete this code
	printf("\n\n%-7s", "ID");
	printf("%-12s","Choco Name");
	printf("%-15s","Choco Weight");
	printf("%-10s","VHeap Index");
	printf("\n%-7s%-12s%-15s%-10s", "--", "----------", "------------", "-----------");

	//Write your code here
	 for(int i = A.elemIndex; i != -1; i = A.VHptr->VH_node[i].next){
		printf("\n\n%-7s", A.VHptr->VH_node[i].elem.prodID);
		printf("%-12s",A.VHptr->VH_node[i].elem.prodDesc.name);
		printf("%-15d",A.VHptr->VH_node[i].elem.prodDesc.weight);
		printf("%-10d",i);
	 }
	 

	printf("\n\n"); system("Pause");	
}


/************************************************************
 *  Problem 2:: Function Definitions                         *
 ************************************************************/
int mallocInVHeap(VHeap *VH)
{
 int retval = VH->avail;

 if(retval != -1){
	VH->avail = VH->VH_node[retval].next;
 }
 return retval;
}


void insertSorted(cursorSet *A, product P) 
{
		int *trav;
		for(trav = &(A->elemIndex);
			*trav != -1 && strcmp(P.prodID, A->VHptr->VH_node[*trav].elem.prodID) > 0;
			trav = &(A->VHptr->VH_node[*trav].next)){}

		if(*trav == -1 || strcmp(P.prodID, A->VHptr->VH_node[*trav].elem.prodID) != 0){
			int newNode = mallocInVHeap(A->VHptr);
			if(newNode != -1){
				A->VHptr->VH_node[newNode].elem = P;
				A->VHptr->VH_node[newNode].next = *trav;
				*trav = newNode;
				A->count++;
			}else{
				printf("\nNo available space. Product with ID: %s cannot be inserted.", P.prodID);
			}

		}else{ //already exists
			printf("\nProduct with ID: %s already exists in the set.", P.prodID);
		}
}

void populateSet(cursorSet *A)
{
	const int COUNT = 15;
	product data[] = { 	{"1701", {"Toblerone", 135}, 150.75, 20},
						{"1356", {"Ferrero", 200}, 250.75, 85},
						{"1109", {"Patchi", 50}, 99.75, 35},
						{"1550", {"Cadbury", 120}, 200.00, 30},
						{"1807", {"Mars", 100}, 150.75, 20},
						{"1201", {"Kitkat", 50}, 97.75, 40},
						{"1450", {"Ferrero", 100},150.50, 50},
						{"1701", {"Toblerone", 50}, 90.75, 80},
						{"1601", {"Meiji", 75}, 75.50, 60},
						{"1310", {"Nestle", 100}, 124.50, 70},
						{"1807", {"Valor", 120}, 149.50, 90},
						{"1455", {"Tango", 75}, 49.50, 100},
						{"1703", {"Toblerone", 100}, 125.75, 60},
						{"1284", {"Lindt", 100}, 250.75, 15},
						{"1688", {"Guylian", 50}, 99.75, 35},
					
		              };
    //Inserts each element of the array to the cursor set
    //Write your code here!!
	for(int i = 0; i < COUNT; i++){
		insertSorted(A, data[i]);
	}
 
 
}



/************************************************************
 *  Problem 3:: Function Definitions                        *
 ************************************************************/
int openHash(char * prodID) { 
    int sum = 0;
    for (int i = 0; prodID[i] != '\0'; i++) {
            sum += prodID[i] - '0';
    }
    return sum % OPEN_DSIZE;
}


openDic initOpenDict(VHeap *VH)
{
	openDic newDic;
	newDic.count = 0;
	newDic.dicVHptr = VH;

	for(int i = 0; i < OPEN_DSIZE; i++){
		newDic.header[i] = -1;
	}

	return newDic;
}

openDic convertToOpenDict(cursorSet *A) //can be better but kapoy na
{
	openDic OPEN = initOpenDict(A->VHptr);

	//deleteFirst cursorSet
	while(A->elemIndex != -1){
		int temp = A->elemIndex; //save location of temp
		int ndx = openHash(A->VHptr->VH_node[temp].elem.prodID); //get hash of temp
		product DATA = A->VHptr->VH_node[temp].elem; //save temp's data
		A->elemIndex = A->VHptr->VH_node[temp].next; //adjust
		A->VHptr->VH_node[temp].next = A->VHptr->avail; //free temp()
		A->VHptr->avail = temp;
		A->count = A->count - 1;

		//Insert temp inside openDic
		int *trav = NULL;
		for(trav = &(OPEN.header[ndx]); *trav != -1 && strcmp(DATA.prodID, A->VHptr->VH_node[*trav].elem.prodID) > 0; trav = &(A->VHptr->VH_node[*trav].next)){}

		if(*trav == -1 || strcmp(DATA.prodID, A->VHptr->VH_node[*trav].elem.prodID) != 0){
			int newNode = mallocInVHeap(A->VHptr);

			if(newNode != -1){ //add to openDic
				A->VHptr->VH_node[newNode].elem = DATA;
				A->VHptr->VH_node[newNode].next = *trav;
				*trav = newNode;
				OPEN.count = OPEN.count + 1;
			}
		}
	}
	
	
	return OPEN;
}



void displayOpenDict(openDic D)
{
	//Variable declaration here 
	
	printf("\n\nDetails of the Open Hash Dictionary:: ");
	printf("\n-------------------------------------");
	
	printf("\nNo. of elements :: %d", D.count);
	printf("\n\n%-7s", "GROUPS");
	printf("%15s","ID Numbers");
	printf("\n%-7s%15s", "------","----------");
	
	//Write your code here
	for(int x = 0; x < OPEN_DSIZE; x++){
		printf("\n\nGroup[%d]:",x);
		for(int trav = D.header[x]; trav != -1; trav = D.dicVHptr->VH_node[trav].next){
		printf("%15s", D.dicVHptr->VH_node[trav].elem.prodID);
		}	
	}

    printf("\n\n"); system("Pause");	
}


/************************************************************
 *  Problem 4:: Function Definitions                        *
 ************************************************************/
void freeInVHeap(VHeap *VH, int ndx)
{
	 VH->VH_node[ndx].next = VH->avail;
	 VH->avail = ndx;
}

void deleteDict(openDic *D, char *IDen)
{	
	int *trav;
	int hash = openHash(IDen);
	for(trav = &(D->header[hash]); *trav != -1 && strcmp(IDen, D->dicVHptr->VH_node[*trav].elem.prodID) > 0; trav = &(D->dicVHptr->VH_node[*trav].next)){}

	if(*trav != -1){
		int temp = *trav;
		*trav = D->dicVHptr->VH_node[temp].next;
		freeInVHeap(D->dicVHptr, temp);
		D->count--;
		printf("\nProduct with ID: %s is successfully deleted.", IDen);

	}else{
		printf("\nProduct with ID: %s does NOT exists in the OPEN dictionary.", IDen);
	}
}


 /************************************************************
 *  Problem 5:: Function Definitions                        *
 ************************************************************/
int closeHash(char *ID)
{
    int sum = 0;
    for (int i = 0; ID[i] != '\0'; i++) {
            sum += ID[i] - '0';
    }
    return sum % CLOSE_DSIZE;
}



void initCloseDict(closeDic CD)
{
	 for(int i = 0; i < CLOSE_DSIZE; i++){
		strcpy(CD[i].prodID, EMPTY);
		strcpy(CD[i].prodDesc.name, "    ");
	 }

}
 
closeDic * convertToCloseDict(openDic *D) //Its wordy para readable, i didnt want to be clever nya libog2 basahon
{	
	//init placeholder synonym array & closeDic
    List synonyms;
	synonyms.last = -1;
	closeDic *PRIMES = (closeDic *) malloc (sizeof(*PRIMES));

	//deleteFirst openHash
	if(*PRIMES != NULL){
	initCloseDict(*PRIMES);
		for(int K = 0; K < OPEN_DSIZE; K++){
			int *trav;
			for(trav = &(D->header[K]); *trav != -1;){
				int temp = *trav;
				*trav = D->dicVHptr->VH_node[temp].next;

				//transfer temp's data into the closeHash
				int closeNdx = closeHash(D->dicVHptr->VH_node[temp].elem.prodID);

				if(strcmp(D->dicVHptr->VH_node[temp].elem.prodID, EMPTY)==0){ // if its empty, insert it.
					(*PRIMES)[closeNdx] = D->dicVHptr->VH_node[temp].elem;
				}else{ // place in synonyms array
					synonyms.last++;
					int synNdx = synonyms.last;
					synonyms.prod[synNdx] = D->dicVHptr->VH_node[temp].elem;
				}

				//free temp
				freeInVHeap(D->dicVHptr, temp);
				D->count--;
			}
		}

		//2nd pass, insert synonyms back into closeDic
		for(int i = 0; i <= synonyms.last; i++){
			int closeNdx = closeHash(synonyms.prod[i].prodID);

			//traverse closeDic to check for valid placement
			int cmp = 0;
			int pos;
			for(pos = closeNdx; cmp < CLOSE_DSIZE && strcmp((*PRIMES)[pos].prodID, EMPTY) != 0; pos = (pos + 1) % CLOSE_DSIZE){
				cmp++;
			}

			(*PRIMES)[pos] = synonyms.prod[i];
		}
	}

	return PRIMES;

}	

void displayCloseDict(closeDic CD)
{
 	//Variable declaration here
 	
 	
	printf("\n\nDetails of Closed Hash Dictionary :: ");
	printf("\n-------------------------------------");
	printf("\n\n%-6s", "Index");
	printf("%-10s", "ChocoID");
	printf("%-15s", "Choco Name");
	printf("\n%-6s%-10s%-15s", "-----", "-------", "----------"); 
	
	//Write your code here
	for(int i = 0; i < CLOSE_DSIZE;i++){
		printf("\n\n%-6d", i);
		printf("%-10s", CD[i].prodID);
		printf("%-15s", CD[i].prodDesc.name);
	}
	 
	
	printf("\n\n"); system("Pause");
 
}
 
