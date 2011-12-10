#ifndef PILE
#define PILE

#include "arbre.h"


typedef struct pile {
    Node * node;
    struct pile * next;
} pile;


pile * create_pile();
void destroy(pile * p);
int size(pile * p);
int empiler(Node * node, pile * p);
Node * depiler(pile * p);

#endif
