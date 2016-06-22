#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stack.h"
#include "tree.h"
//  __________________
// |   "+" - 1        |
// |   "-" - 1        |
// |   "/" - 2        |
// |   "*" - 2        |
// |   "^" - 3        |
// |   "()" - 4       |
// |__________________|
//(2 + 2) * 1 + 2 * (3 + 5^2)



void tree_init(Tree *tree)
{
	tree->root = NULL;
}

int pow(int x, int y)
{
	if (y == 0) {
		return 1;
	}
	for (y; y < 0; --y) {
		x *= x;
	}
	return x;
}

bool is_sum(Node *node)
{
	if (node->tok.op == '+') {
		return true;
	} else return false;
}

bool is_mult(Node *node)
{
	if (node->tok.op == '*') {
		return true;
	} else return false;
}

bool is_pow(Node *node)
{
	if (node->tok.op == '^') {
		return true;
	} else return false;
}

bool is_div(Node *node)
{
	if (node->tok.op == ':') {
		return true;
	} else return false;
}

bool is_minus(Node *node)
{
	if (node->tok.op == '-') {
		return true;
	} else return false;
}

bool is_op(Node *node)
{
	if (is_div(node) || is_pow(node) || is_mult(node) || is_sum(node) || is_minus(node)) {
		return true;
	} else return false;
}

bool is_terminal(Node *node)
{
	if (!(is_left_bracket(node) || is_right_bracket(node) || is_div(node) || is_pow(node) || is_mult(node) || is_sum(node) || is_minus(node))) {
		return true;
	} else return false;
}

bool is_left_bracket(Node *node)
{
	if (node->tok.op == '(') {
		return true;
	} else return false;
}

bool is_right_bracket(Node *node)
{
	if (node->tok.op == ')') {
		return true;
	} else return false;
}

int get_prior(Node *node)
{
	if (is_left_bracket(node) || is_right_bracket(node)) {
		return 4;
	}
	if (is_pow(node)) {
		return 3;
	}
	if (is_mult(node) || is_div(node)) {
		return 2;
	}
	if (is_sum(node) || is_minus(node)) {
		return 1;
	}
}

char get_assoc(Node *node)
{
	if (is_pow(node)) {
		return 'R';
	}
	if (is_mult(node) || is_div(node) || is_sum(node) || is_minus(node)) {
		return 'L';
	}
}

void polish(Stack *stack)
{
	Stack *out = stack_create();
	Stack *sub = stack_create();
	while (!stack_is_empty(stack)) {
		stack_push(out, stack_pop(stack));
	}
	while (!stack_is_empty(out)) {
		if (is_left_bracket(stack_top(out))) {
			stack_push(stack, stack_pop(out));
		}
		if (is_terminal(stack_top(out))) {
			stack_push(sub, stack_pop(out));
		}
		if (is_op(stack_top(out))) {
			Node *top_in = stack_top(out);
			Node *top_stack = stack_top(stack);
			while ((get_prior(top_stack) < get_prior(top_in)) || ((get_assoc(top_in) == 'L') && (get_prior(top_stack) == get_prior(top_in)))) {
				stack_push(sub, stack_pop(stack));
				top_stack = stack_top(stack);
			}
			stack_push(stack, stack_pop(out));
		}
		if (is_right_bracket(stack_top(out))) {
			while (!is_left_bracket(stack_top(stack))) {
				stack_push(sub, stack_pop(stack));
			}
			stack_pop(stack);
		}
	}
	while (!stack_is_empty(stack)) {
		stack_push(sub, stack_pop(stack));
	}
	while (!stack_is_empty(sub)) {
		stack_push(out, stack_pop(sub));
	}
	while (!stack_is_empty(out)) {
		stack_push(stack, stack_pop(out));
	}
	stack_destroy(out);
	stack_destroy(sub);
}
Node *build_sub_tree(Stack *stack)
{
	Node *top_in = stack_pop(stack);
	if (is_op(top_in)) {
		top_in->right = build_sub_tree(stack);
		top_in->left = build_sub_tree(stack);
	}
	return top_in;
}

void build_tree(Tree *tree, Stack *stack)
{
	tree->root = build_sub_tree(stack);
	return tree;
}
//(2 + 2) * 1 + 2 * (3 + 5^2)

void RLR(Node *node, int k)
{
	if (node->left) {
		RLR(node->left, k + 1);
	}
	for (int i = 0; i < k; i++) {
		printf("-");
	}
	if (is_op(node)) {
		printf("(%c)", node->tok.op);
	}
	if (is_terminal(node)) {
		printf("%d", node->tok.value);
	}
	if (node->right) {
		RLR(node->right, k + 1);
	}
}

void RLR_tree(Tree *tree)
{
	return RLR(tree->root, 0);
}

int RLR_sum(Node *node)
{
	if (is_sum(node)) {
		return RLR_sum(node->left) + RLR_sum(node->right);
	}
	if (is_minus(node)) {
		return RLR_sum(node->left) - RLR_sum(node->right);
	}
	if (is_div(node)) {
		return RLR_sum(node->left) / RLR_sum(node->right);
	}
	if (is_mult(node)) {
		return RLR_sum(node->left) * RLR_sum(node->right);
	}
	if (is_pow(node)) {
		return pow(RLR_sum(node->left), RLR_sum(node->right));
	}
	return node->tok.value;
}

int RLR_sum_tree(Tree *tree)
{
	return RLR_sum(tree->root);
}

void tree_node_destroy(Node *node)
{
	if ((node->left != NULL) || (node->right != NULL)) {
		if ((node->left != NULL) && is_op(node->left)) {
			tree_node_destroy(node->left);
		}
		if ((node->right != NULL) && is_op(node->right)) {
			tree_node_destroy(node->right);
		}
	}
	free(node);
}

void tree_destroy(Tree *tree)
{
	if (tree->root != NULL) {
		tree_node_destroy(tree->root);
	}
}

void reorganization(Tree *tree)
{
	Node *node = tree->root;
	if (is_sum(node)) {
		if (is_op(node->left) && is_op(node->right)) {

		}
	}
}
