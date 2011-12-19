#include <stdlib.h>

#include "pile.h"

/* Nom: NF16 - TP05
 * Sujet: Arbres et calcul formel
 * Auteurs: Akim Sadaoui et Antoine Hars
 * Section: GI01
 */



/*********************************************************************/

pile * create_pile()
{
    pile * p;

    /* Création de la pile et de la sentinelle. */
    p = malloc(sizeof(pile));
    if (p != NULL) {
        p->node = NULL;
        p->next = NULL;
    }

    return p;
}

/*********************************************************************/

void destroy(pile * p)
{
    pile * next;

    /* On libère chaque node de la pile un par un. */
    while (p != NULL) {
        next = p->next;
        free(p);
        p = next;
    }
}

/*********************************************************************/

int empiler(Node * node, pile * p)
{
    pile *head, *newNode;

    head = p->next;

    /* Création d'un nouveau conteneur de la pile. */
    newNode = malloc(sizeof(pile));
    if (newNode == NULL)
        return 1;

    /* On insère le nouveau conteneur après la sentinelle et avant
     * la tête de pile et on le fait pointer sur le node donné.
     */
    p->next = newNode;
    newNode->next = head;
    newNode->node = node;

    return 0;
}

/*********************************************************************/

Node * depiler(pile * p)
{
    pile * ret;

    /* Si la pile est vide on retourne NULL. */
    if (p == NULL || p->next == NULL)
        return NULL;

    /* Sinon on enlève la tête et on retourne le node associé. */
    ret = p->next;
    p->next = p->next->next;

    return ret->node;
}

/*********************************************************************/

int size(pile * p)
{
    int nb = -1;

    /* On parcourt la liste jusqu'à la fin et on compte les nodes. */
    while (p != NULL) {
        p = p->next;
        nb++;
    }

    return nb;
}
