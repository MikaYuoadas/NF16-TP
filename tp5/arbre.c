#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "arbre.h"
#include "pile.h"

/* Nom: NF16 - TP05
 * Sujet: Arbres et calcul formel
 * Auteurs: Akim Sadaoui et Antoine Hars
 * Section: GI01
 */



/*********************************************************************/

Node * create_node(char * val, Node * right, Node * left)
{
    Node * node;
    char ** endptr = NULL;

    node = malloc(sizeof(Node));
    if (node != NULL) {
        if (val == NULL) {
            /* Par défaut le node est un 0. */
            node->name = '\0';
            node->value = 0;
        } else if (!strcmp(val, "+") || !strcmp(val, "*") || isalpha(val[0])) {
            /* Cas où le node est une variable ou un opérateur. */
            node->name = val[0];
            node->value = -42;
        } else {
            /* Cas où le node est un réel. */
            node->value = strtod(val, endptr);
            if (endptr == &val) {
                free(node);
                return NULL;
            }

            node->name = '\0';
        }

        node->right = right;
        node->left = left;
    }

    return node;
}

/*********************************************************************/

void destroy_all(Node * node)
{
    if (node != NULL) {
        destroy_all(node->right);
        destroy_all(node->left);

        free(node);
    }
}

/*********************************************************************/

void copy(Node * src, Node * dest)
{
    dest->name = src->name;
    dest->value = src->value;
    dest->right = src->right;
    dest->left = src->left;
}

/*********************************************************************/

Node * saisie_expression()
{
    char rep[LEN];
    char * exp = NULL;
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
            /* Si la chaine suivante est un opérateur. */
            r = depiler(p);
            l = depiler(p);
            node = create_node(exp, r, l);
            if (node == NULL || node->right == NULL || node->left == NULL || empiler(node, p))
                 break;
        } else {
            /* Si la chaine est un nombre ou une variable. */
            node = create_node(exp, NULL, NULL);
            if (node == NULL || empiler(node, p))
                break;
        }
        /* strtok retourne la prochaine sous chaine. */
        exp = strtok(NULL, " \t\n");
    }

    /* Si la pile ne contient qu'un node,
     * l'opération est un succés et ce node
     * est l'arbre de l'expression.
     * Sinon on libère la mémoire des nodes
     * de la pile proprement.
     */
    if (size(p) != 1)
        do {
            node = depiler(p);
            destroy_all(node);
        } while (node != NULL);
    else
        node = depiler(p);

    destroy(p);
    return node;
}

/*********************************************************************/

void pre_ordre(Node * node)
{
    if (node != NULL) {
        if (node->name == '\0')
            printf("%.2f ", node->value); /* nombre */
        else
            printf("%c ", node->name);    /* opérateur ou variable */
        pre_ordre(node->left);
        pre_ordre(node->right);
    }
}

/*********************************************************************/

void in_ordre(Node * node)
{
    if (node != NULL) {
        in_ordre(node->left);
        if (node->name == '\0')
            printf("%.2f ", node->value); /* nombre */
        else
            printf("%c ", node->name);    /* opérateur ou variable */
        in_ordre(node->right);
    }
}

/*********************************************************************/

void post_ordre(Node * node)
{
    if (node != NULL) {
        post_ordre(node->left);
        post_ordre(node->right);
        if (node->name == '\0')
            printf("%.2f ", node->value); /* nombre */
        else
            printf("%c ", node->name);    /* opérateur ou variable */
    }
}

/*********************************************************************/

void affiche_expression(Node * node)
{
    static int in = 0;

    if (node != NULL) {
        if (in) {
            /* On est dans un sous calcul, on affiche les parenthèses */

            /* On affiche des parenthèse autour des sommes prioritaires. */
            if (node->name == '+')
                printf("(");

            affiche_expression(node->left);
            if (node->name == '\0')
                printf("%.5g", node->value);
            else if (isalpha(node->name))
                printf("%c", node->name);
            else
                printf(" %c ", node->name);
            affiche_expression(node->right);

            /* Sommes prioritaires. */
            if (node->name == '+')
                printf(")");
        } else {
            /* Premier calcul de l'expression, pas besoin de parenthèse. */
            in = 1;
            affiche_expression(node->left);
            if (node->name == '\0')
                printf("%.5g", node->value);
            else if (isalpha(node->name))
                printf("%c", node->name);
            else
                printf(" %c ", node->name);
            affiche_expression(node->right);
            in = 0;
        }
    }
}

/*********************************************************************/

Node * clone(Node * node)
{
    Node * pt = NULL;

    /* On recrée un node identique et on clone les fils droit et gauche. */
    if (node != NULL) {
        pt = create_node(NULL, clone(node->right), clone(node->left));
        pt->value = node->value;
        pt->name = node->name;

        return pt;
    } else
        return NULL;
}

/*********************************************************************/

void calcul_intermediaire(Node * node)
{
    Node * pt = NULL;

    if (node != NULL && node->right != NULL && node->left != NULL) {
        if (node->right->name == '\0' && node->left->name == '\0') {
            /* Si les deux fils sont des nombres, on effectue le calcul. */
            if (node->name == '+')
                node->value = node->right->value + node->left->value;
            else if (node->name == '*')
                node->value = node->right->value * node->left->value;

            node->name = '\0';
            destroy_all(node->right);
            destroy_all(node->left);
            node->right = NULL;
            node->left= NULL;
        } else if ((isalpha(node->right->name) && node->left->name == '\0') ||
                   (isalpha(node->left->name) && node->right->name == '\0')){
            /* Sinon si un des fils et une varible et l'autre un nombre, on
             * traite les cas particuliers.
             */
            if ((node->left->value == 0 || node->right->value == 0) && node->name == '*') {
                /* multiplication par 0. */
                destroy_all(node->right);
                destroy_all(node->left);

                node->right = NULL;
                node->left = NULL;
                node->value = 0;
                node->name = '\0';
            } else if ((node->left->value == 0 && node->name == '+')
                    || (node->left->value == 1 && node->name == '*')) {
                /* Somme avec 0 ou multiplication par 1. */
                destroy_all(node->left);
                pt = node->right;
                copy(node->right, node);
                free(pt);
            } else if ((node->right->value == 0 && node->name == '+')
                    || (node->right->value == 1 && node->name == '*')) {
                /* Somme avec 0 ou multiplication par 1 (symétrique). */
                destroy_all(node->right);
                pt = node->left;
                copy(node->left, node);
                free(pt);
            }
        } else {
            /* Sinon On essaie de réduire les sous arbres gauche et droit. */
            calcul_intermediaire(node->right);
            calcul_intermediaire(node->left);
        }
   }
}

/*********************************************************************/

void calcul(Node * node)
{
    Node * pt = NULL;

    if (node != NULL && node->right != NULL && node->left != NULL) {
        /* Avant d'aller plus loin on s'assure que les sous arbres
         * gauche et droit sont déjà réduit au minimum.
         */
        calcul(node->right);
        calcul(node->left);

        if (node->right->name == '\0' && node->left->name == '\0') {
            /* Si les deux fils sont des nombres, on effectue le calcul. */
            if (node->name == '+')
                node->value = node->right->value + node->left->value;
            else if (node->name == '*')
                node->value = node->right->value * node->left->value;

            node->name = '\0';
            destroy_all(node->right);
            destroy_all(node->left);
            node->right = NULL;
            node->left= NULL;
        } else if ((node->left->value == 0 || node->right->value == 0) && node->name == '*') {
            /* multiplication par 0. */
            destroy_all(node->right);
            destroy_all(node->left);

            node->right = NULL;
            node->left = NULL;
            node->value = 0;
            node->name = '\0';
        } else if ((node->left->value == 0 && node->name == '+') || (node->left->value == 1 && node->name == '*')) {
            /* Somme avec 0 ou multiplication par 1 (symétrique). */
            destroy_all(node->left);
            pt = node->right;
            copy(node->right, node);
            free(pt);
        } else if ((node->right->value == 0 && node->name == '+') || (node->right->value == 1 && node->name == '*')) {
            /* Somme avec 0 ou multiplication par 1 (symétrique). */
            destroy_all(node->right);
            pt = node->left;
            copy(node->left, node);
            free(pt);
        }
    }
}

/*********************************************************************/

void developpement(Node * node)
{
    Node * a = NULL;
    Node * b = NULL;
    Node * c = NULL;
    Node * d = NULL;

    if (node != NULL && node->right != NULL && node->left != NULL) {
        /* Avant de développer l'opérateur en cours, on s'assure
         * que les sous arbres sont complétement développés.
         */
        developpement(node->right);
        developpement(node->left);

        if (node->name == '*') {
            /* Si l'opérateur est une multiplication on développe. */
            if (node->right->name == '+' && node->left->name == '+') {
                /* Cas d'une somme à gauche et à droite. */
                a = node->left->left;
                b = node->left->right;
                c = node->right->left;
                d = node->right->right;

                node->name = '+';
                node->left->left = create_node("*", c, a);
                node->left->right = create_node("*", d, clone(a));
                node->right->left = create_node("*", clone(c), b);
                node->right->right = create_node("*", clone(d), clone(b));
            } else if (node->right->name == '+') {
                /* Cas d'une somme à droite et d'un scalaire à gauche. */
                a = node->left;
                b = node->right->left;
                c = node->right->right;

                node->name = '+';
                free(node->right);

                node->left = create_node("*", b, a);
                node->right = create_node("*", c, clone(a));
            } else if (node->left->name == '+') {
                /* Cas d'une somme à gauche et d'un scalaire à droite. */
                a = node->right;
                b = node->left->left;
                c = node->left->right;

                node->name = '+';
                free(node->left);

                node->right = create_node("*", b, a);
                node->left = create_node("*", c, clone(a));
            } else
                return;
        }
    }
}
