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

void inputStrings(char str[10][MAXSIZE]);
int checkDuplicate(char s1[], char s2[]);
int checkStringLen(char s[]);
int checkLegalCharacters(char s[]);
// int calculateASCII(char str[10][MAXSIZE]);
void outputStringComp(char str[10][MAXSIZE]);
void ascendingSort(char str[10][MAXSIZE]); // - need to define this then done!

int main() {

    char str[10][MAXSIZE];

    inputStrings(str);
    // calculateASCII(str);
    outputStringComp(str);
    ascendingSort(str);


    return 0;
}

void ascendingSort(char str[10][MAXSIZE]) {

    char *ascending;
    // char *sortOrder; 
    int sortOrder;
    //get ascending or descending
    for (int i = 0; i < 1; i++) {
        printf("Print character strings in Ascending or Descending order...\nEnter 'A' for Ascending or 'D' for Descending: ");
        // fgets(ascending, MAXSIZE, stdin);
        scanf("%d", &sortOrder);
        //infinite loop?
        if ( sortOrder == 'A' || sortOrder == 'a' ) {
            // strcpy(sortOrder, "A");
            sortOrder = 0;
        } else if (strcmp(ascending, "D") == 0 || strcmp(ascending,"d") == 0) {
            // strcpy(sortOrder, "D");
            sortOrder = 1;
        } else {
            i--;
            continue;
        }
    }

    printf("Made it here\n");
    //works!
    // Iterate through the strings 
    // Nested for loop that iterates through everything = o(n)^2 ... I know- inefficient! 
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (strcmp(str[i], str[j]) < 0 && sortOrder == 0) {
                char temp[MAXSIZE];
                strcpy(temp, str[i]);
                strcpy(str[i], str[j]);
                strcpy(str[j], temp);
            }

            if (strcmp(str[i], str[j]) > 0 && sortOrder == 1) {
                char temp[MAXSIZE];
                strcpy(temp, str[i]);
                strcpy(str[i], str[j]);
                strcpy(str[j], temp);
            }
        }
    }

    // printing the list
    for (int i = 0; i < 10; i++) {
        printf("%s", str[i]);
    }
    
}

void outputStringComp(char str[10][MAXSIZE]) { 

    //works!
    // Iterate through the strings 
    // Nested for loop that iterates through everything = o(n)^2 ... I know- inefficient! 
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (strcmp(str[i], str[j]) > 0) {
                char temp[MAXSIZE];
                strcpy(temp, str[i]);
                strcpy(str[i], str[j]);
                strcpy(str[j], temp);
            }
        }
    }

    // printing the list
    for (int i = 0; i < 10; i++) {
        printf("%s", str[i]);
    }

}

/*int calculateASCII(char str[10][MAXSIZE]) {

    // Create an array to store the ASCII values
    // int *ascii_values = malloc(sizeof(int) * strlen(char_array));
    int ascii_values_chars[10][MAXSIZE];
    int *ascii_values_total = malloc(sizeof(int) * strlen(str));

    // Iterate through the strings 
    // Nested for loop = o(n)^2 ... I know- inefficient! 
    for (int i = 0; i < 10; i++) {
        
        // Iterate through the character array and convert each character to its ASCII value
        for (int j = 0; j < strlen(str[i]); j++) {
            ascii_values_chars[i][j] = (int)str[i][j];
            printf("ASCII Value is of %c is %d\n", str[i][j], ascii_values_chars[i][j]);
            ascii_values_total[i] += ascii_values_chars[i][j];
        }
        printf("End of string\n");
        printf("Total ASCII Value of string %d is %d\n", i, ascii_values_total[i]);
    }

    return ascii_values_total;
}*/

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


/*


void inputStings() //Prompt the user for 10 character strings 2 points
void checkStringLen() //Ensure string length within [2..25] 1 point
int checkLegalCharacters() //Ensure no illegal characters: ’!’, ’@’, ’#’, ’$’, ‘%’, ‘^’, ’(’, or’)’. 2 point
void checkDuplicate() //Ensure no duplicate strings 1 point
void ascendingSort(char sortOrder) //Sort and display the output

*/
