#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>

#include "tp3.h"

/*********************************************************************/

task * cree_tache(char caract[MAX_NOM+1], int duree)
{
	task * pt = NULL;

	if (strcmp(caract, "") == 0 || duree <= 0)
		return NULL;
	pt = malloc(sizeof(task));
	if (pt == NULL)
		return NULL;
	strcpy(pt->ID, caract);
	pt->duree = duree;
	pt->psuivant = NULL;
	
	return pt;
}

/*********************************************************************/

task * cree_liste(task *tache)
{
	task * pt = NULL;
	
	/* Cr�ation de la sentinelle */
	pt = cree_tache("null", '0');
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
				printf("tache : %s\t duree : %d\n", pt->ID, pt->duree);
				pt = pt->psuivant;
			}
		}
	}
}

/*********************************************************************/

int ajoute_tache(task *list_task, task *ptache)
{
	task * pt = NULL;

	/* On v�rifie la coh�rence des arguments. */
	if (list_task == NULL || ptache == NULL)
		return 0;
	/* On v�rifie que l'identifiant est unique. */
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

	/* On parcourt la liste jusqu'� retourner � la sentinelle
	   ou jusqu'� trouver la tache recherch�e. */
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

	/* On supprime chaque �l�ment un par un � partir
	   du premier apr�s la sentinelle. */
	while (pt1 != list_task) {
		pt2 = pt1->psuivant;
		free(pt1);
		pt1 = pt2; 
	}

	/* La sentinelle pointe sur elle-m�me. */
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

	/* Recherche du dernier �l�ment � d�piler */
	while (pt->psuivant != list_task) {
		pre = pt;
		pt = pt->psuivant;
	}

	printf("ex�cution LIFO de la t�che  %s (%d)", pt->ID, pt->duree);
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
	/* Recherche de la place de la t�che � ins�rer en fonction de la dur�e
	 * des �l�ments de la liste.
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

task * load_data(char * nom_fichier)
{
	task * list = NULL;
	FILE* fsource = NULL;
	int i = 0;
	char name[MAX_NOM+1] = "", nom;
	int duree;

	fsource = fopen(nom_fichier, "r");
	/* Probl�me d'ouverture du fichier/ */
	if (fsource == NULL)
		printf("erreur dans l'ouverture du fichier\n\n");
	else {
		/* Copie de toutes les t�ches du fichier dans la liste. */
		while(fscanf(fsource,"%s\t%d\n",name,&duree) != EOF) {
			char *nom = (char*)malloc(MAX_NOM*sizeof(char));

			for(i=0; i < MAX_NOM+1;i++)
                nom[i] = name[i];

            if(list == NULL)
                list = cree_liste(cree_tache(nom, duree));
            else
            	ajoute_tache(list, cree_tache(nom,duree));
		}
		fclose(fsource);
	}
	return list;
}

/*********************************************************************/

task * fusion_listes(task *list_task1, task *list_task2)
{
	task * fusion = NULL;
	task * old = NULL;
	task * newTask;

	while(list_task1 || list_task2)
	{
		if(list_task1 && (!list_task2 || list_task1->duree <= list_task2->duree)) // Cas ajout tache de la liste 1.
		{
			newTask = malloc(sizeof(task));
			newTask->duree = list_task1->duree;
			newTask->ID = list_task1->ID;
//			newTask->priorite = list_task1->priorite;
			newTask->psuivant = NULL;
			list_task1 = list_task1->psuivant;
		}
		else if(list_task2 && (!list_task1 || list_task2->duree <= list_task1->duree)) // Cas ajout tache de la liste 2.
		{
			newTask = malloc(sizeof(task));
			newTask->duree = list_task2->duree;
			newTask->ID = list_task2->ID;
//			newTask->priorite = list_task2->priorite;
			newTask->psuivant = NULL;
			list_task2 = list_task2->psuivant;
		}

		if(fusion == NULL)
		{
			fusion = newTask;
		}
		else
		{
			old->psuivant = newTask;
		}
		old = newTask;
	}
	return fusion;
}


