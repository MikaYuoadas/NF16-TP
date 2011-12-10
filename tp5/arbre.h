#ifndef ARBRE
#define ARBRE

#define LEN 100


typedef struct Node {
    struct Node * left;		/* fils gauche */
    struct Node * right;	/* fils droit */
    char name;				/* nom de l'opérateur */
    double value;			/* valeur de la constante */
} Node;


Node * create_node(char * val, Node *left, Node *right);
Node * saisie_expression();
void pre_ordre(Node * node);
void in_ordre(Node * node);
void post_ordre(Node * node);
void affiche_expression(Node * node);
Node * clone(Node * node);
void calcul_intermediaire(Node * node);

#endif
