#ifndef TP3
#define TP3

/* Nom: NF16 - TP03
 * Sujet: Listes cha�n�es.
 * Auteurs: Akim Sadaoui et Antoine Hars
 * Section: GI01
 */

#define MAX_NOM 20      	// Taille maximale des ID.
#define MAX_LIST 5			// Taille maximale des listes.

typedef struct task
{
	char ID[MAX_NOM+1];    // Identifiant (nom) unique de la t�che.
	int duree;			   // Dur�e de la t�che (en p�riode processeur).
	int priorite;		   // Priorit� de la t�che.
	struct task *psuivant; // Pointeur de la t�che suivante.
} task;


/* Cr�e une nouvelle t�che.
 * caract : l'id de la t�che.
 * duree : la dur�e de la t�che.
 * Retourne un pointeur sur la t�che cr��e.
 */
task * cree_tache(char caract[MAX_NOM+1], int duree);

/* Cr�e une liste de t�ches avec la t�che donn�e.
 * tache : la premi�re t�che de la liste � cr�er.
 * Retourne un pointeur sur la liste cr��e.
 */
task * cree_liste(task *tache);

/* Affiche la liste donn�e.
 * list_task : la liste de t�ches � afficher.
 */
void affiche_liste(task *list_task);

/* Ajoute une t�che � la fin d'une liste.
 * list_task : la liste � laquelle on ajoute la t�che.
 * ptache : la t�che � ajouter.
 * Retourne 0 en cas d'�chec, 1 sinon.
 */
int ajoute_tache(task *list_task, task *ptache);

/* Cherche la position d'une t�che dans la liste de t�ches.
 * list_task : la liste de t�ches.
 * ID : l'identifiant de la t�che recherch�e.
 * Retourne la position de la t�che, -1 si la t�che n'existe pas.
 */
int search_ID(task * list_task, char * ID);

/* Annule une t�che.
 * list_task : la liste de t�ches d'o� retirer la t�che.
 * caract : l'identifiant de la t�che � annuler.
 * Retourne un pointeur vers la liste de t�ches.
 */
task * annule_tache(task *list_task, char caract[MAX_NOM+1]);

/* Vide la liste donn�e.
 * list_task : la liste � vider.
 * Retourne un pointeur vers la liste vide.
 */
task * libere_liste(task *list_task);

/* Ex�cute la t�che de la liste arriv�e en premier.
 * list_track : la liste de t�ches � ex�cuter.
 * Retourne la liste de t�ches sans la t�che ex�cut�e.
 */
task * execute_tache_FIFO(task *list_task);

/* Ex�cute la t�che de la liste arriv�e en dernier.
 * list_task : la liste de t�ches � ex�cuter.
 * Retourne la liste de t�ches sans la t�che ex�cut�e.
 */
task * execute_tache_LIFO(task *list_task);

/* Ins�re une t�che dans la liste de t�ches � ex�cuter en respectant
 * un ordre croissant de la dur�e des t�ches de la liste.
 * list_task : la liste de t�ches.
 * ptache : la t�che � ins�rer dans la liste.
 * Retourne la liste de t�ches.
 */
task * insere_tache(task *list_task, task *ptache);

/* Charge les t�ches du fichier texte dans la liste de t�ches.
 * nom_fichier : fichier texte contenant les t�ches � ex�cuter.
 * nb_taches : le nombre de t�ches � charger.
 * Retourne la liste de t�ches.
 */
task * load_data(char * nom_fichier, int nb_taches);

/* Fusionne 2 listes de t�ches en fonction de leur dur�es dans la premi�re liste.
 * list_task1 : la premi�re liste de t�ches.
 * list_task2 : la seconde liste de t�ches.
 * Retourne la liste fusionn�e.
 */
task * fusion_listes(task *list_task1, task *list_task2);

task * insere_tache_priorite(task *list_task, task *ptache);

int MAJ_priorite(task *list_task);

#endif
