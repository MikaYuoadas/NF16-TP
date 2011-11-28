#include <string.h>
#include <stdio.h>
#include <windows.h>

#include "tp3.h"


task * cree_tache(char caract[MAX_NOM+1], int duree)
{
	task * pt = NULL;

	if (strcmp(caract, "") == 0 or duree <= 0)
		return NULL;
	pt = malloc(sizeof(task));
	if (pt == NULL)
		return NULL;
	strcpy(pt->ID, caract);
	pt->duree = duree;
	pt->psuivant = NULL;
	return pt;
}

task * cree_liste(task *tache)
{
	task * pt = NULL;
	
	/* Création de la sentinelle */
	pt = cree_tache("null", -1);
	if (pt == NULL)
		return NULL;
	pt->psuivant = tache;
	tache->psuivant = pt;
	return pt;
}

void affiche_liste(task *list_task)
{
	task * pt = NULL;
	pt = list_task->psuivant;
	printf("\n");
	if (list_task == NULL)
		print("Pointeur NULL.\n");
	else if (pt == list_task)
		printf("Liste vide.\n");
	while(pt != list_task) {
		printf("id : %s\t duree : %d\n", pt->ID, pt->duree);
		pt = pt->psuivant;
	}
}

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

int search_ID(task * list_task, char * ID)
{
	int i = 0;
	int found = 0;
	task * pt = NULL;
	pt = list_task;

	/* On parcourt la liste jusqu'à retourner au début
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

task * annule_tache(task *list_task, char caract[MAX_NOM+1])
{
	task * pt1 = NULL;
	task * pt2 = NULL;
	int pos, i;

	if (list_task == NULL)
		return NULL; //TODO message d'erreur

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

task * execute_tache_FIFO(task *list_task)
{
	task * pt = NULL;

	pt = list_task->psuivant;
	if (pt == list_task)
		return list_task; // message d'erreur

	printf("exécution de la tâche  %s (%d)\n", pt->ID, pt->duree);
	sleep(1);

	list_task->psuivant = pt->psuivant;
	free(pt);

	return list_task;
}

task * execute_tache_LIFO(task *list_task)
{
	task * pt = NULL;
	task * pre = NULL;

	pre = pt = list_task->psuivant;
	if (pt == list_task)
		return list_task; // message d'erreur

	while (pt->psuivant != list_task) {
		pre = pt;
		pt = pt->psuivant;
	}

	printf("exécution de la tâche  %s (%d)\n", pt->ID, pt->duree);
	sleep(1);

	pre->psuivant = list_task;
	free(pt);

	return list_task;
}

task * insere_tache(task *list_task, task *ptache)
{
	task * pt1 = NULL;
	task * pt2 = NULL;

	if (list_task == NULL || ptache == NULL)
		return NULL;

	pt1 = list_task;
	pt2 = list_task->psuivant;

	while (pt2->duree < ptache->duree && pt2 != list_task) {
		pt1 = pt2;
		pt2 = pt2->psuivant;
	}

	pt1->psuivant = ptache;
	ptache->psuivant = pt2;

	return list_task;
}

task * load_data(char * nom_fichier)
{

}
