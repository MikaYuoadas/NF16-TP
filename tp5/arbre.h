#ifndef  ARBRE
#define ARBRE

#include "pile.h"

#define LEN 20


typedef struct pile pile;

typedef struct Node {
    struct Node * left;		/* fils gauche */
    struct Node * right;	/* fils droit */
    char name;				/* nom de l’opérateur */
    int value;				/* valeur de la constante */
} Node;


Node * create_node(char val, Node *left, Node *right);
Node * saisie_expression();
void pre_ordre(Node * node);
void in_ordre(Node * node);
void post_ordre(Node * node);

#endif
