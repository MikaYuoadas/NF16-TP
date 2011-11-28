#ifndef TP3
#define TP3

#define MAX_NOM 20         //Taille maximale des ID.


typedef struct task
{
	char ID[MAX_NOM+1];    //Identifiant (nom) unique de la t�che.
	int duree;			   //Dur�e de la t�che (en p�riode processeur).
	struct task *psuivant; //Pointeur � la t�che suivante.
}task;


/* Cr�e une nouvelle tache.
 * caract : l'id de la tache.
 * duree : la dur�e de la tache.
 * Retourne un pointeur sur la tache cr��e.
 */
task * cree_tache(char caract[MAX_NOM+1], int duree);

/* Cr�e une liste avec la tache donn�e.
 * tache : la premi�re tache de la liste � cr�er.
 * Retourne un pointeur sur la liste cr��e.
 */
task * cree_liste(task *tache);

/* Affiche la liste donn�e.
 * list_task : la liste � afficher.
 */
void affiche_liste(task *list_task);

/* Ajoute une tache � la fin d'une liste.
 * list_task : la liste � laquelle ajouter la tache.
 * ptache : la tache � ajouter.
 * Retourne 0 en cas d'�chec, 1 sinon.
 */
int ajoute_tache(task *list_task, task *ptache);

/* Cherche la position d'une tache dans la liste.
 * list_task : la liste de taches.
 * ID : l'identifiant de la tache recherch�e.
 * Retourne la position de la tache, -1 si la tache n'existe pas.
 */
int search_ID(task * list_task, char * ID);

/* Annule une tache.
 * list_task : la liste d'o� retirer la tache.
 * caract : l'identifiant de la tache � annuler.
 * Retourne un pointeur vers la liste de tache.
 */
task * annule_tache(task *list_task, char caract[MAX_NOM+1]);

/* Vide la liste donn�e.
 * list_task : la liste a vider.
 * Retourne un pointeur vers la liste vide.
 */
task * libere_liste(task *list_task);

task * execute_tache_FIFO(task *list_task);

task * execute_tache_LIFO(task *list_task);

task * insere_tache(task *list_task, task *ptache);

task * load_data(char * nom_fichier);
#endif