#include <stdio.h>
#include <stdlib.h>

#include "arbre.h"

#define MAX 5


int getint();


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
               "7 - Effectuer tous les calculs possibles.\n"
               "8 - Développer une expression.\n"
               "9 - Dériver une expression.\n"
               "\nChoix : ");
        choice = getint();
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
                    printf("Nombre maximum d'expressions atteint.");
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
                i = getint();

                if (i < MAX && list[i] != NULL) {
                    printf("\npréfixée : ");
                    pre_ordre(list[i]);
                    printf("\ninfixée : ");
                    in_ordre(list[i]);
                    printf("\npostfixée : ");
                    post_ordre(list[i]);
                } else
                    printf("Expression NULL");
                break;

            /* Dupliquer un arbre */
            case 4 :
                printf("Copie de l'expression numéro : ");
                i = getint();
                printf("Dans l'emplacement numéro : ");
                j = getint();

                if (i < MAX && j < MAX) {
                    if (list[j] == NULL) {
                        printf("\nDuplication de l'arbre %d vers l'emplacement %d.", i, j);
                        list[j] = clone(list[i]);
                    } else
                        printf("\nEmplacement de destination n'est pas vide !");
                } else
                    printf("\nIndice d'emplacement incorrect !");
                break;

            /* Détruire un arbre */
            case 5 :
                printf("Suppression de l'expression numéro : ");
                i = getint();

                if (i < MAX) {
                    destroy_all(list[i]);
                    list[i] = NULL;
                    printf("\nExpression %d supprimée.", i);
                } else
                    printf("\nIndice d'emplacement incorrect !");
                break;

            /* Réduire la hauteur d'un arbre */
            case 6 :
                printf("Réduction de l'expression numéro : ");
                i = getint();

                if (i < MAX && list[i] != NULL) {
                    calcul_intermediaire(list[i]);
                    printf("\nCalcul intermédiaire de l'expression %d effectué", i);
                } else
                    printf("\nPas d'expression à réduire.");
                break;

            /* Effectuer tous les calculs possibles */
            case 7 :
                printf("Calcul de l'expression numéro : ");
                i = getint();

                if (i < MAX && list[i] != NULL) {
                    calcul(list[i]);
                    printf("\nL'expression %d a été réduite au maximum.", i);
                } else
                    printf("\nPas d'expression à calculer.");
                break;

            /* Développer une expression */
            case 8 :
                printf("Développement de l'expression numéro : ");
                i = getint();

                if (i < MAX && list[i] != NULL) {
                    developpement(list[i]);
                    printf("\nLes produits de l'expression %d ont été développés.", i);
                } else
                    printf("\nPas d'expression à développer.");
                break;

            /* Dériver une expression */
            case 9 :
                printf("Dérivation de l'expression numéro : ");
                i = getint();
            	printf("Variable de dérivation : ");
			    c = getchar();

                if ((c > 'z' || c < 'a') && (c > 'Z' || c < 'A'))
                    c = 'x';

                if (i < MAX && list[i] != NULL) {
                    derivation(list[i], c);
                    printf("\nL'expression %d a été dérivé par %c.\n"
                           "(il est conseillé d'utiliser la fonction calcul "
                           "pour simplifier le résultat)", i, c);
                } else
                    printf("\nPas d'expression à dériver.");

                while ((c = getchar()) != '\n' && c != EOF);
                break;
        }
    } while (choice != 0);

    for (i = 0; i < MAX; i++)
        if (list[i] != NULL)
            destroy_all(list[i]);

    return 0;
}


int getint()
{
    char rep[11];

    fgets(rep, 11, stdin);

    return atoi(rep);
}
