#include <stdio.h>

#include "arbre.h"


int main()
{
    Node * node;
    Node * node2;

    node = saisie_expression();

    printf("\nPré ordre : ");
    pre_ordre(node);
    printf("\nIn ordre : ");
    in_ordre(node);
    printf("\nPost ordre : ");
    post_ordre(node);

    printf("\n\nAffichage formaté : ");
    affiche_expression(node);
    printf("\nAffichage formaté clone : ");
    node2 = clone(node);
    affiche_expression(node2);

    printf("\n\nCalcul Complet : ");
    calcul(node);
    affiche_expression(node);
    printf("\nCalcul intermédiaire : ");
    calcul_intermediaire(node2);
    affiche_expression(node2);
    printf("\n");

    destroy_all(node);
    destroy_all(node2);

    return 0;
}
