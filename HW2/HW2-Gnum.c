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
struct address_t* lookUpAddress();
void updateAddress();
void deleteAddress();
//Functions here
/*

For linked list need:
push()
pop()

Per the rurbric:
1) Add address - almost done
2) Look up address - almost done
3) Update address - needs some touch up
4) Delete address - almost done
5) Display list - almost done 
6) Display aliases for location
7) Save to file
8) Quit 

Also need a populate list function
*/

int main() {

    //Start with file list...
    createListFromFile();

    // addAddress();     - only need one right now because the other will be behind the menu as buffer
    addAddress();
    displayList();
    // lookUpAddress();
    updateAddress();
    // deleteAddress();
    displayList();

    return 0;
}


void deleteAddress() { 

    char confirm;
    struct address_t *del = lookUpAddress();
    struct address_t *prev = head;

    if (del != NULL) {
        printf("Please confirm that you want to delete alias %s with ip %d.%d.%d.%d...\nEnter 'Y' for Yes or 'N' for No: ", del->alias, del->octet[0], del->octet[1], del->octet[2], del->octet[3]);
        scanf("%c", &confirm);

        //Eliminate the upper or lower case issues
        if ( confirm == 'Y' || confirm == 'y' ) {
            //find the previous node real quick
            while (prev != NULL) {
                if (prev->next == del) { 
                    break;
                }
                prev = prev->next;
            }

            //If previous exists and del is any node besides the head node
            if (prev != NULL) {
                prev->next = del->next;
            }
            //If del is the head node
            else if (del == head) {
                head = del->next;
            }
            //Delete it!!
            free(del);
            del = NULL;

        } else if ( confirm == 'N' || confirm == 'n' ) {
            //TODO: Exit and reprompt?
            
        } else {        // - This is for error input
            printf("\nError: %c is not 'Y' or 'N' - try again...\n", confirm);
            //Empty Character constant
            confirm = '\0';
            // continue;

            //need to reprompt? 
        }

    }

}


void updateAddress() {

    //searching will be the same as the look-up it will just do something different when it finds it
    //I think that lookup should be reused here
    // char alias[] = lookUpAddress();
    char ip[17];
    struct address_t *found = lookUpAddress();
    struct address_t *ptr = head;
    struct address_t *update = (struct address_t*)malloc(sizeof(struct address_t));

    if (found != NULL) {
        // printf("%s\n", found->alias);  - working
        printf("Enter the updated IPv4 address for %s: ", found->alias);
        fgets(ip, 17, stdin);  
        ip[strcspn(ip, "\n")] = 0;
        sscanf(ip, "%d.%d.%d.%d\n", &update->octet[0], &update->octet[1], &update->octet[2], &update->octet[3]);
        //check for octet out of range 0-255
        strcpy(update->alias, found->alias);
        printf("\n%s:%d.%d.%d.%d\n", update->alias, update->octet[0], update->octet[1], update->octet[2], update->octet[3]);
        for (int i = 0; i < 4; i++) {

            if ( update->octet[i] > 255 || update->octet[i] < 0 ) {
                printf("Please re-enter IPv4! It is outside of the valid range 0-255\n");
                //TODO: REPROMPT
            }
            
        }

        //TODO: Check if address is a duplicate then REPROMPT
        while (ptr != NULL) {
            // check all octets 
                
            if (update->octet[0] == ptr->octet[0] && update->octet[1] == ptr->octet[1] && update->octet[2] == ptr->octet[2] && update->octet[3] == ptr->octet[3]) {
                printf("Address is a duplicate! Please re-enter a new adress for alias %s", found->alias);
                //TODO: REPROMPT 
                break;
            } else {

                ptr = ptr->next;

            }

        }

        // strcpy(update->alias, found->alias);
        printf("Alias %s IPv4 address %d.%d.%d.%d is now %d.%d.%d.%d\n", found->alias, found->octet[0], found->octet[1], found->octet[2], found->octet[3], update->octet[0], update->octet[1], update->octet[2], update->octet[3]);
        found->octet[3] = update->octet[3];
        //everything is working excepet - found = update; which is all I need I think
        // ptr = found;
    }

}

struct address_t* lookUpAddress() {

    //this might need to return an int for usage in update and delete address functions
    char alias[50];
    struct address_t *ptr = head;
    struct address_t *tmp = NULL;
    
    //Prompt for alias...
       
    //Get input - Alias
    printf("Enter a the alias to search for: ");
    fgets(alias, 50, stdin); 

    printf("%s\n", alias);
    //I believe that this adds a whitespace that we need so I am including it here too so strings stay consistent
    sscanf(alias, "%s\n", alias);
    //Iterate through all values to find searched value in ptr
    while(ptr != NULL) {
        // printf("%d", strcmp(ptr->alias, alias));
        if( strcmp(ptr->alias, alias) == 0 ) {
            printf("\nALIAS FOUND!\n");
            printf("The address for alias:%s is %d.%d.%d.%d\n", ptr->alias, ptr->octet[0], ptr->octet[1], ptr->octet[2], ptr->octet[3]);
            return ptr;
            break;
        }
        else {
            // tmp = ptr;
            // printf(".%s", ptr->alias);
            //TODO: REPROMPT, DISPLAY ERROR MESSAGE, REDISPLAY MENU
            ptr = ptr->next;
        }
    }

    return NULL;
}

void addAddress() {
        
    char ip[17];
    char alias[50];     // I could set fgets() character buffer to 11 but then it just cuts the input off which doesnt follow the rubric
    struct address_t *test= (struct address_t*)malloc(sizeof(struct address_t));
    
    //Get input - first IP address then alias
    printf("Enter IPv4 Address: ");
    fgets(ip, 17, stdin);  
    ip[strcspn(ip, "\n")] = 0;
    sscanf(ip, "%d.%d.%d.%d\n", &test->octet[0], &test->octet[1], &test->octet[2], &test->octet[3]);
    
    //check for octet out of range 0-255
    for (int i = 0; i < 4; i++) {

        if ( test->octet[i] > 255 || test->octet[i] < 0 ) {
            printf("Please re-enter IPv4! It is outside of the valid range 0-255\n");
            //TODO: REPROMPT
        }
    }

    //Get input - Alias
    printf("Enter a maximum 10 digit alias for IPv4 Address %s : ", ip);
    fgets(alias, 50, stdin);  
    sscanf(alias, "%s\n", test->alias);

    if ( strlen(alias) > 10) {
        printf("Please re-enter the alias! It's more than 10 digits!\n");
        //TODO: REPROMPT
    }
    
    //TODO: if either the address or alias already exists then display an error message and redisplay menu

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