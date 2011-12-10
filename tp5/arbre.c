#include <stdio.h>
#include <stdlib.h>

#include "arbre.h"


Node * create_node(char val, Node * right, Node * left)
{
	Node * node;

	node = malloc(sizeof(Node));
	if (node == NULL)
		return NULL;

	if (val <= '9' || val >= '0') {
		node->name = '\0';
		node->value = val - '0';
	} else
		node->name = val;

	node->right = right;
	node->left = left;

	return node;
}


Node * saisie_expression()
{
	char exp[LEN];
	int i = 0;
	Node * node;
	pile * p;

	scanf("%s", exp);

	p = create_pile();
	
	/* TODO : pouvoir entrer un nombre composé de plusieurs chiffres */
	while (exp[i] != '\0' && i < LEN) {
		if (exp[i] == '+' || exp[i] == '*') {
			node = create_node(exp[i], depiler(p), depiler(p));
			if (node == NULL || node->right == NULL || node->left == NULL || empiler(node, p))
				return NULL;
		} else if (exp[i] >= '0' && exp[i] <= '9') {
			node = create_node(exp[i], NULL, NULL);
			if (node == NULL || empiler(node, p))
				return NULL;
		}
		i++;
	}

	if (size(p) != 1)
		return NULL;
	else
		return depiler(p);
}


void pre_ordre(Node * node)
{
	if (node != NULL) {
		if (node->name == '\0')
			printf("%d ", node->value);
		else
			printf("%c ", node->name);
		pre_ordre(node->left);
		pre_ordre(node->right);
	}
}


void in_ordre(Node * node)
{
	if (node != NULL) {
		in_ordre(node->left);
		if (node->name == '\0')
			printf("%d ", node->value);
		else
			printf("%c ", node->name);
		in_ordre(node->right);
	}
}


void post_ordre(Node * node)
{
	if (node != NULL) {
		post_ordre(node->left);
		post_ordre(node->right);
		if (node->name == '\0')
			printf("%d ", node->value);
		else
			printf("%c ", node->name);
	}
}