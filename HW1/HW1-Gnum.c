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

#define MAXSIZE 26

void inputStrings(char str[10][MAXSIZE]);
int checkDuplicate(char s1[], char s2[]);
int checkStringLen(char s[]);
int checkLegalCharacters(char s[][]);

int main() {

    char str[10][MAXSIZE];

    inputStrings(str);
    /*
    printf("Enter a String: ");
    scanf("%[^\n]s", str);    // %[^\n]s - allows for spaces in input   
    if( strlen(str) < 2) {
        printf("Error: string too few characters - please re-enter\n");
        // reprompt
    } else if ( strlen(str) > 25)
    {
        printf("Error: string too many characters - please re-enter\n");
        //reprompt
    }
    
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '!' || str[i] == '@' || str[i] == '#' || str[i] == '$' || str[i] == '%' || str[i] == '^' || str[i] == '(' || str[i] == ')') {
          printf("Error: %c is an illegal character - please re-enter\n", str[i]);
          //reprompt
          break;
        }
    }

    printf("string is: %s\n", str);
    printf("String length is: %zu\n", strlen(str));
    printf("\n");*/

    return 0;
}

//not working... need to send iver the array and the associated characters
int checkLegalCharacters(char s[][]){
    int i = 0;
    for (i = 0; i < strlen(s); i++) {
        if (s[i] == '!' || s[i] == '@' || s[i] == '#' || s[i] == '$' || s[i] == '%' || s[i] == '^' || s[i] == '(' || s[i] == ')') {
            printf("Error: %c is an illegal character - please re-enter\n", s[i]);
            return 1; 
        } else {
            return 0;
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
        // Check if the string is duplicate
        // for (j = 0; j < i; j++) {
        //     if (strcmp(str[i], str[j]) == 0) {
        //         printf("Error: duplicate string - please re-enter\n");
        //         dup = 1;
        //         break;
        //     }
        // } 
        // // If the string is duplicate, re-prompt the user
        // if (dup) {
        //     i--;
        //     continue;
        // } 
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
        if (checkLegalCharacters(str[i][j]) == 1){
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
