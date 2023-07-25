/*
Kevin Leary 
G01357635
*/

/*
Running instructions: 
 1. Open terminal 
 2. `gcc -o HW3-Gnum HW3-Gnum.c`
 3. ./HW3-Gnum

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
    struct address_t *leftChild, *rightChild, *parent;
    int height, depth;
};
struct address_t *head = NULL;

void createListFromFile();
void displayList();
void addAddress();
struct address_t* lookUpAddress();
void updateAddress();
void deleteAddress();
void displayAliasforLocation();
void saveToFile();
void menu();
//Functions here
/*


Per the rurbric:
1) Add address - almost done
2) Look up address - almost done
3) Update address - almost done
4) Delete address - almost done
5) Display list - almost done 
6) Display aliases for location - almost done 
7) Save to file - almost done
8) Quit - starting

Also need a populate list function - done
*/

int main() {

    int exit, choice = 0;
    printf("\nWelcome to the IPv4 Program!\nWe will start by reading in the CS531_Inet.txt file!\n");
    //Start with file list...
    createListFromFile();

    //Then do the menu prompting...
    while (exit != 1) {
        printf("\n\nIPv4 Menu:\n1) Add address\n2) Look up address\n3) Update address\n4) Delete address\n5) Display list\n6) Display aliases for location\n7) Save to file\n8) Quit\n\n");
        printf("Please enter a choice from the above menu: ");
        scanf("%d", &choice);
        getchar(); // - used as buffer absorber for input first keyboard input not working

        switch(choice) {
            case 1 :
                addAddress();
                break;
            case 2 : 
                lookUpAddress();
                break;
            case 3 : 
                updateAddress();
                break;
            case 4 :
                deleteAddress();
                break;
            case 5 :
                displayList();
                break;
            case 6 : 
                displayAliasforLocation();
                break;
            case 7 : 
                saveToFile();
                break;
            case 8 :
                exit = 1;
                break;
            default : 
                printf("Error! Invalid Input- Please re-enter your choice!\n");
                break;
        }
    }

    return 0;
}

void menu() {

}

void saveToFile() {

    char filename[50];
    struct address_t *ptr = head;
    //Prompt for file name
    printf("Please enter a name for the file: ");
    fgets(filename, 50, stdin);
    filename[strcspn(filename, "\n")] = 0;
    strcat(filename, ".txt");
    //Open file
    FILE *address_file = fopen(filename, "w");

    //Put list into file
    while (ptr != NULL) {
        fprintf(address_file, "%d.%d.%d.%d %s\n", ptr->octet[0], ptr->octet[1], ptr->octet[2], ptr->octet[3], ptr->alias);
        ptr = ptr->next;
    }
    printf("File %s ready!\n", filename);
    fclose(address_file);
}

void displayAliasforLocation() {

    //This needs to be ordered pair - first two values for locality... 172.16...
    //List ALL alias that map to 172.16 ... 

    char locality[8];
    char list[100][11];
    struct address_t *ptr = head;
    struct address_t *tmp = (struct address_t*)malloc(sizeof(struct address_t));

    //Prompt for locality
    printf("Please enter a locality (XXX.XXX) to see if it exists in the list: ");
    fgets(locality, 8, stdin);  
    //TODO:REPROMPT IF ERROR
    locality[strcspn(locality, "\n")] = 0;
    sscanf(locality, "%d.%d\n", &tmp->octet[0], &tmp->octet[1]);
        
    printf("Locality is %d.%d\n", tmp->octet[0], tmp->octet[1]);

    //search for locality range - working
    int i = 0;
    while (ptr != NULL) {

        if (tmp->octet[0] == ptr->octet[0] && tmp->octet[1] == ptr->octet[1]) {
            strcpy(list[i], ptr->alias);
            i++;
            ptr = ptr->next;
        }
        else {
            ptr = ptr->next;
        }
    }
    //print list here... if there is a list
    if ( strlen(list[0]) == 1 ) {
        printf("Error: Locality %d.%d does not exist in the list!\n", tmp->octet[0], tmp->octet[1]);
    } else {
        printf("\nAliases with range %d.%d found are: \n", tmp->octet[0], tmp->octet[1]);
        for (int j = 0; j < strlen(list[j]); j++) {
            printf("%s\n", list[j]);
        }
    }

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
            displayList();
            
        } else {        // - This is for error input
            printf("\nError: %c is not 'Y' or 'N' - try again...\n", confirm);
            //Empty Character constant
            confirm = '\0';
            displayList();
        }

    }

}


void updateAddress() {

    //searching will be the same as the look-up it will just do something different when it finds it
    //I think that lookup should be reused here
    // char alias[] = lookUpAddress();
    int exit, dup = 0;
    char ip[17];
    struct address_t *found = lookUpAddress();
    struct address_t *ptr = head;
    struct address_t *update = (struct address_t*)malloc(sizeof(struct address_t));

    if (found != NULL) {

        while ( exit != 1 ) {
            printf("Enter the updated IPv4 address for %s: ", found->alias);
            fgets(ip, 17, stdin);  
            ip[strcspn(ip, "\n")] = 0;
            sscanf(ip, "%d.%d.%d.%d\n", &update->octet[0], &update->octet[1], &update->octet[2], &update->octet[3]);
            //check for octet out of range 0-255
            strcpy(update->alias, found->alias);
            for (int i = 0; i < 4; i++) {

                if ( update->octet[i] > 255 || update->octet[i] < 0 ) {
                    printf("Please re-enter IPv4! It is outside of the valid range 0-255\n");
                    break;
                } else if ( i == 3 && update->octet[i] < 256 && update->octet[i] > 0 ){
                    exit = 1;
                    break;
                } 

            }

            while ( ptr != NULL ) {
            // check all octets 

                if (update->octet[0] == ptr->octet[0] && update->octet[1] == ptr->octet[1] && update->octet[2] == ptr->octet[2] && update->octet[3] == ptr->octet[3]) {
                    printf("Address is a duplicate! Please re-enter a new adress for alias %s\n", found->alias);
                    dup = 1;
                    break;
                } else {
                    ptr = ptr->next;
                    exit = 1;
                }
            }
        }

        if ( dup != 1 ) {
            printf("Alias %s IPv4 address %d.%d.%d.%d is now %d.%d.%d.%d\n", found->alias, found->octet[0], found->octet[1], found->octet[2], found->octet[3], update->octet[0], update->octet[1], update->octet[2], update->octet[3]);
            //set new octet values
            for (int i = 0; i < 4; i++) {
                found->octet[i] = update->octet[i];
            }
        }

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
        if( strcmp(ptr->alias, alias) == 0 ) {
            printf("\nALIAS FOUND!\n");
            printf("The address for alias:%s is %d.%d.%d.%d\n", ptr->alias, ptr->octet[0], ptr->octet[1], ptr->octet[2], ptr->octet[3]);
            return ptr;
            break;
        }
        else {
            ptr = ptr->next;
        }
    }
    printf("\nError! Alias does not exist in list!\n");
    return NULL;
}

//When addAddress is first selection it makes the menu reprompt and auto populates a garbage address - mind boggling (maybe only on the mac?)
void addAddress() {
        
    char ip[17];
    char alias[50];
    char ipAlias[50];
    int exit, reprompt, iter = 0;
    struct address_t *test= (struct address_t*)malloc(sizeof(struct address_t));
    struct address_t *ptr = head;
    
    //working...
    while (exit != 1) {
        //Get IP and alias
        printf("Enter IPv4 Address followed by a 10 character Alias: ");
        fgets(ipAlias, 50, stdin);  
        // ipAlias[strcspn(ipAlias, "\n")] = 0;
        sscanf(ipAlias, "%d.%d.%d.%d %s", &test->octet[0], &test->octet[1], &test->octet[2], &test->octet[3], test->alias);
        //check for octet out of range 0-255
        for (int i = 0; i < 4; i++) {
            if ( test->octet[i] > 255 || test->octet[i] < 0 ) {
                printf("Please re-enter IPv4! It is outside of the valid range 0-255\n");
                break;
            } else if ( i == 3 && test->octet[i] < 256 && test->octet[i] > 0 ) {
                
                if ( strlen(test->alias) > 10 ) {
                    printf("Please re-enter the alias! It's more than 10 digits!\n");
                    break;
                } else {
                    exit = 1;
                }
                break;
            } 
        }

    }

    //Search for duplicates
    while (ptr != NULL) {
        //check octets
        int count = 0;
        for (int i = 0; i < 4; i++) {
            if (ptr->octet[i] == test->octet[i]) {
                count++;
            }
        }
        if (count == 4) {
            printf("\nError: IPv4 already exists in list!\n");
            return;
            break;
        }
        //now check for alias
        if ( strcmp(ptr->alias, test->alias) == 0) {
            printf("\nError: Alias already exists in list!\n");
            return;
            break;
        }

        ptr = ptr->next;

    }


    //Point to next memory location
    test->next = head;
    head = test;
        
}

void createListFromFile() {

    // Open the file
    FILE *address_file = fopen("CS531_Inet.txt", "r+");
    
    // Check if the file was opened successfully.
    if (address_file == NULL) {
        printf("\nError opening file.\n");
    }  
    
    // Read the contents of the file line by line.
    char line[100];

    while (fgets(line, sizeof(line), address_file)) {
        struct address_t *test= (struct address_t*)malloc(sizeof(struct address_t));

        sscanf(line, "%d.%d.%d.%d %s\n", &test->octet[0], &test->octet[1], &test->octet[2], &test->octet[3], test->alias);
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

}