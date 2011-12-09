#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tp3.h"

/* Nom: NF16 - TP03
 * Sujet: Listes chaînées.
 * Auteurs: Akim Sadaoui et Antoine Hars
 * Section: GI01
 */

int main()
{
	char id[MAX_NOM+1], filename[100];
	int nb, i, choix, indice = 0;
	task * T[MAX_LIST] = {NULL,NULL,NULL,NULL,NULL};

	do {
		printf("\n\n********************** Menu Listes **********************\n\n"
			   "0 - Quitter.\n"
			   "1 - Creer une liste de taches.\n"
			   "2 - Charger une liste de taches.\n"
			   "3 - Afficher les listes.\n"
			   "4 - Acceder aux taches d'une liste.\n"
			   "5 - Liberer une liste de taches\n"
			   "6 - Fusionner deux listes.\n"
			   "\nChoix : ");
		scanf("%d", &choix);
		printf("\n");

		switch(choix) {
			/* Quitter. */
			case 0 :
				printf("\n\n********************** FIN **********************\n\n");
				break;

			/* Creer une liste de taches. */
			case 1 :
				while (indice < MAX_LIST && T[indice] != NULL) {
					indice++;
				}
				if (indice < MAX_LIST)
					T[indice] = cree_liste(T[indice]);

				break;

			/* Charger une liste de taches. */
			case 2 :
				printf("Le nom du fichier de taches : ");
				scanf("%s", filename);
				printf("Le nombre de tâches à charger : ");
				scanf("%d", &i);
				printf("L'indice de la liste à modifier : ");
				scanf("%d", &indice);

				T[indice] = load_data(filename, i);

				break;

			/* Afficher les listes. */
			case 3 :
				for (i = 0; i < MAX_LIST; i++) {
					printf("liste (%d) :\n",i);
					affiche_liste(T[i]);
					printf("\n");
					}
				break;

			/* Accéder aux tâches d'une liste. */
			case 4 :
				printf("Choix de la liste numero : ");
				scanf("%d", &indice);

				if (T[indice] != NULL) {
					do {
						printf("\n\n********************** Menu Taches **********************\n\n"
					   		   "0 - Quitter.\n"
							   "1 - Afficher la liste de taches.\n"
							   "2 - Ajouter une tache.\n"
							   "3 - Annuler une tache.\n"
							   "4 - Executer une tache en FIFO.\n"
							   "5 - Executer une tache en LIFO.\n"
							   "6 - Inserer une tache dans la liste selon la durée.\n"
							   "7 - Inserer une tache dans la liste selon la priorité.\n"
                               "8 - Mettre à jour la priorité des taches.\n"
							   "9 - Revenir au menu des listes.\n"
							   "\nChoix : ");
						scanf("%d", &choix);
						printf("\n");

						switch(choix) {
							/* Quitter. */
							case 0 :
								printf("\n\n********************** FIN **********************\n\n");
								break;

							/* Afficher la liste de tâches. */
							case 1 :
								affiche_liste(T[indice]);
								break;

							/* Ajouter une tâche. */
							case 2 :

								printf("id tache : ");
								scanf("%s", id);
								printf("duree tache : ");
								scanf("%d", &nb);

								nb = ajoute_tache(T[indice], cree_tache(id,nb));
								if (nb == 1)
									printf("Ajout reussi.\n");
								else
									printf("Erreur ajout.\n");

								break;

							/* Annuler une tâche. */
							case 3 :

								printf("Tache a supprimer : ");
								scanf("%s", id);

								T[indice] = annule_tache(T[indice], id);

								break;

							/* Exécuter une tâche en FIFO. */
							case 4 :

								printf("Nombre de taches a executer : ");
								scanf("%d", &nb);
								printf("\n");

								if (nb > 0) {
									for (i = 0; i < nb; i++)
										T[indice] = execute_tache_FIFO(T[indice]);
								}
								else
									printf("Erreur du nombre de taches a executer.\n");

								break;

							/* Exécuter une tâche en LIFO. */
							case 5 :

								printf("Nombre de taches a executer : ");
								scanf("%d", &nb);
								printf("\n");

								if (nb > 0) {
									for (i = 0; i <nb; i++)
										T[indice] = execute_tache_LIFO(T[indice]);
								}
								else
									printf("Erreur du nombre de taches a executer.\n");

								break;

							/* Insérer une tâche dans la liste selon la durée. */
							case 6 :

								printf("id tache : ");
								scanf("%s", id);
								printf("duree tache : ");
								scanf("%d", &nb);

								T[indice] = insere_tache(T[indice], cree_tache(id,nb));

								break;

							/* Insérer une tâche dans la liste selon la priorite. */
							case 7 :

								printf("id tache : ");
								scanf("%s", id);
								printf("duree tache : ");
								scanf("%d", &nb);

								T[indice] = insere_tache_priorite(T[indice], cree_tache(id,nb));

								break;

                            /* Mettre à jour la priorité des taches */
                            case 8 :

                                printf("Priorités décrémentés de 1.\n");
                                MAJ_priorite(T[indice]);

                                break;

							/* Revenir au menu des listes. */
							case 9 :
								break;

							default :
								printf("Commande incorrecte.\n");
								break;
						}
					} while (choix != 0 && choix != 9);
				}
				break;


			/* Libérer la liste de tâches. */
			case 5 :
				printf("Choix de la liste à libérer : ");
				scanf("%d", &indice);
				T[indice] = libere_liste(T[indice]);

				break;


			/* Fusionner deux listes. */
			case 6 :
				printf("Indice de la premiere liste :");
				scanf("%d", &nb);
				printf("Indice de la seconde liste :");
				scanf("%d", &indice);

				T[nb] = fusion_listes(T[nb],T[indice]);
				break;

			default :
				printf("Commande incorrecte.\n");
				break;
		}
	} while (choix != 0);

	return 0;

}


