#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#define PI 3.14
// char *reverse(char *input);

struct node {
  int data;
  struct node *next;
};

struct node *head = NULL;

int x = 10;

printf("%s\n", x > 10 ? "Hello" : "Goodbye");

void delete_node(struct node *head, int n) {
  if (head == NULL) {
    return;
  }

  struct node *current = head;
  int count = 1;
  while (current != NULL && count < n) {
    current = current->next;
    count++;
  }

  if (current == NULL) {
    return;
  }

  struct node *temp = current->next;
  free(current);
  current = temp;
}

void init_list() {
  //initialize list with one node
  struct node *new_node = malloc(sizeof(struct node));
  new_node->data = 1;
  new_node->next = head;
  head = new_node;
}

void add_node(int data) {
  struct node *new_node = malloc(sizeof(struct node));
  new_node->data = data;
  new_node->next = head;
  head = new_node;
}

void print_list() {
  struct node *current = head;
  while (current != NULL) {
    printf("%d\n", current->data);
    current = current->next;
  }
}

// char *reverse(char *input) {
//      	       int len = strlen(input);
//      	       char output[len] ;
//                 char *s = malloc(len);	
// 	       for (int i = 0; i < len; i++) {
//          		output[len - i - 1] = input[i];
//       	      }
//                 s = output;
//       	      return s;
//     	}
