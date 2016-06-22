#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "stack.h"
#include "tree.h"
#include "parser.h"



int main(void)
{
	Stack *stack = stack_create();
	Tree *tree;
	tree_init(&tree);
	printf("\n\n=========================\n\n default - insert\n\n t - print tree\n\n e - print expression in polis\n\n r - result of the expression\n\n q - quit\n\n =========================\n\n");
	while (true) {
		char cmd = 0;
		scanf("%c", &cmd);
		switch (cmd){
			default:
				if (!stack_is_empty(stack)) {
					stack_destroy(stack);
					stack = stack_create();
				}
				parser(stack);
				polish(stack);
				break;
			case 't':
				build_tree(&tree, stack);
				break;
			case 'e':
				RLR_tree(&tree);
				break;
			case 'r':
				printf("%d\n", RLR_sum_tree(&tree));
				break;
			case 'q':
				if (tree->root != NULL) {
					tree_destroy(&tree);
				}
				stack_destroy(stack);
				printf("Good Bye!");
				return 0;
		}
	}
} 