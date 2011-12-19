#ifndef PILE
#define PILE

#include "arbre.h"

/* Nom: NF16 - TP05
 * Sujet: Arbres et calcul formel
 * Auteurs: Akim Sadaoui et Antoine Hars
 * Section: GI01
 */

typedef struct pile {
    Node * node;           // pointeur vers un node de la pile
    struct pile * next;    // le node suivant dans la pile
} pile;


/* Crée une nouvelle pile vide.
 * Retourne un pointeur vers la pile.
 */
pile * create_pile();

/* Libère la pile de la mémoire.
 * p : la pile à supprimer.
 */
void destroy(pile * p);

/* Donne la taille actuelle de la pile.
 * p : La pile à mesurer.
 * Retourne le nombre de node dans la pile.
 */
int size(pile * p);

/* Ajoute un node dans la pile.
 * node : le node à ajouter.
 * p : la pile à remplir.
 * Retourne 1 si une erreur apparait, 0 sinon.
 */
int empiler(Node * node, pile * p);

/* Récupère le node en tête de la pile.
 * p : la pile à lire.
 * Retourne le premier node de la pile.
 */
Node * depiler(pile * p);

#endif
