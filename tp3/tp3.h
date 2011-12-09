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
	char ID[MAX_NOM+1];    // Identifiant (nom) unique de la tache.
	int duree;			   // Durée de la tache (en période processeur).
	int priorite;		   // Priorité de la tache.
	struct task *psuivant; // Pointeur de la tache suivante.
} task;


/* Crée une nouvelle tache.
 * caract : l'id de la tache.
 * duree : la durée de la tache.
 * Retourne un pointeur sur la tache créée.
 */
task * cree_tache(char caract[MAX_NOM+1], int duree);

/* Crée une liste de taches avec la tache donnée.
 * tache : la première tache de la liste à créer.
 * Retourne un pointeur sur la liste créée.
 */
task * cree_liste(task *tache);

/* Affiche la liste donnée.
 * list_task : la liste de taches à afficher.
 */
void affiche_liste(task *list_task);

/* Ajoute une tache à la fin d'une liste.
 * list_task : la liste à laquelle on ajoute la tache.
 * ptache : la tache à ajouter.
 * Retourne 0 en cas d'échec, 1 sinon.
 */
int ajoute_tache(task *list_task, task *ptache);

/* Cherche la position d'une tache dans la liste de taches.
 * list_task : la liste de taches.
 * ID : l'identifiant de la tache recherchée.
 * Retourne la position de la tache, -1 si la tache n'existe pas.
 */
int search_ID(task * list_task, char * ID);

/* Annule une tache.
 * list_task : la liste de taches d'où retirer la tache.
 * caract : l'identifiant de la tache à annuler.
 * Retourne un pointeur vers la liste de taches.
 */
task * annule_tache(task *list_task, char caract[MAX_NOM+1]);

/* Vide la liste donnée.
 * list_task : la liste à vider.
 * Retourne un pointeur vers la liste vide.
 */
task * libere_liste(task *list_task);

/* Exécute la tache de la liste arrivée en premier.
 * list_track : la liste de taches à exécuter.
 * Retourne la liste de taches sans la tache exécutée.
 */
task * execute_tache_FIFO(task *list_task);

/* Exécute la tache de la liste arrivée en dernier.
 * list_task : la liste de taches à exécuter.
 * Retourne la liste de taches sans la tache exécutée.
 */
task * execute_tache_LIFO(task *list_task);

/* Insère une tache dans la liste de taches à exécuter en respectant
 * un ordre croissant de la durée des taches de la liste.
 * list_task : la liste de taches.
 * ptache : la tache à insérer dans la liste.
 * Retourne la liste de taches.
 */
task * insere_tache(task *list_task, task *ptache);

/* Charge les taches du fichier texte dans la liste de taches.
 * nom_fichier : fichier texte contenant les taches à exécuter.
 * nb_taches : le nombre de taches à charger.
 * Retourne la liste de taches.
 */
task * load_data(char * nom_fichier, int nb_taches);

/* Fusionne 2 listes de taches en fonction de leur durées dans la première liste.
 * list_task1 : la première liste de taches.
 * list_task2 : la seconde liste de taches.
 * Retourne la liste fusionnée.
 */
task * fusion_listes(task *list_task1, task *list_task2);

/* Insere une tache en fonction de sa priorité
 * list_task : la liste des taches
 * ptache : un pointeur vers la tache à ajouter
 * Retourne la liste des taches
 */
task * insere_tache_priorite(task *list_task, task *ptache);

/* Met à jour la priorité de chaque tache de la liste
 * list_task : la liste des taches
 * Retourne 0 en cas de succe et 1 sinon
 */
int MAJ_priorite(task *list_task);

#endif
