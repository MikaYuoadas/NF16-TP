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
	char ID[MAX_NOM+1];    // Identifiant (nom) unique de la tache.
	int duree;			   // Dur�e de la tache (en p�riode processeur).
	int priorite;		   // Priorit� de la tache.
	struct task *psuivant; // Pointeur de la tache suivante.
} task;


/* Cr�e une nouvelle tache.
 * caract : l'id de la tache.
 * duree : la dur�e de la tache.
 * Retourne un pointeur sur la tache cr��e.
 */
task * cree_tache(char caract[MAX_NOM+1], int duree);

/* Cr�e une liste de taches avec la tache donn�e.
 * tache : la premi�re tache de la liste � cr�er.
 * Retourne un pointeur sur la liste cr��e.
 */
task * cree_liste(task *tache);

/* Affiche la liste donn�e.
 * list_task : la liste de taches � afficher.
 */
void affiche_liste(task *list_task);

/* Ajoute une tache � la fin d'une liste.
 * list_task : la liste � laquelle on ajoute la tache.
 * ptache : la tache � ajouter.
 * Retourne 0 en cas d'�chec, 1 sinon.
 */
int ajoute_tache(task *list_task, task *ptache);

/* Cherche la position d'une tache dans la liste de taches.
 * list_task : la liste de taches.
 * ID : l'identifiant de la tache recherch�e.
 * Retourne la position de la tache, -1 si la tache n'existe pas.
 */
int search_ID(task * list_task, char * ID);

/* Annule une tache.
 * list_task : la liste de taches d'o� retirer la tache.
 * caract : l'identifiant de la tache � annuler.
 * Retourne un pointeur vers la liste de taches.
 */
task * annule_tache(task *list_task, char caract[MAX_NOM+1]);

/* Vide la liste donn�e.
 * list_task : la liste � vider.
 * Retourne un pointeur vers la liste vide.
 */
task * libere_liste(task *list_task);

/* Ex�cute la tache de la liste arriv�e en premier.
 * list_track : la liste de taches � ex�cuter.
 * Retourne la liste de taches sans la tache ex�cut�e.
 */
task * execute_tache_FIFO(task *list_task);

/* Ex�cute la tache de la liste arriv�e en dernier.
 * list_task : la liste de taches � ex�cuter.
 * Retourne la liste de taches sans la tache ex�cut�e.
 */
task * execute_tache_LIFO(task *list_task);

/* Ins�re une tache dans la liste de taches � ex�cuter en respectant
 * un ordre croissant de la dur�e des taches de la liste.
 * list_task : la liste de taches.
 * ptache : la tache � ins�rer dans la liste.
 * Retourne la liste de taches.
 */
task * insere_tache(task *list_task, task *ptache);

/* Charge les taches du fichier texte dans la liste de taches.
 * nom_fichier : fichier texte contenant les taches � ex�cuter.
 * nb_taches : le nombre de taches � charger.
 * Retourne la liste de taches.
 */
task * load_data(char * nom_fichier, int nb_taches);

/* Fusionne 2 listes de taches en fonction de leur dur�es dans la premi�re liste.
 * list_task1 : la premi�re liste de taches.
 * list_task2 : la seconde liste de taches.
 * Retourne la liste fusionn�e.
 */
task * fusion_listes(task *list_task1, task *list_task2);

/* Insere une tache en fonction de sa priorit�
 * list_task : la liste des taches
 * ptache : un pointeur vers la tache � ajouter
 * Retourne la liste des taches
 */
task * insere_tache_priorite(task *list_task, task *ptache);

/* Met � jour la priorit� de chaque tache de la liste
 * list_task : la liste des taches
 * Retourne 0 en cas de succe et 1 sinon
 */
int MAJ_priorite(task *list_task);

#endif
