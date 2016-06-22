#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "stack.h"
#include "parser.h"

void parser(Stack *stack)
{
	Node *node = (Node *) calloc(sizeof(Node), 1);
	char c = 0;
	int k = 0;
	char *string = NULL;
	do {
		c = getchar();
		if (c >= '0' || c <= '9') {
			string = realloc(string, sizeof(char) * ++k);
			string[k - 1] = c;
		}
		if (isalpha(c)) {
			node->tok.varname = c;
			stack_push(stack, node);
		}
		if (c == '+' || c == '-' || c == '^' || c == '*' || c == ':' || c == '(' || c == ')') {
			if (string != NULL) {
				node->tok.value = atoi(string);
				stack_push(stack, node);
				free(string);
				string = NULL;
				k = 0;
			}
			node->tok.op = c;
			stack_push(stack, node);
		}
	} while (c != '\n');
	free(string);
	free(node);
}




//ideal interface by Igor

// FILE *f = stdin;

// char c = fgetc(f);


// Stack *parse(FILE *in);
// Stack *toPostfix(Stack *in);
// Node *toTree(Stack *in);
// Node *transform(Node *);
// void toInfix(Node *n, FILE out);


// int main()
// {
// 	toInfix(transform(toTree(toPostfix(parse(stdin)))), stdout);
// 	return 0;
// }
