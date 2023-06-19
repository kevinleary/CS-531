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

//Functions here
/*

For linked list need:
push()
pop()

Per the rurbric:
1) Add address
2) Look up address
3) Update address
4) Delete address
5) Display list
6) Display aliases for location
7) Save to file
8) Quit 

Also need a populate list function
*/

int main() {

    // Open the file
    FILE *address_file = fopen("CS531_Inet.txt", "r+");
    
    // Check if the file was opened successfully.
    if (address_file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }  
    
     
    //need starter
    // struct address_t *ptr = head;

    // Read the contents of the file line by line.
    char line[100];

    while (fgets(line, sizeof(line), address_file)) {
        struct address_t *test= (struct address_t*)malloc(sizeof(struct address_t));

        sscanf(line, "%d.%d.%d.%d %s\n", &test->octet[0], &test->octet[1], &test->octet[2], &test->octet[3], test->alias);
        // printf("%d.%d.%d.%d %s\n", test->octet[0], test->octet[1], test->octet[2], test->octet[3], test->alias);
        test->next = head;
        head = test;
    }

    struct address_t *ptr = head;
    
    while (ptr != NULL) {
        printf("%d.%d.%d.%d %s\n", ptr->octet[0], ptr->octet[1], ptr->octet[2], ptr->octet[3], ptr->alias);
        ptr = ptr->next;
    }

    // while (fgets(address_file, "%d.%d.%d.%d %s", &test->octet[0], &test->octet[1], &test->octet[2], &test->octet[3], &test->alias)) {
    // fscanf(address_file, "%d.%d.%d.%d %s\n", &test->octet[0], &test->octet[1], &test->octet[2], &test->octet[3], test->alias);
    // printf("%d.%d.%d.%d %s\n", test->octet[0], test->octet[1], test->octet[2], test->octet[3], test->alias);
    // test->next = head;
    // head = test;
    //create new? 



    // struct test_struct *create_list(intval) { 
    //     printf("\ncreatinglistwithheadnodeas[%d]\n",val); 
    //     struct test_struct *ptr = (struct test_struct*)m alloc(sizeof(struct test_struct));
    //      if(NULL==ptr) { 
    //          printf("\nNodecreationfailed\n"); 
    //          returnNULL; 
    //     } 
    //     ptr->val=val; 
    //     ptr->next=NULL; 
    //     head=curr=ptr; 
    //     return ptr; 
    // }
    
    // printf("%s\n", line);
    //   i=0;
        // i++;
    // }   

    // Close the file.
    // fclose(address_file);

    return 0;
}
