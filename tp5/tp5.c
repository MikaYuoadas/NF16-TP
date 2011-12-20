#include <stdio.h>

#include "arbre.h"

#define MAX 5


int main()
{
    int choice, i, j;
    char c;
    Node * list[MAX] = {NULL, NULL, NULL, NULL, NULL};

    do {
        printf("\n\n******************** Menu ********************\n\n"
               "0 - Quitter.\n"
               "1 - Saisir une expression.\n"
               "2 - Afficher les expressions.\n"
               "3 - Autres affichages.\n"
               "4 - Dupliquer un arbre.\n"
               "5 - Détruire un arbre.\n"
               "6 - Réduire la hauteur d'un arbre.\n"
               "7 - Effectuer tous les calculs possible.\n"
               "8 - Développer une expression.\n"
               "9 - Dériver une expression.\n"
               "\nChoix : ");
        scanf("%d", &choice);
        printf("\n");

        switch(choice) {
            /* Quitter */
            case 0 :
                printf("\n\n******************** FIN ********************\n\n");
                break;

            /* Saisir une expression */
            case 1 :
                i = 0;
                while (i < MAX && list[i] != NULL)
                    i++;

                if (i < MAX)
                    list[i] = saisie_expression();
                else
                    printf("Nombre d'expression maximum atteint.");
                break;

            /* Afficher une expression */
            case 2 :
                for (i = 0; i < MAX; i++) {
                    printf("Expression %d : ", i);
                    if (list[i] != NULL)
                        affiche_expression(list[i]);
                    else
                        printf("NULL");
                    printf("\n");
                }
                break;

            /* Autres Affichages */
            case 3 :
                printf("Affichage de l'expression numéro : ");
                scanf("%d", &i);

                if (i < MAX && list[i] != NULL) {
                    printf("\npréfixée : ");
                    pre_ordre(list[i]);
                    printf("\ninfixée : ");
                    in_ordre(list[i]);
                    printf("\npostfixée : ");
                    post_ordre(list[i]);
                } else
                    printf("Expression NULL");

            /* Dupliquer un arbre */
            case 4 :
                printf("Copie de l'expression numéro : ");
                scanf("%d", &i);
                printf("Dans l'emplacement numéro : ");
                scanf("%d", &j);

                if (i < MAX && j < MAX) {
                    if (list[j] == NULL)
                        list[j] = clone(list[i]);
                    else
                        printf("Emplacement de destination n'est pas vide !");
                } else
                    printf("Indice d'emplacement incorrect !");
                break;

            /* Détruire un arbre */
            case 5 :
                printf("Suppression de l'expression numéro : ");
                scanf("%d", &i);

                if (i < MAX)
                    destroy_all(list[i]);
                break;

            /* Réduire la hauteur d'un arbre */
            case 6 :
                printf("Réduction de l'expression numéro : ");
                scanf("%d", &i);

                if (i < MAX && list[i] != NULL)
                    calcul_intermediaire(list[i]);
                else
                    printf("Pas d'expression à réduire.");
                break;

            /* Effectuer tous les calculs possible */
            case 7 :
                printf("Calcul de l'expression numéro : ");
                scanf("%d", &i);

                if (i < MAX && list[i] != NULL)
                    calcul(list[i]);
                else
                    printf("Pas d'expression à calculer.");
                break;

            /* Développer une expression */
            case 8 :
                printf("Développement de l'expression numéro : ");
                scanf("%d", &i);

                if (i < MAX && list[i] != NULL)
                    developpement(list[i]);
                else
                    printf("Pas d'expression à développer.");
                break;

            /* Dériver une expression */
            case 9 :
                printf("Dérivation de l'expression numéro : ");
                scanf("%d", &i);
                printf("Varible de dérivation : ");
                scanf("%c", &c);

                if (i < MAX && list[i] != NULL)
                    derivation(list[i], c);
                else
                    printf("Pas d'expression à dériver.");
                break;
        }
    } while (choice != 0);

    return 0;
}
