#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct stack{
	char ch;
	struct stack *next;
}Stack;

Stack *top = NULL;
Stack *topForTime = NULL;
int cnt1 = 0, cnt2 = 0;

void push(char);
char pop();
void pushForTime(char);
char popForTime();
char topStack();
int isEmty();
void foundObject();
void popThenAdd(char);
void check(char);
void input();
void output();

int main(int argc, const char* argv[]){
	input();
	output();
	return 0;
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
	if(isalpha(stackTop)){
		pushForTime(')');
		pushForTime(pop());
		pushForTime(ch);
		char stackTop_2 = topStack();
		if(isalpha(stackTop_2)){
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
					if(isalpha(popStack_2)){
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
	if(isalpha(ch)){
		push(ch);
	}else{
		popThenAdd(ch);
	}
}

void input(){
	char ch;
	scanf("%c", &ch);
	while(ch != '\n'){
		check(ch);
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
		travel = travel->next;
		printf("%c", popForTime());
	}
}
