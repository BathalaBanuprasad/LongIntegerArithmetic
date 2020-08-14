#include"2_header.h"


//Value Stack Operation
void MAKENULL(struct stack *s) {s->top = STACK_TOP;}
int ISEMPTY(struct stack *s) {if (s->top == STACK_TOP) return 1; return 0;}
int ISFULL(struct stack *s) {return s->top == 0;}
void PUSH(struct stack *s, struct node* node, int size) {if(!ISFULL(s)) {s->top = s->top-1; s->data[s->top] = node; s->size[s->top] = size; } else printf("Stack is full\n");}
struct node* POP(struct stack *s, int *size) {if(!ISEMPTY(s)) {*size = s->size[s->top]; return s->data[s->top++];} printf("Empty vs stack\n"); exit(0); return NULL;}
struct node* TOP(struct stack *s, int *size) {if(!ISEMPTY(s)) {*size = s->size[s->top]; return s->data[s->top];} return NULL;}

//Operator stack operations
void opMAKENULL(struct opstack *s) {s->top = STACK_TOP;}
int opISEMPTY(struct opstack *s) {if (s->top == STACK_TOP) return 1; return 0;}
int opISFULL(struct opstack *s) {return s->top == 0;}
void opPUSH(struct opstack *s, char data) {if(!opISFULL(s)) s->data[--s->top] = data; else printf("Stack is full\n");}
char opPOP(struct opstack *s) {if(!opISEMPTY(s)) return s->data[s->top++]; printf("Empty op stack\n"); exit(0); return 255;}
char opTOS(struct opstack *s) {if(!opISEMPTY(s)) return s->data[s->top]; printf("Empty op stack\n"); exit(0); return 255;}


/*Creates new node for linked list with next pointer*/
struct node* createNewNode(unsigned int value, struct node* next) {
		struct node* new = (struct node*)malloc(sizeof(struct node));
		if(new==NULL) {printf("\nUnable to create new node\n"); exit(0);} else {new->value = 	value;	new->next = next;	return new;}
	return NULL;
		}

void intToString(unsigned value, char result[]) {
	int i=0;
	unsigned int n=value;
	while(n>0){ unsigned int ch=n%10; n=n/10; result[3-i]=ch+'0'; i++;}//3 is length of string and '0': to convert int to corresponding ASCII
}

// To Print Final Result
void reversePrintList(struct node* node, struct node* header, int size) {
	if(size>0&&node!=NULL) {
		reversePrintList(node->next, header, size-1);
		char result[4] = "0000";
		intToString(node->value, result);
		printf("%s", result);
		if(node!=header) printf(",");
	}
}

// Used while multiplication operation
void copyandreverse(struct node* header, struct node** result, int size) {
	if(size==0) *result = NULL;
	else if (size==1) *result = header;
	else {
		int s=size;
		struct node* cin = header;
		while(s>0){
			struct node* newNode = createNewNode(cin->value, *result); //Insert at head
			*result=newNode;
			if(cin==header) {newNode->next=NULL;}
			cin=cin->next; s--;}}
}

//Operations

void add(struct node* op1, struct node *op2, int size1, int size2, struct node** result, int *size){
    struct node* cop1 = op1; //OPERAND 1
    struct node* cop2 = op2; //OPERAND 2   
    struct node* cresult = NULL;
	struct node* tail = NULL;
	int s1=size1;
	int s2=size2;
	int s=0;
    unsigned int c = 0;
	if(size2==0) {*size = size1; *result=op1; return;} 
	else if(size1==0) {*size = size2; *result=op2; return;}

	//Add elements until both the operands have elements
    while(s1>0&&s2>0) {
			unsigned int valueSum = (cop1->value + cop2->value + c); 
			c=valueSum/BASE;
            struct node* newNode = createNewNode(valueSum%BASE, NULL);
			s++; //Increment size of final result
			s1--; s2--; //Decrement size of next result
			if(cresult==NULL){
				cresult = newNode; 
				tail=newNode;
			} else {
				tail->next = newNode; 
				tail=newNode;
			}
        	cop1=cop1->next; cop2=cop2->next;
	}
	
	//Handling remaining operand's values
    if(cop2!=NULL) {
    	// Copy remaining digits to operand 1
		cop1=cop2; s1=s2;
	}

	// Copy remaining values in final result
    while(s1>0) {
		unsigned int valueSum = (cop1->value + c); c=valueSum/BASE;
        struct node* newNode = createNewNode(valueSum%BASE, NULL);
		s++;
		s1--;
		if(cresult==NULL){
			cresult = newNode; 
			tail=newNode;
		} 
		else {
			tail->next = newNode; 
			tail=newNode;
		} 
		cop1=cop1->next;
	}

	// If there is some carry, add it to the result
	if(c>0) {
		struct node* newNode = createNewNode(c, NULL); s++;
		if(cresult==NULL){
			cresult = newNode; 
			tail=newNode;
		} else {
			tail->next = newNode; 
			tail=newNode;
		}
	}

	if(tail!=NULL) tail->next = *result;
	*result=cresult;
	*size=s;
}

void mul(struct node* op1, struct node *op2, int n1, int n2, struct node** result, int *size) {	
	struct node* cresult;
	struct node* oper2;
	struct node* tail;
	copyandreverse(op2, &oper2, n2);
	int s1=n1;
	int carry=0;
	int s=0;
	int i,j;
	for(i=0;i<(n1+n2-1);i++){
		int m=n2-1;
		struct node* cop1 = op1; s1=n1;
		struct node* cop2 = oper2;
		// Shift elements untile we get desired shifts
		while(m>i && cop2!=NULL && cop2->next!=NULL) {cop2=cop2->next; m--;}
		unsigned int product = 0;
		for(j=0;j<=i;j++) {
			if(i-j==m && j<=(n1-1) && cop1!=NULL && cop2!=NULL) {
				product+=(cop1->value)*(cop2->value);
				cop1=cop1->next; cop2=cop2->next; m--;
			} else if(cop1!=NULL) cop1=cop1->next; s1--;
		}
		product=product+carry;
		if(i==0) {cresult = createNewNode(product%BASE, NULL); tail=cresult; s++;} 
		else {tail->next = createNewNode(product%BASE, NULL); tail=tail->next; s++;}
		carry = product/BASE;
	}
	
	// Store the carry
	if(carry>0) {tail->next=createNewNode(carry, NULL); tail=tail->next; s++;}

	tail->next = *result;
	*result=cresult;
	*size=s;
}

// Intermediate computation
void compute(struct stack *vs,struct opstack *os, struct node** header, char currentOp) {
	int flag = 0;
	if(opISEMPTY(os)) return;
	flag = (opTOS(os)=='*'&&currentOp=='+') ? 1: 0;
	while(!ISEMPTY(vs) && !(opISEMPTY(os)) && flag) {
		//Evaluate expression, when Top of Stack is * and current operation is +
		int sizeop1=0;
		int sizeop2=0;
		char opr=opPOP(os);
		struct node* op1=POP(vs, &sizeop1);
		struct node* op2;
		if(!ISEMPTY(vs))
			op2=POP(vs, &sizeop2); 
		else {
			printf("Invalid expression\n"); exit(0);
		}
		if(op1!=NULL&&op2!=NULL) {
			int size_r=0;
			if(opr=='+') {
				add(op1,op2,sizeop1, sizeop2,header,&size_r); 
				PUSH(vs, *header, size_r);
			}
			else if(opr=='*') {
				mul(op1, op2, sizeop1, sizeop2,header,&size_r); 
				PUSH(vs, *header, size_r);
			}
		}

		if(opISEMPTY(os)) return;
		flag = (opTOS(os)=='+'&&currentOp=='*') ? 1: 0;
	}
}

void readandcompute() {
	struct stack *vs = (struct stack*)malloc(sizeof(struct stack));
	MAKENULL(vs);
	struct opstack *os = (struct opstack*)malloc(sizeof(struct opstack));
	opMAKENULL(os);

	printf("\nStart entering expression: \n");
	//Read Input
	struct node* header=NULL;
	struct node* curr=header;
	char ch;
	int i=0;
	int val=0;
	int size=0;
	while(1){
		ch=getchar();
		if(ch<='9'&&ch>='0'){
			// Read digits
			if(i<=3) {
				val=val*10+(ch-'0');
				i++;
			}
		} else if(ch==',') {
			// Separator for 4 digits
			if(i==4){
				struct node* newNode=createNewNode(val, header); //Create new node
				size++;
				header=newNode; // Storing the long number reversed
				val=0; i=0; //Reset temporary variables
				continue;
			} else {printf("Invalid!\n\n"); exit(0);}}
		else if(ch=='$'){ 
			// Terminator for a long number
			struct node* newNode=createNewNode(val, header);
			size++; 
			header=newNode;//Inserting at head
			val=0; i=0;
			PUSH(vs, header, size); //Push value onto a stack
			header=NULL; } //Number terminator
		else if(ch=='+'||ch=='*'){
			// Operand detection
			size=0;
			compute(vs, os, &header, ch);
			opPUSH(os, ch);
			}
		else if(ch=='=') {
			// End of expression
			break;
		}
		else {
			// Invalid Data Entered
			printf("\tERROR!\n");
			printf("\n\nInvalid data\n\n");
			exit(0);
			}
	}

//Evaluate the remaining expression
	struct node* result;
	if(ch=='=') {
		while(!ISEMPTY(vs) && !(opISEMPTY(os))) {
			//Evaluate expression
			int sizeop1=0;
			int sizeop2=0;
			char opr=opPOP(os);
			struct node* op1=POP(vs, &sizeop1);
			struct node* op2;
			if(!ISEMPTY(vs))
				op2=POP(vs, &sizeop2); 
			else {
				printf("Invalid expression\n"); 
				exit(0);
			}
			if(op1!=NULL&&op2!=NULL) {
				int size_r=0;
				if(opr=='+') {
					// Addition
					add(op1,op2,sizeop1, sizeop2,&header,&size_r);
					PUSH(vs, header, size_r);
				}
				else if(opr=='*') {
					// Multiplication
					mul(op1, op2, sizeop1, sizeop2,&header,&size_r);
					PUSH(vs, header, size_r);
				}
			}
		}
	}

//After infix evaluation, the only value present in Value stack must be final result
	if(!ISEMPTY(vs)) {
		header = POP(vs, &size);
		if(ISEMPTY(vs)) {
			printf("\nResult: "); 
			reversePrintList(header, header, size);
		} 
		else {
			printf("\n\nInvalid expression 1\n");
		}
	}
	else {
		printf("\n\nInvalid expression 2\n");
	}
	printf("\n");
}
