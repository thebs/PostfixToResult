#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct stack{
	char ch;
	float cal;
	struct stack *next;
}Stack;

Stack *top = NULL;
Stack *topForTime = NULL;
Stack *calTotal = NULL;
Stack *bVar;
Stack *eVar;
Stack *bCal = NULL;
Stack *eCal = NULL;
Stack *bString = NULL;
Stack *eString = NULL;

int cnt1 = 0, cnt2 = 0;
float total;

void push(char);
char pop();
void pushForTime(char);
char popForTime();
void pushTotal(float);
float popTotal();
char topStack();
int isEmty();
void foundObject();
void popThenAdd(char);
void check(char);
void input();
void output();
void calculator();
void append();
void appendString(char);
void destroy();
void addVar(char);

int main(int argc, const char* argv[]){
	char chk;
	printf("\t<<<<<<<<<< Welcome to Postfix to Result Program >>>>>>>>>>\n");
	do{
		printf("\n\tInfix\t: ");
		input();
		printf("\t----------------------------------------------------------");
		printf("\n\tResult\t: ");
		output();
		printf("\n\t----------------------------------------------------------\n\n");
		printf("\tPlease input value each variable\n");
		calculator();
		printf("\n\tTotal: %.2f", total);
		printf("\n\t----------------------------------------------------------");
		destroy();
		printf("\n\n");
		do{
			printf("\tDo you want to change Postfix to Result (y/n)? : ");
			fflush(stdin);
			scanf("%c", &chk);
		}while(!(tolower(chk) == 'y' || tolower(chk) == 'n'));
		
	}while(tolower(chk) != 'n');
	
	printf("\n\n\t<<<<<<<<<<<<<<<<<<<<<<<< Good Bye >>>>>>>>>>>>>>>>>>>>>>>>\n\n");
	return 0;
}

void input(){
	char ch;
	do{
		fflush(stdin);
		scanf("%c", &ch);
		if(ch == '\n')
			printf("\tInfix\t: ");
	}while(ch == '\n');
	
	while(ch != '\n'){
		check(ch);
		appendString(ch);
		scanf("%c", &ch);
	}
}

void output(){
	Stack *travel = top;
	while(travel != NULL){
		travel = travel->next;
		pushForTime(pop());
	}
	travel = topForTime;
	while(travel != NULL){
		char ch = travel->ch;
		travel = travel->next;
		printf("%c", ch);
	}
}

void destroy(){
	Stack *travel = bString;
	Stack *del;
	while(travel != NULL){
		del = travel;
		travel = travel->next;
		free(del);
	}
	bString = NULL;
	
	travel = bCal;
	while(travel != NULL){
		del = travel;
		travel = travel->next;
		free(del);
	}
	bCal = NULL;
	
	travel = bVar;
	while(travel != NULL){
		del = travel;
		travel = travel->next;
		free(del);
	}
	bVar = NULL;
	
	travel = top;
	while(travel != NULL){
		del = travel;
		travel = travel->next;
		free(del);
	}
	
	travel = topForTime;
	while(travel != NULL){
		del = travel;
		travel = travel->next;
		free(del);
	}
	topForTime = NULL;
	
	travel = calTotal;
	while(travel != NULL){
		del = travel;
		travel = travel->next;
		free(del);
	}
	calTotal = NULL;
}

void calculator(){
	Stack *travel = bCal;
	stack *tVar = bVar;
	while(travel != NULL){
		printf("\t%c = ", tVar->ch);
		scanf("%f", &travel->cal);
		travel = travel->next;
		tVar = tVar->next;
	}
	
	travel = bString;
	Stack *cal = bCal;
	float x, y;
	while(travel != NULL){
		char str = travel->ch;
		if(isalpha(str)){
			pushTotal(cal->cal);
			cal = cal->next;
		}else{
			if(str == '^'){
				x = popTotal();
				y = popTotal();
				float temp = 1.0;
				for(int i=0;i<x;i++){
					temp *= y;
				}
				total = temp;
				pushTotal(total);
			}else if(str == '*'){
				x = popTotal();
				y = popTotal();
				total = x * y;
				pushTotal(total);
			}else if(str == '/'){
				x = popTotal();
				y = popTotal();
				total = y / x;
				pushTotal(total);
			}else if(str == '+'){
				x = popTotal();
				y = popTotal();
				total = x + y;
				pushTotal(total);
			}else if(str == '-'){
				x = popTotal();
				y = popTotal();
				total = y - x;
				pushTotal(total);
			}
		}
		travel = travel->next;
	}
}

void addVar(char ch){
	Stack *n = (Stack *)malloc(sizeof(Stack));
	if(bVar == NULL)
		bVar = n;
	else
		eVar->next = n;
	eVar = n;
	n->ch = ch;
	n->next = NULL;
}

void append(){
	Stack *n = (Stack *)malloc(sizeof(Stack));
	if(bCal == NULL)
		bCal = n;
	else
		eCal->next = n;
	eCal = n;
	n->next = NULL;
}

void appendString(char ch){
	Stack *n = (Stack *)malloc(sizeof(Stack));
	if(bString == NULL)
		bString = n;
	else
		eString->next = n;
	eString = n;
	n->ch = ch;
	n->next = NULL;
}

void push(char ch){
	Stack *n = (Stack *)malloc(sizeof(Stack));
	n->next = top;
	top = n;
	n->ch = ch;
}

char pop(){
	Stack *backup = top;
	char ch = top->ch;
	top = top->next;
	free(backup);
	return ch;
}

void pushForTime(char ch){
	Stack *n = (Stack *)malloc(sizeof(Stack));
	n->next = topForTime;
	topForTime = n;
	n->ch = ch;
}

char popForTime(){
	Stack *backup = topForTime;
	char ch = topForTime->ch;
	topForTime = topForTime->next;
	free(backup);
	return ch;
}

void pushTotal(float cal){
	Stack *n = (Stack *)malloc(sizeof(Stack));
	n->next = calTotal;
	calTotal = n;
	n->cal = cal;
}

float popTotal(){
	Stack *backup = calTotal;
	float cal = calTotal->cal;
	calTotal = calTotal->next;
	free(backup);
	return cal;
}

char topStack(){
	return (isEmty())? NULL : top->ch;
}

int isEmty(){
	return (top == NULL);
}

void foundObject(){
	while(top != NULL){
		char popStack = pop();
		if(popStack == ')'){
			cnt1++;
			pushForTime(popStack);
		}
		else if(popStack == '('){
			cnt2++;
			if(cnt1 == cnt2){
				cnt1 = cnt2 = 0;
				push('(');
				push('(');
				while(topForTime != NULL){
					push(popForTime());
				}
				break;
			}else{
				pushForTime(popStack);
			}
		}else{
			pushForTime(popStack);
		}
	}
}

void popThenAdd(char ch){
	char stackTop = topStack();
	if(isalpha(stackTop) || isdigit(stackTop)){
		pushForTime(')');
		pushForTime(pop());
		pushForTime(ch);
		char stackTop_2 = topStack();
		if(isalpha(stackTop_2) || isdigit(stackTop_2)){
			pushForTime(pop());
			push('(');
			while(topForTime != NULL){
				push(popForTime());
			}
		}else{
			foundObject();
		}
	}else{
		pushForTime(')');
		while(top != NULL){
			char popStack = pop();
			if(popStack == ')'){
				cnt1++;
				pushForTime(popStack);
			}
			else if(popStack == '('){
				cnt2++;
				if(cnt1 == cnt2){
					cnt1 = cnt2 = 0;
					pushForTime(popStack);
					pushForTime(ch);
					char popStack_2 = topStack();
					if(isalpha(popStack_2) || isdigit(popStack_2)){
						pushForTime(pop());
						push('(');
						while(topForTime != NULL){
							push(popForTime());
						}
						break;
					}else{
						foundObject();
						break;
					}
				}else{
					pushForTime(popStack);
				}
			}else{
				pushForTime(popStack);
			}
		}
	}
}

void check(char ch){
	if(isalpha(ch) || isdigit(ch)){
		push(ch);
		append();
		addVar(ch);
	}else{
		popThenAdd(ch);
	}
}
