#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _node {
	int value;
	struct _node *left;
	struct _node *right;
} Node;

Node *set_node(int value)
{
	Node *new = malloc(sizeof(*new)); 
	new->value = value;
	new->left = NULL;
	new->right = NULL;
	return new;
}

void add_node(Node *node, int value)
{
	if (value < node->value)
	{
		if (node->left == NULL)
			node->left = set_node(value);
		else
			add_node(node->left, value);
	}
	else if (value > node->value)
	{
		if (node->right == NULL)
			node->right = set_node(value);
		else
			add_node(node->right, value);
	}
}

char *get_indent(char* ind, int i)
{
	char *dent = "  ";
	int j;

	for (j = 0; j < i; j++)
		strcat(ind, dent);
	return ind;
}

void print_tree(Node *node, int i)
{
	char ind[32] = { '\0' };
	get_indent(ind, i);

	if (node->right != NULL)
		print_tree(node->right, i+1);

	printf("%s%d\n", ind, node->value);

	if (node->left != NULL)
		print_tree(node->left, i+1);
}

int main(void)
{
	Node r, *root;
	root = &r;
	root = set_node(10);

	add_node(root, 12);
	add_node(root, 9);
	add_node(root, 15);
	add_node(root, 3);
	add_node(root, 7);

	print_tree(root, 0);

	return 0;
}
