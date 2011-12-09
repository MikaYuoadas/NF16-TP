#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "tp3.h"

/* Nom: NF16 - TP03
 * Sujet: Listes chaînées.
 * Auteurs: Akim Sadaoui et Antoine Hars
 * Section: GI01
 */



/*********************************************************************/

task * cree_tache(char caract[MAX_NOM+1], int duree)
{
	task * pt = NULL;

	if (strcmp(caract, "") == 0 || duree < 0)
		return NULL;
	pt = malloc(sizeof(task));
	if (pt == NULL)
		return NULL;
	strcpy(pt->ID, caract);
	pt->duree = duree;
	pt->priorite = (duree/10 < 5 ? duree/10 : 5);
	pt->psuivant = NULL;

	return pt;
}

/*********************************************************************/

task * cree_liste(task *tache)
{
	task * pt = NULL;

	/* Création de la sentinelle */
	pt = cree_tache("null", 0);
	if (tache != NULL) {
		pt->psuivant = tache;
		tache->psuivant = pt;
	}
	else
		pt->psuivant = pt;

	return pt;
}

/*********************************************************************/

void affiche_liste(task *list_task)
{
	task * pt = NULL;

	pt = list_task;
	if (pt == NULL)
		printf("Pointeur NULL.\n");
	else if (strcmp(list_task->ID, "null") == 0) {
		pt = list_task->psuivant;
		if (pt == list_task)
			printf("Liste vide.\n");
		else {
			printf("Liste de taches:\n");
			while(pt != list_task) {
				printf("tache : %s\t duree : %d\tpriorite : %d\n", pt->ID, pt->duree, pt->priorite);
				pt = pt->psuivant;
			}
		}
	}
}

/*********************************************************************/

int ajoute_tache(task *list_task, task *ptache)
{
	task * pt = NULL;

	/* On vérifie la cohérence des arguments. */
	if (list_task == NULL || ptache == NULL)
		return 0;
	/* On vérifie que l'identifiant est unique. */
	if (search_ID(list_task, ptache->ID) != -1)
		return 0;

	/* On ajoute la tache. */
	pt = list_task;
	while(pt->psuivant != list_task)
		pt = pt->psuivant;
	pt->psuivant = ptache;
	ptache->psuivant = list_task;
	return 1;
}

/*********************************************************************/

int search_ID(task * list_task, char * ID)
{
	int i = 0;
	int found = 0;
	task * pt = NULL;
	pt = list_task;

	/* On parcourt la liste jusqu'à retourner à la sentinelle
	   ou jusqu'à trouver la tache recherchée. */
	while(pt->psuivant != list_task && !found) {
		i++;
		pt = pt->psuivant;
		if (!strcmp(pt->ID, ID))
			found = 1;
	}

	if (found)
		return i;
	else
		return -1;
}

/*********************************************************************/

task * annule_tache(task *list_task, char caract[MAX_NOM+1])
{
	task * pt1 = NULL;
	task * pt2 = NULL;
	int pos, i;

	if (list_task == NULL)
		return NULL;
	pt1 = list_task;
	pt2 = list_task->psuivant;
	pos = search_ID(list_task, caract);
	/* Si la tache n'existe pas on retourne la liste directement. */
	if (pos != -1) {
		for (i = 1; i < pos; i++) {
			pt1 = pt2;
			pt2 = pt2->psuivant;
		}
		pt1->psuivant = pt2->psuivant;
		free(pt2);
	}
	return list_task;
}

/*********************************************************************/

task * libere_liste(task *list_task)
{
	task * pt1 = NULL;
	task * pt2 = NULL;
	pt1 = list_task->psuivant;

	if (list_task == NULL)
		return NULL;

	/* On supprime chaque élément un par un à partir
	   du premier après la sentinelle. */
	while (pt1 != list_task) {
		pt2 = pt1->psuivant;
		free(pt1);
		pt1 = pt2;
	}

	/* La sentinelle pointe sur elle-même. */
	list_task->psuivant = list_task;
	return list_task;
}

/*********************************************************************/

task * execute_tache_FIFO(task *list_task)
{
	task * pt = NULL;

	pt = list_task->psuivant;
	if (pt == list_task)
		return list_task;

	printf("Execution FIFO de la tache %s (%d)", pt->ID, pt->duree);
	sleep(1);

	list_task->psuivant = pt->psuivant;
	free(pt);
	printf("\n");
	return list_task;
}

/*********************************************************************/

task * execute_tache_LIFO(task *list_task)
{
	task * pt = NULL;
	task * pre = NULL;

	pre = pt = list_task->psuivant;
	if (pt == list_task)
		return list_task;

	/* Recherche du dernier élément à dépiler */
	while (pt->psuivant != list_task) {
		pre = pt;
		pt = pt->psuivant;
	}

	printf("exécution LIFO de la tâche  %s (%d)", pt->ID, pt->duree);
	sleep(1);

	pre->psuivant = list_task;
	free(pt);
	printf("\n");
	return list_task;
}

/*********************************************************************/

task * insere_tache(task *list_task, task *ptache)
{
	task * pt1 = NULL;
	task * pt2 = NULL;

	if (list_task == NULL || ptache == NULL)
		return list_task;

	pt1 = list_task;
	pt2 = list_task->psuivant;
	/* Recherche de la place de la tâche à insérer en fonction de la durée
	 * des éléments de la liste.
	 */
	while (pt2->duree <= ptache->duree && pt2 != list_task) {
		pt1 = pt2;
		pt2 = pt2->psuivant;
	}

	pt1->psuivant = ptache;
	ptache->psuivant = pt2;

	return list_task;
}

/*********************************************************************/

task * load_data(char * nom_fichier, int nb_taches)
{
	task * list = NULL;
	FILE* fsource = NULL;
	int i = 0, duree, cmp = 0;
	char name[MAX_NOM+1] = "", nom;

	fsource = fopen(nom_fichier, "r");
	/* Problème d'ouverture du fichier/ */
	if (fsource == NULL)
		printf("erreur dans l'ouverture du fichier\n\n");
	else {
		/* Copie de toutes les tâches du fichier dans la liste. */
		while((fscanf(fsource,"%s\t%d\n",name,&duree) != EOF) && (cmp < nb_taches)) {
			char *nom = (char*)malloc(MAX_NOM*sizeof(char));

			for(i=0; i < MAX_NOM+1;i++)
                nom[i] = name[i];

            if(list == NULL)
                list = cree_liste(cree_tache(nom, duree));
            else
            	ajoute_tache(list, cree_tache(nom,duree));
            cmp++;
		}
		fclose(fsource);
	}
	return list;
}

/*********************************************************************/

task * fusion_listes(task *list_task1, task *list_task2)
{
    task * pt = NULL;
	task * old = NULL;
    task * t1 = NULL;
    task * t2 = NULL;

    if (list_task1 == NULL || list_task2 == NULL)
        return NULL;

    t1 = list_task1->psuivant;
    t2 = list_task2->psuivant;
    old = t1;

    while (t1 != list_task1 || t2 != list_task2) {
        if (t1 != list_task1 && (t2 == list_task2 || t1->duree <= t2->duree)) {
            pt = t1;
            t1 = t1->psuivant;
        } else if (t2 != list_task2 && (t1 == list_task1 || t1)) {
            pt = t2;
            t2 = t2->psuivant;
        }
        old->psuivant = pt;
        old = pt;
    }

    old->psuivant = list_task1;
    list_task2->psuivant = list_task2;

	return list_task1;
}
