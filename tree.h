#ifndef TREE_H
#define TREE_H
#include "stack.h"


typedef struct tree_{
	Node *root;
} Tree;

void tree_init(Tree *tree);
bool is_sum(Node *node);
bool is_mult(Node *node);
bool is_pow(Node *node);
bool is_div(Node *node);
bool is_minus(Node *node);
bool is_op(Node *node);
bool is_terminal(Node *node);
bool is_left_bracket(Node *node);
bool is_right_bracket(Node *node);
int get_prior(Node *node);
char get_assoc(Node *node);
void polish(Stack *stack);
Node *build_sub_tree(Stack *stack);
void build_tree(Tree *tree, Stack *stack);
void RLR_tree(Tree *tree);
int RLR_sum_tree(Tree *tree);
void tree_destroy(Tree *tree);
void reorganization(Tree *tree);
#endif