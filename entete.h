#ifndef ENTETE_H
#define ENTETE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_NOM 4


typedef struct task
{
	char ID[MAX_NOM+1];			//Nom de la tache
	int duree;					//Durée de la tâche (en période processeur)
	int priorite;				//priorite
	struct task *psuivant;				//Pointeur à la suivante
}task;


task * cree_tache(char caract[MAX_NOM+1], int duree);

task * cree_liste(task *tache);

void affiche_liste(task *list_task);

int ajoute_tache(task *list_task, task *ptache);

task * annule_tache(task *list_task, char caract[MAX_NOM+1]);

//int execute_tache_FIFO(task **list_task);

task * execute_tache_FIFO(task *list_task);

task * depile_tache(task *list_task);

task * depile_tache2(task **list_task);

task * execute_tache_LIFO(task *list_task);

task * load_data(char * nom_fichier);

task * load_data2(char * nom_fichier);

task * load_data_exemple_fm(char * nom_fichier);

task * load_data_exemple_fm2(char * nom_fichier);

task * insere_tache(task *list_task, task *ptache);

task * insere_tache_priorite(task *list_task, task *ptache);

task * fusion_listes(task *list_task1, task *list_task2);

int MAJ_priorite(task *list_task);

#endif
