#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int fullCounter = 0;

struct Stack {
	int items[MAX];
	int top;
};

struct Stack newEmptyStack() {
	struct Stack st;
	st.top = -1;
	return st;
}

int pop(struct Stack *st) {
	if (st->top == -1) {
		printf("Stack is empty. Cannot pop.\n");
		exit(1);
	}
	int poppedItem = st->items[st->top];
	st->top--;
	return poppedItem;
}

void push(struct Stack *st, int data) {
	if (st->top == MAX - 1) {
		printf("Stack is full. Cannot push %d.\n", data);
		exit(1);
	} else {
		st->top++;
		st->items[st->top] = data;
	}
}

void printStack(struct Stack *st) {
	for (int i = 0; i <= st->top; i++) { 
		printf("%d ", st->items[i]);
	}
	printf("\n");
}

int main() {
	struct Stack stack = newEmptyStack();

	push(&stack, 10);
	push(&stack, 20);
	push(&stack, 30);
	push(&stack, 40);

	printf("Stack after pushes: ");
	printStack(&stack);

	int poppedValue = pop(&stack);
	printf("Popped value: %d\n", poppedValue);

	printf("Stack after pop: ");
	printStack(&stack);

	push(&stack, 50);
	push(&stack, 60);

	printf("Stack after more pushes: ");
	printStack(&stack);

	while (stack.top != -1) {
		printf("Popped value: %d\n", pop(&stack));
	}

	printf("Attempting to pop from empty stack...\n");
	pop(&stack); 

	return 0;
}

