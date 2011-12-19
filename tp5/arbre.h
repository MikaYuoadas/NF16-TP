#ifndef ARBRE
#define ARBRE

#define LEN 100

/* Nom: NF16 - TP05
 * Sujet: Arbres et calcul formel
 * Auteurs: Akim Sadaoui et Antoine Hars
 * Section: GI01
 */

typedef struct Node {
    struct Node * left;     // fils gauche
    struct Node * right;    // fils droit
    char name;              // nom de l'opérateur
    double value;           // valeur de la constante
} Node;


/* Crée un nouveau node.
 * val : un string représentant la valeur du node.
 * left : le fils gauche du node.
 * right : le fils droit du node:
 * Retourne le node créé.
 */
Node * create_node(char * val, Node *left, Node *right);

/* Détruis le node et tous les fils récursivement.
 * node : un pointeur vers le sous-arbre.
 */
void destroy_all(Node * node);

/* Copie le contenu du node src dans le node dest.
 * src : un pointeur vers le node à copier.
 * dest : un pointeur vers le node vers lequel copier.
 */
void copy(Node * src, Node * dest);

/* Lis une expression et crée l'arbre correspondant.
 * Retourne le node père de l'arbre créé.
 */
Node * saisie_expression();

/* Affiche l'expression en mode préfixé.
 * node : un pointeur vers l'arbre à afficher.
 */
void pre_ordre(Node * node);

/* Affiche l'expression en mode infixé.
 * node : un pointeur vers l'arbre à afficher.
 */
void in_ordre(Node * node);

/* Affiche l'expression en mode postfixé.
 * node : un pointeur vers l'arbre à afficher.
 */
void post_ordre(Node * node);

/* Affiche l'expression formaté en respectant la priorité des opérations.
 * node : un pointeur vers l'arbre à afficher.
 */
void affiche_expression(Node * node);

/* Duplique un arbre.
 * node : l'arbre à dupliquer.
 * Retourne un pointeur vers la copie de l'arbre.
 */
Node * clone(Node * node);

/* Réduit la hauteur de l'arbre de 1 si possible en effectuant les calculs aux feuilles.
 * node : l'arbre à réduire.
 */
void calcul_intermediaire(Node * node);

/* Réduit la hauteur de l'arbre au minimum possible.
 * node : l'arbre à réduire.
 */
void calcul(Node * node);

/* Développe tous les produits dans l'expression.
 * node : l'arbre à développer.
 */
void developpement(Node * node);

#endif
