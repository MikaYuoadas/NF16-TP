#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arbre.h"
#include "pile.h"


Node * create_node(char * val, Node * right, Node * left)
{
    Node * node;

    node = malloc(sizeof(Node));
    if (node == NULL)
        return NULL;

    if (!strcmp(val, "+") || !strcmp(val, "*"))
        node->name = val[0];
    else {
        node->name = '\0';
        node->value = atof(val);
    }

    node->right = right;
    node->left = left;

    return node;
}


Node * saisie_expression()
{
    char rep[LEN];
    char * exp = NULL;
    char ** endptr = NULL;
    Node * node = NULL;
    pile * p = NULL;
    Node * r = NULL;
    Node * l = NULL;

    printf("Saisissez une expression en notation polonaise inverse :\n");
    fgets(rep, LEN, stdin);
    exp = strtok(rep, " \t\n");

    p = create_pile();

    while (exp != NULL) {
        if (!strcmp(exp, "+") || !strcmp(exp, "*")) {
            r = depiler(p);
            l = depiler(p);
            node = create_node(exp, r, l);
            if (node == NULL || node->right == NULL || node->left == NULL || empiler(node, p))
                return NULL;
        } else {
            strtod(exp, endptr);
            if (endptr == &exp)
                return NULL;

            node = create_node(exp, NULL, NULL);
            if (node == NULL || empiler(node, p))
                return NULL;
        }
        exp = strtok(NULL, " \t\n");
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
            printf("%.2f ", node->value);
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
            printf("%.2f ", node->value);
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
            printf("%.2f ", node->value);
        else
            printf("%c ", node->name);
    }
}
