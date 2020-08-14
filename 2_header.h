//Common headers
#include<stdio.h>
#include<stdlib.h>

//Constants
#define BASE 10000
#define STACK_TOP 20

//Basic structures
struct node{unsigned int value; struct node* next;};
struct stack {struct node* data[STACK_TOP]; int size[STACK_TOP]; int top;};
struct opstack {char data[STACK_TOP]; int top;};

/*Creates new node for linked list with value and next node updated*/
struct node* createNewNode(unsigned int value, struct node* next);
struct node* generateSampleList(struct node** header1, struct node** header2);

//Operations
void reversePrintList(struct node* node, struct node* header, int size);
void readnum(struct node** header);
void readandcompute();
