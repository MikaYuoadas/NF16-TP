#ifndef TP3
#define TP3

/* Nom: NF16 - TP03
 * Sujet: Listes chaînées.
 * Auteurs: Akim Sadaoui et Antoine Hars
 * Section: GI01
 */

#define MAX_NOM 20      	// Taille maximale des ID.
#define MAX_LIST 5			// Taille maximale des listes.

typedef struct task
{
	char ID[MAX_NOM+1];    // Identifiant (nom) unique de la tâche.
	int duree;			   // Durée de la tâche (en période processeur).
	int priorite;		   // Priorité de la tâche.
	struct task *psuivant; // Pointeur de la tâche suivante.
} task;


/* Crée une nouvelle tâche.
 * caract : l'id de la tâche.
 * duree : la durée de la tâche.
 * Retourne un pointeur sur la tâche créée.
 */
task * cree_tache(char caract[MAX_NOM+1], int duree);

/* Crée une liste de tâches avec la tâche donnée.
 * tache : la première tâche de la liste à créer.
 * Retourne un pointeur sur la liste créée.
 */
task * cree_liste(task *tache);

/* Affiche la liste donnée.
 * list_task : la liste de tâches à afficher.
 */
void affiche_liste(task *list_task);

/* Ajoute une tâche à la fin d'une liste.
 * list_task : la liste à laquelle on ajoute la tâche.
 * ptache : la tâche à ajouter.
 * Retourne 0 en cas d'échec, 1 sinon.
 */
int ajoute_tache(task *list_task, task *ptache);

/* Cherche la position d'une tâche dans la liste de tâches.
 * list_task : la liste de tâches.
 * ID : l'identifiant de la tâche recherchée.
 * Retourne la position de la tâche, -1 si la tâche n'existe pas.
 */
int search_ID(task * list_task, char * ID);

/* Annule une tâche.
 * list_task : la liste de tâches d'où retirer la tâche.
 * caract : l'identifiant de la tâche à annuler.
 * Retourne un pointeur vers la liste de tâches.
 */
task * annule_tache(task *list_task, char caract[MAX_NOM+1]);

/* Vide la liste donnée.
 * list_task : la liste à vider.
 * Retourne un pointeur vers la liste vide.
 */
task * libere_liste(task *list_task);

/* Exécute la tâche de la liste arrivée en premier.
 * list_track : la liste de tâches à exécuter.
 * Retourne la liste de tâches sans la tâche exécutée.
 */
task * execute_tache_FIFO(task *list_task);

/* Exécute la tâche de la liste arrivée en dernier.
 * list_task : la liste de tâches à exécuter.
 * Retourne la liste de tâches sans la tâche exécutée.
 */
task * execute_tache_LIFO(task *list_task);

/* Insère une tâche dans la liste de tâches à exécuter en respectant
 * un ordre croissant de la durée des tâches de la liste.
 * list_task : la liste de tâches.
 * ptache : la tâche à insérer dans la liste.
 * Retourne la liste de tâches.
 */
task * insere_tache(task *list_task, task *ptache);

/* Charge les tâches du fichier texte dans la liste de tâches.
 * nom_fichier : fichier texte contenant les tâches à exécuter.
 * nb_taches : le nombre de tâches à charger.
 * Retourne la liste de tâches.
 */
task * load_data(char * nom_fichier, int nb_taches);

/* Fusionne 2 listes de tâches en fonction de leur durées dans la première liste.
 * list_task1 : la première liste de tâches.
 * list_task2 : la seconde liste de tâches.
 * Retourne la liste fusionnée.
 */
task * fusion_listes(task *list_task1, task *list_task2);

task * insere_tache_priorite(task *list_task, task *ptache);

int MAJ_priorite(task *list_task);

#endif
