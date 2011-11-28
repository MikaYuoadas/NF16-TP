#include <stdio.h>

#include "tp3.h"

int main()
{
	char id[MAX_NOM+1];
	int nb, choix;
	task * list = NULL;

	printf("Creation d'une liste.\nID premiere tache : ");
	scanf("%s", id);
	printf("Duree tache : ");
	scanf("%d", &nb);

	/* Initialisation de la liste. */
	list = cree_tache(id, nb);
	list = cree_liste(list);
	affiche_liste(list);

	do {
		printf("\n0 - Quitter\n1 - Afficher la liste\n2 - Ajouter une tache\n"
			   "3 - Annuler une tache\n4 - Chercher une tache\n5 - Vider la liste\n"
			   "Choix : ");
		scanf("%d", &choix);
		switch(choix){
			case 1:
				/* Affichage de la liste. */
				affiche_liste(list);
				break;
			case 2:
				/* Ajout d'une tache. */
				printf("\nID tache : ");
				scanf("%s", id);
				printf("Duree tache : ");
				scanf("%d", &nb);
				ajoute_tache(list, cree_tache(id, nb));
				break;
			case 3:
				/* Annulation d'une tache. */
				printf("\nID tache : ");
				scanf("%s", id);
				annule_tache(list, id);
				break;
			case 4:
				/* Recherche dans la liste.*/
				printf("\nID tache : ");
				scanf("%s", id);
				nb = search_ID(list, id);
				if (nb == -1)
					printf("Cet ID n'existe pas dans la liste.\n");
				else
					printf("La tache est %deme dans la liste.\n", nb);
				break;
			case 5:
				/* Libérer la liste. */
				libere_liste(list);
				printf("\nLa liste a ete vide.\n");
				break;
		}
	} while (choix != 0);
	return 0;
}