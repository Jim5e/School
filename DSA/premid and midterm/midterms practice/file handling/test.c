#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

typedef struct {
	char FN[24]; //firstname
	char MI; //middle initial
	char LN[16]; //lastname
}Nametype;

typedef struct {
	Nametype name;
	int ID;
	char course[8]; //BSCS, BSIS, BSIT
	int yrLevel;
}Studtype;

//C] Function Prototypes
void displayHeader();
void displayStudent(Studtype S[]);
void readFile(Studtype *B);

int main(){
	Studtype B[MAX];
	readFile(B);
	displayStudent(B);
	return 0;
}

void readFile(Studtype *B)
{
    FILE *fp;
    int limit = 1;
    char fileToRead[30];
    printf("Enter file to read (eg. file.txt):\n");
    scanf("%s", &fileToRead);
    if (!(fp = fopen(fileToRead, "rb")))
    {
        printf("Could not open file / File Does not exist");
    }
    else
    {
        displayHeader();
        int i = 0;
        while (fread(&B[i], sizeof(Studtype), 12, fp)){ 
        	if(i < MAX){
        		i++;
			}
        }
        
       fclose(fp);  
    }
}

void displayHeader()
{
printf("\n\n");
printf("%-10s", "ID No.");
printf("%-16s", "Lastname");
printf("%-24s", "Firstname");
printf("%-3s", "MI");
printf("%-8s", "Course");
printf("%5s", "Year");
printf("\n");
printf("%-10s", "======");
printf("%-16s", "========");
printf("%-24s", "=========");
printf("%-3s", "==");
printf("%-8s", "======");
printf("%5s", "====");
}

void displayStudent(Studtype S[]) {
	int i = 0;
	
	while(i < MAX){
    printf("\n");
    printf("%-10d", S[i].ID);
    printf("%-16s", S[i].name.LN);
    printf("%-24s", S[i].name.FN);
    printf("%-3c", S[i].name.MI);
    printf("%-8s", S[i].course);
    printf("%5d", S[i].yrLevel);
	i++;	
	}

}

