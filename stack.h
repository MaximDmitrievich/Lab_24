#ifndef STACK_H
#define STACK_H
#include <stddef.h>

typedef char Operator;
typedef struct token_{
	int value;
	char varname;
	Operator op;
} Token;
typedef struct node_{
	Token tok;
	struct node_ *left;
	struct node_ *right;
} Node;
typedef struct stack_ Stack;

Stack *stack_create();
void stack_destroy(Stack *stack);
void stack_push(Stack *stack, Node *node);
bool stack_is_empty(Stack *stack);
Node *stack_pop(Stack *stack);
Node *stack_top(Stack *stack);
#endif