/*
Kevin Leary 
G01357635
*/

/*
Running instructions: 
 1. Open terminal 
 2. `gcc -o HW2-Gnum HW2-Gnum.c`
 3. ./HW2-Gnum

 OR 

 1. use the runner.sh
*/

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

struct address_t
{
    int octet[4];
    char alias[11];
    struct address_t *next;
};
struct address_t *head = NULL;

void createListFromFile();
void displayList();
void addAddress();
//Functions here
/*

For linked list need:
push()
pop()

Per the rurbric:
1) Add address - halfway done
2) Look up address
3) Update address
4) Delete address
5) Display list - almost done 
6) Display aliases for location
7) Save to file
8) Quit 

Also need a populate list function
*/

int main() {

    //Start with file list...
    createListFromFile();

    // addAddress();
    addAddress();
    displayList();

    return 0;
}

void addAddress() {
        
    // Read the contents of the file line by line.
    // char line[100];
    char ip[16];
    char alias[10];
    // while (fgets(line, sizeof(line), address_file)) {
    struct address_t *test= (struct address_t*)malloc(sizeof(struct address_t));
    
    //Get input - first IP address then alias
    printf("Enter IPv4 Address: ");
    fgets(ip, 17, stdin);  
    // ip[strlen(ip) - 1] = 0; //this removes the newline from the end of the string - THIS FUCKS UP THE STRING

    printf("Enter a maximum 10 digit alias for IPv4 Address %s : ", ip[strlen(ip) - 1]);
    fgets(alias, 12, stdin);  
    alias[strlen(alias) - 1] = 0;

    //parse input
    sscanf(ip, "%3d.%3d.%3d.%3d\n", &test->octet[0], &test->octet[1], &test->octet[2], &test->octet[3]);
    sscanf(alias, "%s\n", test->alias);
    //Point to next memory location
    test->next = head;
    head = test;
        
}

void createListFromFile() {

    // Open the file
    FILE *address_file = fopen("CS531_Inet.txt", "r+");
    
    // Check if the file was opened successfully.
    if (address_file == NULL) {
        printf("Error opening file.\n");
        // return 1;
    }  
    
    // Read the contents of the file line by line.
    char line[100];

    while (fgets(line, sizeof(line), address_file)) {
        struct address_t *test= (struct address_t*)malloc(sizeof(struct address_t));

        sscanf(line, "%d.%d.%d.%d %s\n", &test->octet[0], &test->octet[1], &test->octet[2], &test->octet[3], test->alias);
        // printf("%d.%d.%d.%d %s\n", test->octet[0], test->octet[1], test->octet[2], test->octet[3], test->alias);
        test->next = head;
        head = test;
    }

}

void displayList() {
    struct address_t *ptr = head;

    while (ptr != NULL) {
        printf("%d.%d.%d.%d %s\n", ptr->octet[0], ptr->octet[1], ptr->octet[2], ptr->octet[3], ptr->alias);
        ptr = ptr->next;
    }

    if (head == NULL) {
        printf("Address list is NULL!\n");
    }
    //TODO - Reprint menu option
}