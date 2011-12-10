#include <stdio.h>

#include "arbre.h"


int main()
{
    Node * node;
    Node * node2;
    node = saisie_expression();
    pre_ordre(node);
    printf("\n");
    in_ordre(node);
    printf("\n");
    post_ordre(node);
    printf("\n");
    affiche_expression(node);
    printf("\n");
    node2 = clone(node);
    affiche_expression(node2);
    printf("\nCalcul complet : ");
    calcul(node);
    affiche_expression(node);
    printf("\nCalcul intermédiaire : ");
    calcul_intermediaire(node2);
    affiche_expression(node2);
    printf("\n");

    return 0;
}
