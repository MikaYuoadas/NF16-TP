#include <stdio.h>

#include "arbre.h"


int main()
{
    Node * node;
    node = saisie_expression();
    pre_ordre(node);
    printf("\n");
    in_ordre(node);
    printf("\n");
    post_ordre(node);
    printf("\n");
    return 0;
}
