#ifndef TP3
#define TP3

#define MAX_NOM 20         //Taille maximale des ID.


typedef struct task
{
	char ID[MAX_NOM+1];    //Identifiant (nom) unique de la tâche.
	int duree;			   //Durée de la tâche (en période processeur).
	struct task *psuivant; //Pointeur à la tâche suivante.
}task;


/* Crée une nouvelle tache.
 * caract : l'id de la tache.
 * duree : la durée de la tache.
 * Retourne un pointeur sur la tache créée.
 */
task * cree_tache(char caract[MAX_NOM+1], int duree);

/* Crée une liste avec la tache donnée.
 * tache : la première tache de la liste à créer.
 * Retourne un pointeur sur la liste créée.
 */
task * cree_liste(task *tache);

/* Affiche la liste donnée.
 * list_task : la liste à afficher.
 */
void affiche_liste(task *list_task);

/* Ajoute une tache à la fin d'une liste.
 * list_task : la liste à laquelle ajouter la tache.
 * ptache : la tache à ajouter.
 * Retourne 0 en cas d'échec, 1 sinon.
 */
int ajoute_tache(task *list_task, task *ptache);

/* Cherche la position d'une tache dans la liste.
 * list_task : la liste de taches.
 * ID : l'identifiant de la tache recherchée.
 * Retourne la position de la tache, -1 si la tache n'existe pas.
 */
int search_ID(task * list_task, char * ID);

/* Annule une tache.
 * list_task : la liste d'où retirer la tache.
 * caract : l'identifiant de la tache à annuler.
 * Retourne un pointeur vers la liste de tache.
 */
task * annule_tache(task *list_task, char caract[MAX_NOM+1]);

/* Vide la liste donnée.
 * list_task : la liste a vider.
 * Retourne un pointeur vers la liste vide.
 */
task * libere_liste(task *list_task);

task * execute_tache_FIFO(task *list_task);

task * execute_tache_LIFO(task *list_task);

task * insere_tache(task *list_task, task *ptache);

task * load_data(char * nom_fichier);
#endif