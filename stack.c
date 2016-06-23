#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include "stack.h"

#define STACK_INITIAL_SIZE 32

typedef struct stack_{
	Node **data;
	size_t size;
	size_t occup;
	ptrdiff_t top;
};

Stack *stack_create()
{
	Stack *stack = (Stack *) malloc(sizeof(Stack));
	if (stack == NULL) {
		return NULL;
	}
	stack->size = STACK_INITIAL_SIZE;
	stack->data = (Node *) malloc(sizeof(Node) * stack->size + 1);
	if (stack->data == NULL) {
		return NULL;
	}
	stack->occup = 0;
	stack->top = -1;
	return stack;
}

void stack_destroy(Stack *stack)
{
	free(stack->data);
	free(stack);
}

void stack_push(Stack *stack, Node *node)
{
	if (stack->size == stack->occup) {
		stack->size *= 2;
		stack->data = (Node *) realloc(stack->data, sizeof(Node) * stack->size);
	}
	stack->data[++stack->top] = node;
}

bool stack_is_empty(Stack *stack)
{
	return stack->top == -1;
}

Node *stack_pop(Stack *stack)
{
	if (stack_is_empty(stack)) {
		perror("STACK_IS_EMPTY");
		return NULL;
	}
	return stack->data[stack->top--];
}

Node *stack_top(Stack *stack)
{
	return stack->data[stack->top];
}