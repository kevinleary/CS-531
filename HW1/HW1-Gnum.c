/*
Kevin Leary 
G01357635
*/

/*
Running instructions: 
 1. Open terminal 
 2. `gcc -o HW1-Gnum HW1-Gnum.c`
 3. ./HW1-Gnum

 OR 

 1. use the runner.sh
*/

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 26

//Adhered to UDF and also added some helper functions...
void inputStrings(char str[10][MAXSIZE]);
int checkDuplicate(char s1[], char s2[]);
int checkStringLen(char s[]);
int checkLegalCharacters(char s[]);
void ascendingSort(char sortOrder, char str[10][MAXSIZE]);
char getSortOrder();
void displayHighestandLowest(char sortOrder, char str[10][MAXSIZE]);


int main() {

    // 2D char array of 10 x 26 (MAXSIZE)
    char str[10][MAXSIZE];

    //Calling all functions
    inputStrings(str);
    char sortOrder = getSortOrder();
    ascendingSort(sortOrder, str);
    displayHighestandLowest(sortOrder, str);


    return 0;
}

// Helper function to display highest and lowest ASCII values
void displayHighestandLowest(char sortOrder, char str[10][MAXSIZE]){

    // We already know highest and lowest because its sorted from the ascending sort function
    if ( sortOrder == 'A') {
        printf("\nString with lowest ASCII value: %s", str[0]);
        printf("String with highest ASCII value: %s", str[9]);
    } else {
        printf("\nString with lowest ASCII value: %s", str[9]);
        printf("String with highest ASCII value: %s", str[0]);
    } 

}

// Helper function to determine whether the array will be output in ascending or descending order
char getSortOrder(){
    
    char sortOrder;
    //get ascending or descending
    for (int i = 0; i < 1; i++) {
        printf("Print character strings in Ascending or Descending order...\nEnter 'A' for Ascending or 'D' for Descending: ");
        scanf("%c", &sortOrder);

        //Eliminate the upper or lower case issues
        if ( sortOrder == 'A' || sortOrder == 'a' ) {
            sortOrder = 'A';
        } else if ( sortOrder == 'D' || sortOrder == 'd' ) {
            sortOrder = 'D';
        } else {        // - This is for error input
            i--;
            printf("\nError: %c is not 'A' or 'D' - try again...\n", sortOrder);
            //Empty Character constant
            sortOrder = '\0';
            continue;
        }
    }
    return sortOrder;
}

// Function that sorts the array
void ascendingSort(char sortOrder, char str[10][MAXSIZE]) {

    // Iterate through the strings 
    // Nested for loop that iterates through everything = o(n)^2 ... I know- inefficient! 
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if ( (strcmp(str[i], str[j]) < 0) && (sortOrder == 'A') ) { // - Check for the sort 
                //Classic temp swapping and holding
                char temp[MAXSIZE];
                strcpy(temp, str[i]);
                strcpy(str[i], str[j]);
                strcpy(str[j], temp);
            }

            if ( (strcmp(str[i], str[j]) > 0) && (sortOrder == 'D') ) {
                char temp[MAXSIZE];
                strcpy(temp, str[i]);
                strcpy(str[i], str[j]);
                strcpy(str[j], temp);
            }
        }
    }

    // print the list back with headings
    if (sortOrder == 'A') {
        printf("\nAscending Order:\n\n");
    } else {
        printf("\nDescending Order:\n\n");
    }

    for (int i = 0; i < 10; i++) {
        printf("%s", str[i]);
    }
    
}

// Function that checks for legal characters as defined in the assignment
int checkLegalCharacters(char s[]){
    int j = 0;
    for (j = 0; j < strlen(s); j++) {
        if (s[j] == '!' || s[j] == '@' || s[j] == '#' || s[j] == '$' || s[j] == '%' || s[j] == '^' || s[j] == '(' || s[j] == ')') {
            printf("Error: %c is an illegal character - please re-enter\n", s[j]);
            return 1; 
        } 
    }
    return 0;
}

// Function that checks for the string length as defined in the assignment
int checkStringLen(char s[]){
    if (strlen(s) == 1) {
        printf("Error: string is empty - please re-enter\n");
        return 1;
    } else if (strlen(s) == 2 || strlen(s) == 3) {
        printf("Error: string too few characters - please re-enter\n");
        return 1;
    } else if (strlen(s) >= 26) {
        printf("Error: string too many characters - please re-enter\n");
        return 1; 
    } else {
        return 0;
    }
}

//Following strcmp() return value range... negative values to 0 then to positive values. although only a 0 or 1 is necessary
int checkDuplicate(char s1[], char s2[]){
    if(strcmp(s1, s2) == 0){
        printf("Error: duplicate string - please re-enter\n");
        return 0;
    } else {
        return 1;
    }
}

// Function where all strings are input. Calls the check functions to meet assignment requirements
void inputStrings(char str[10][MAXSIZE]) {

    int dup = 0;
    int i;
    int j;
    // Prompt the user for 10 strings
    for (i = 0; i < 10; i++) {
        printf("Enter string %d: ", i + 1);
        fgets(str[i], MAXSIZE, stdin);    

        printf("String length is: %zu\n", strlen(str[i]));

        if (checkDuplicate(str[i-1], str[i]) == 0){
            i--;
            continue;
        }

        // Check if the string is empty
        if (checkStringLen(str[i]) == 1) {
            i--;
            continue;
        }

        // Check legal characters
        if (checkLegalCharacters(str[i]) == 1){
            i--;
            continue;
        }
    }
}
