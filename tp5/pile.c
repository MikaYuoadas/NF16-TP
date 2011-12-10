#include <stdlib.h>

#include "pile.h"


pile * create_pile()
{
    pile * p;

    p = malloc(sizeof(pile));
    p->node = NULL;
    p->next = NULL;

    return p;
}


void destroy(pile * p)
{
    pile * next;

    while (p != NULL) {
        next = p->next;
        free(p);
        p = next;
    }
}


int empiler(Node * node, pile * p)
{
    pile *head, *newNode;

    head = p->next;
    newNode = malloc(sizeof(pile));
    if (newNode == NULL)
        return 1;

    p->next = newNode;
    newNode->next = head;
    newNode->node = node;

    return 0;
}


Node * depiler(pile * p)
{
    pile * ret;

    if (p == NULL || p->next == NULL)
        return NULL;

    ret = p->next;
    p->next = p->next->next;

    return ret->node;
}


int size(pile * p)
{
    int nb = -1;

    while (p != NULL) {
        p = p->next;
        nb++;
    }

    return nb;
}
