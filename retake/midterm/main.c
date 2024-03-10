#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXORDERS 20
#define CUSTBUCKETS 10

int lastOrderNumber = 10000;

typedef enum{OPEN, CLOSED} orderStatus;  //used in Closed Hashing of Orders
typedef enum{PREPARING, SERVED} pizzaStatus;
typedef unsigned char toppingsCW;       //Computer Word representation of toppings
typedef int toppingsBW[8];              //Bit Vector representation of toppings




typedef struct{
    char pizzaName[32];
    toppingsBW pizzaToppings;
}pizzaType;

typedef struct pizzaNode{
    pizzaType P;
    pizzaStatus pStat;                  //PREPARING by default
    struct pizzaNode* nextPizza;
}pizzaNode, *pizzaList;

typedef struct{
    char fName[64];
    char lName[32];
}nameDetails;

typedef struct{
    char customerID[9];
    nameDetails custName;
}customer;

typedef struct customerNode{
    customer C;
    struct customerNode* nextCust;
}customerNode, *custList;

typedef custList cDict[CUSTBUCKETS];    //Open Hashing Representation of Customers

typedef struct{
    int orderNumber;
    customer cust;
    pizzaList pList;
    orderStatus stat;                   //OPEN by default
}orderType;

typedef struct{
    orderType orderList[MAXORDERS];
    int numOrders;
}orderList;                             //Closed Hashing Representation of Orders

void createCustomerFile(void)
{
    customer customers[] = {
            {"CUST001", {"SEAN ANSELMO", "ABELLANA"}},
            {"CUST002", {"VICTOR", "AGUHOB"}},
            {"CUST003", {"YEVGENY GRAZIO MARI", "ALBAÑO"}},
            {"CUST004", {"MIGUEL CARLOS", "BERINGUEL"}},
            {"CUST005", {"KARYLLE", "BERNATE"}},
            {"CUST006", {"RAYNOR", "BUHIAN"}},
            {"CUST007", {"NIÑO JAN", "CABATAS"}},
            {"CUST008", {"KENNETH JOHN", "CANTILLAS"}},
            {"CUST009", {"VINCEADE", "CENTINO"}},
            {"CUST010", {"JUN", "CHEONG"}},
            {"CUST011", {"CERIL", "HEYROSA"}},
            {"CUST012", {"JEREMIAH JACOB ANTHONY", "JUINIO"}},
            {"CUST013", {"JIWOO", "JUNG"}},
            {"CUST014", {"XANDER JACOB", "LABIDE"}},
            {"CUST015", {"ACHILLE LORENZO", "LANUTAN"}},
            {"CUST016", {"MATT VINCENT", "MAGDADARO"}},
            {"CUST017", {"GREGG ALEXANDER", "MARAYAN"}},
            {"CUST018", {"JASPER LEE", "MARBELLA"}},
            {"CUST019", {"DAN LIUS", "MONSALES"}},
            {"CUST020", {"SHAWN RYAN", "NACARIO"}},
            {"CUST021", {"SHANNEN", "NAZARENO"}},
            {"CUST022", {"OIEU ZHYDD", "NUÑEZA"}},
            {"CUST023", {"MARC NELSON", "OCHAVO"}},
            {"CUST024", {"RAY EMANUEL", "PATALINGHUG"}},
            {"CUST025", {"NATHAN ELDRIDGE MITNICK", "PERNITES"}},
            {"CUST026", {"LANCE JUSTIN", "RAMOS"}},
            {"CUST027", {"KENT JOSEPH", "RICONALLA"}},
            {"CUST028", {"JOSHUA LOUI", "SOQUEÑO"}},
            {"CUST029", {"ASHLENGAIL", "VICTOR"}},
            {"CUST030", {"MURLIWANI", "GANGARAM"}}
        };
        FILE* file = fopen("customers.txt", "w");
        if (file != NULL) {
            for (int i = 0; i < sizeof(customers) / sizeof(customers[0]); i++) {
                fwrite(&customers[i], sizeof(customer), 1, file);
            }
        }
        fclose(file);
}


#define EMPTY -1
void initorderList(orderList *OD){
        OD->numOrders = 0;

        //set EMPTY
        for(int i = 0; i < MAXORDERS; i++){
            OD->orderList[i].orderNumber = EMPTY;
        }
        
}

/*
 initCustomerDict() = This function will receive as parameter a cDict, which is an array of custList (Linked List of Customers). The function will initialize the dictionary by setting each element in cDict to be empty.
 */
void initCustomerDict(cDict customers)
{
    for(int i = 0; i < CUSTBUCKETS; i++){
        customers[i]->nextCust = NULL;
    }
}

/*
 hashCustomer() = This function will receive as a parameter a customerID. The function will add up the first 3 digits in the customerID and let the remainder of the sum when divided by 10 be returned to the calling function.
 */
int hashCustomer(char customerID[])
{
    int retVal = -1;
    
    //how do i check for validity here??? theres no initCustomer to set placeholder for ID's value
    int first = strlen(customerID) - 1; //if di pwede using another lib then id just
    int second = first - 1;         // traverse till '/0', then do count backwards
    int third = second - 1;
    retVal = (customerID[first] - '0') + (customerID[second] - '0') + (customerID[third] - '0');


    return retVal % 10;
}

/*
 addNewCustomer() = This function will add a new customer to the cDict given a customer record. The function will only add the customer if the customer does not yet exist. Also, the customer is inserted into its proper "bucket" (linked list at index N based on hash). The new customer should be inserted in its proper place in the list, sorted ascending by family name.
 */
void addNewCustomer(cDict customers, customer C)
{
    //check if exist
    int hash = hashCustomer(C.customerID);

    custList *trav;

    //locate proper position
    for(trav = &(customers[hash]); *trav != NULL && strcmp(C.custName.lName, (*trav)->C.custName.lName) > 0; trav = &(*trav)->nextCust){
    }

    //if it reached the end, it means it doesnt exist OR C is no longer > node.
    if(*trav == NULL || strcmp(C.custName.lName, (*trav)->C.custName.lName) != 0){
        custList newNode = malloc (sizeof(customerNode));
        if(newNode != NULL){
            newNode->C = C;
            newNode->nextCust = *trav;
            *trav = newNode;
        }
    }
}

/*
 populateCustomers() = This function will read a file "customers.txt", and populate the given cDict with the customer records in the file. You may use the previously written functions for this function.
 */
void populateCustomers(cDict customers){

}

/*
 buildPizza() = This function will receive as parameter a pizzaName, and a list of toppings represented in computer word. Each bit in the CW representation represent the ff:
        0000 0000
        8765 4321
    1 - Pepperoni
    2 - Ham
    3 - Onions
    4 - Pineapples
    5 - Bacon
    6 - Olives
    7 - Bell Peppers
    8 - Mushrooms
    
    For example: A Hawaiian Pizza with mushrooms, pineapples, and pepperoni is represented as: 1000 0101.
 
    Once the pizza record has been built, return it to the calling function.
 */
pizzaType buildPizza(char pizzaName[], toppingsCW toppings)
{
    pizzaType retVal = {};

    //transfer name
    strcpy(retVal.pizzaName, pizzaName);

    //transfer toppings
    toppingsCW mask = 1 << (sizeof(mask) * 8) - 1;

    for(int i = 7; i != 0 && mask > 0;mask = mask >> 1){
        if((mask & toppings) == 0){
            retVal.pizzaToppings[i] = 0;
        }else{
            retVal.pizzaToppings[i] = 1;
        }
        
        i--;
    }
    
    return retVal;
}

/*
 hashOrder() = The function will receive an orderID as parameter. The function will take the last 4 digits of the orderID, and return the remainder when it is divided by 20.
 */

int hashOrder(int orderID)
{
    int retVal = -1;

    retVal = orderID % 10000;

    return retVal % 20;
}

/*
 orderPizza() = This function will receive an orderList, a cDict, a customerID, and a pizza to order. The function will add a new order to the orderList for the given customerID and pizza record. Update any fields as necessary. Only add the order if the customer exists. Resolve any collisions using linear probing.
 */

void orderPizza(orderList* orders, cDict customers, char customerID[], pizzaType pizza)
{
    //check if customer is there
    int hash = hashCustomer(customerID);

    custList trav;
    for(trav = customers[hash]; trav != NULL && strcmp(customerID,trav->C.customerID) > 0; trav = trav->nextCust){
    }

    if(trav != NULL){ //i.e. it found the customer

        //check if there is space in orderList left
        if(orders->numOrders < MAXORDERS){

            //get pizza hash
            int pos = hashOrder(trav->C.customerID);

            //check if theres a valid position for the newOrder to be created within orderList
            int cmp; //comparisons
            for(cmp = 0;cmp < orders->numOrders && strcmp(orders->orderList[pos].orderNumber, EMPTY) != 0; pos = (pos + 1) % MAXORDERS){
                cmp++;
            }

            //when for loop breaks, it means we found an EMPTY cell to add the order
            //we can do insertFirst for pizzaList since no order was specified
            pizzaList newNode = (pizzaList) malloc (sizeof(struct pizzaNode));
            if(newNode != NULL){
                newNode->P = pizza; //add pizza elem
                newNode->pStat = PREPARING; //set status of pizza
                newNode = orders->orderList[pos].pList; //link
                orders->orderList[pos].pList = newNode; //link
                orders->orderList[pos].stat = OPEN; //indicate order's status
                orders->numOrders++; //update num of orders
                orders->orderList[pos].cust = trav->C; //copy customer data
                orders->orderList[pos].orderNumber = lastOrderNumber++; //create new orderNumber
            }

            
        }
    }else{
        printf("Customer with ID: %s does not exist within cDict.", customerID);
    }
}

/*
 servePizza() = This function will receive an orderList, an orderNumber and a pizzaName. The function will go through the given orderList and the pizzas for the specified orderNumber. If the pizza exists, then update the pizzaStatus to be SERVED.
 */
void servePizza(orderList* orders, int orderNumber, char pizzaName[])
{   
    int i;

    //locate order
    for(i = 0; i < MAXORDERS && orders->orderList[i].orderNumber != orderNumber; i = (i + 1) % MAXORDERS){
    }

    //if its found
    if(orders->orderList[i].orderNumber == orderNumber){
        pizzaList trav = orders->orderList[i].pList;
        for(;trav != NULL && strcmp(trav->P.pizzaName, pizzaName) != 0; trav = trav->nextPizza){
        } //locate pizza

        //if pizza is found
        if(strcmp(trav->P.pizzaName, pizzaName) == 0){
            trav->pStat = SERVED; //update status
        }
    }
}

/*
 updateOrderStatus() = This function will receive an orderList and an orderID. The function will go through the list of pizzas in the order record of the given orderID, and check if all of the pizzas have been SERVED. If they have all been SERVED, then the function will update the orderStatus to CLOSED.
 */
void updateOrderStatus(orderList* orders, int orderNumber)
{   
    int i;
    for(i = 0; i < MAXORDERS && orders->orderList[i].orderNumber != orderNumber; i++){
    }

    if(orders->orderList[i].orderNumber == orderNumber){
        pizzaList trav;
        for(trav = orders->orderList[i].pList;trav != NULL && trav->pStat != PREPARING; trav = trav->nextPizza){
        }

        if(trav == NULL){
            orders->orderList[i].stat = CLOSED;
        }
    }
}

/*
 displayOrderList() = This function will go through each order in the orderList and display each of the orders in the ff: format:
 
    OrderNumber:
    Customer ID:
    Customer Name:
    Pizza Orders: pizzaName1(SERVED) -> pizzaName2(PREPARING)
    Order Status:
 */

void displayOrderList(orderList orders)
{
    for(int i = 0; i < MAXORDERS; i++){
        printf("\nOrderNumber: %d",orders.orderList[i].orderNumber);
        printf("\nCustomer ID: %s",orders.orderList[i].cust.customerID);
        printf("\nCustomer Name: %s %s",orders.orderList[i].cust.custName.fName, orders.orderList[i].cust.custName.lName);
        for(pizzaList trav = orders.orderList[i].pList; trav != NULL; trav = trav->nextPizza){
            printf("%s %s",trav->P.pizzaName,trav->pStat);
        }
        
        updateOrderStatus(&orders,orders.orderList[i].orderNumber);
        printf("Order Status: %s", orders.orderList[i].stat);
    }
}

int main(void)
{
	createCustomerFile();

    //read customer file here i guess?
    
    return 0;
}
