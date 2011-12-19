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

    if (val == NULL) {
        node->name = '\0';
        node->value = 0;
    } else if (!strcmp(val, "+") || !strcmp(val, "*")) {
        node->name = val[0];
        node->value = 0;
    } else {
        node->name = '\0';
        node->value = atof(val);
    }

    node->right = right;
    node->left = left;

    return node;
}


void destroy_all(Node * node)
{
    if (node != NULL) {
        destroy_all(node->right);
        destroy_all(node->left);

        free(node);
    }
}


void copy(Node * src, Node * dest)
{
    dest->name = src->name;
    dest->value = src->value;
    dest->right = src->right;
    dest->left = src->left;
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


void affiche_expression(Node * node)
{
    static int in = 0;

    if (node != NULL) {
        if (in) {
            if (node->name == '+')
                printf("(");

            affiche_expression(node->left);
            if (node->name == '\0') {
                printf("%.5g", node->value);
            } else
                printf(" %c ", node->name);
            affiche_expression(node->right);

            if (node->name == '+')
                printf(")");
        } else {
            in = 1;
            affiche_expression(node->left);
            if (node->name == '\0') {
                printf("%.5g", node->value);
            } else
                printf(" %c ", node->name);
            affiche_expression(node->right);
            in = 0;
        }
    }
}


Node * clone(Node * node)
{
    Node * pt;

    if(node != NULL) {
        pt = create_node(NULL, clone(node->right), clone(node->left));
        pt->value = node->value;
        pt->name = node->name;

        return pt;
    } else
        return NULL;
}


void calcul_intermediaire(Node * node)
{
    if (node->right != NULL && node->left != NULL) {
        if (node->right->name == '\0' && node->left->name == '\0') {
            if (node->name == '+')
                node->value = node->right->value + node->left->value;
            else if (node->name == '*')
                node->value = node->right->value * node->left->value;
            node->name = '\0';
            free(node->right);
            free(node->left);
            node->right = NULL;
            node->left= NULL;
        } else {
            calcul_intermediaire(node->right);
            calcul_intermediaire(node->left);
        }
   }
}


void calcul(Node * node)
{
    while (node->right != NULL && node->left != NULL)
        calcul_intermediaire(node);
}
