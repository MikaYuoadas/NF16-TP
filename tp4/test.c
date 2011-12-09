#include <stdlib.h>
#include <stdio.h>
//#include <windows.h>
#include <unistd.h>
#include "tp4.h"

/* Nom: NF16 - TP04
 * Sujet: Vérification de programmes.
 * Auteurs: Akim Sadaoui et Antoine Hars
 * Section: GI01
 */


int main() {

	int choix, result;
	task * list1, * list2, * tache;
	
	do {
	
		printf("\n********** Menu **********\n\n"
			   "0 - Quitter.\n"
			   "1 - Fonction cree_tache.\n"
			   "2 - Fonction cree_liste.\n"
			   "3 - Fonction affiche_liste.\n"
			   "4 - Fonction ajoute_tache.\n"
			   "5 - Fonction annule_tache.\n"
			   "6 - Fonction execute_tache_FIFO.\n"
			   "7 - Fonction depile_tache.\n"
			   "8 - Fonction execute_tache_LIFO.\n"
			   "9 - Fonction load_data.\n"
			   "10 - Fonction load_data2.\n"
			   "11 - Fonction insere_tache.\n"
			   "12 - Fonction insere_tache_priorite.\n"
			   "13 - Fonction fusion_listes.\n"
			   "14 - Fonction MAJ_priorite.\n\n"
			   "Choix : ");
		scanf("%d", &choix);
		
		switch(choix) {
	
			/* Quitter. */
			case 0 :
				printf("\n\nfin\n\n");
			
				break;
			
			/* Fonction cree_tache. */
			case 1 :
				printf("Test fonction cree_tache:\n");
				
				printf("Cas 1 : valeurs courantes\n");
				tache = cree_tache("aa",1);
				affiche_liste(tache);
				
				printf("Cas 2 : id vide\n");
				tache = cree_tache("",5);
				affiche_liste(tache);
				
				printf("Cas 2 bis : duree negative\n");
				tache = cree_tache("rr",-6);
				affiche_liste(tache);
				
				printf("Cas 3 : id = NULL\n"
					   "Impossible de créer une tache sans identifiant.\n");
			
				break;
			
			/* Fonction cree_liste. */
			case 2 :
				printf("Test fonction cree_liste:\n");
				
				printf("Cas 1 : tache classique\n");
				tache = cree_tache("gf",30);
				list1 = cree_liste(tache);
				affiche_liste(list1);
				
				printf("Cas 2 : Tache vide\n");
				list1 = cree_liste(NULL);
				affiche_liste(list1);
				
				printf("Cas 3 : valeur aberrante pour la tache\n");
				list1 = cree_liste("ab");
				affiche_liste(list1);
			
				break;
			
			/* Fonction affiche_liste. */
			case 3 :
				printf("Test fonction affiche_liste:\n");
				
				printf("Cas 1 : valeurs courantes\n");
				tache = cree_tache("ab",10);
				list1 = cree_liste(tache);
				affiche_liste(list1);
				
				printf("Cas 2 : liste avec une tache null\n");
				tache = NULL;
				list1 = creer_liste(tache);
				affiche_liste(list1);
				
				printf("Cas 3 : liste null\n");
				list1 = NULL;
				affiche_liste(list1);
			
				break;
			
			/* Fonction ajoute_tache. */
			case 4 :
				printf("Test fonction ajoute_tache:\n");
				
				printf("Cas 1 : ajout classique d'une tache a une liste\n");
				tache = cree_tache("ab",10);
				list1 = cree_liste(tache);
				tache = cree_tache("cd",20);
				result = ajoute_tache(list1, tache);
				printf("resultat : %d \n",result);
				
				printf("Cas 2 : liste null \n");
				result = ajoute_tache(NULL,tache);
				printf("resultat : %d \n",result);

				printf("Cas 3 : tache null \n");
				result = ajoute_tache(list1,NULL);
				printf("resultat : %d \n",result);

				printf("cas 4 : valeur aberrante pour la tache\n");
				result = ajoute_tache(list1,"cd");
				printf("resultat : %d \n",result);
			
				break;
			/* Fonction annule_tache. */
			case 5 :
				printf("Test fonction annule_tache:\n");
				
				printf("Cas 1 : valeurs courantes\n");
				list1 = cree_liste(cree_tache("aa",2));
				list1 = ajoute_tache(list1, cree_tache("bb",5));
				list1 = annule_tache(list1, "bb");
				affiche_liste(list1);
				
				printf("Cas 2 : tache non comprise dans la liste\n");
				list1 = cree_liste(cree_tache("aa",2));
				list1 = ajoute_tache(list1, cree_tache("bb",5));
				list1 = annule_tache(list1, "ff");
				affiche_liste(list1);
				
				printf("Cas 3 : liste NULL\n");
				list1 = NULL;
				list1 = annule_tache(list1, "ff");
				affiche_liste(list1);
			
				break;
			/* Fonction execute_tache_FIFO. */
			case 6 :
				printf("Test fonction execute_tache_FIFO:\n");
				
		        printf("Cas 1 : normal \n");
		        list1 = cree_liste(cree_tache("aa" 10));
		        list1 = ajoute_tache(list1, cree_tache("bb", 2));
		        list1 = ajoute_tache(list1, cree_tache("cc", 65));
		        list1 = execute_tache_FIFO(list1);
		        affiche_liste(list1);
		        
		        printf("Cas 2 : La liste est vide\n");
		        list1 = NULL;
		        list1 = execute_tache_FIFO(NULL);
				affiche_liste(list1);
				
				break;
			/* Fonction depile_tache. */
			case 7 :
				printf("Test fonction depil_tache:\n");
				
				printf("Cas 1 : liste non vide\n");
				list1 = cree_liste(cree_tache("aa" 10));
		        list1 = ajoute_tache(list1, cree_tache("bb", 2));
		        list1 = depile_tache(list1);
		        affiche_liste(list1);
		        
		        printf("Cas 1 bis : liste à une tache\n");
				list1 = cree_liste(cree_tache("aa" 10));
				list1 = depile_tache(list1);
		        affiche_liste(list1);
				
				printf("Cas 2 : liste vide\n");
				list1 = cree_liste(NULL);
				list1 = depile_tache(list1);
				affiche_liste(list1);
				
				break;
			/* Fonction execute_tache_LIFO. */
			case 8 :
				printf("Test fonction execute_tache_LIFO:\n");
				
		        printf("Cas 1 : normal \n");
		        list1 = cree_liste(cree_tache("aa" 10));
		        list1 = ajoute_tache(list1, cree_tache("bb", 2));
		        list1 = ajoute_tache(list1, cree_tache("cc", 65));
		        list1 = execute_tache_LIFO(list1);
		        affiche_liste(list1);
		        
		        printf("Cas 2 : La liste est vide\n");
		        list1 = NULL;
		        list1 = execute_tache_LIFO(NULL);
		        affiche_liste(list1);
			
				break;
			/* Fonction load_data. */
			case 9 :
				printf("Test fonction load_data:\n");
				
				printf("Cas 1 : nom de fichier correct\n");
				list1 = load_data("tasks.dat");
				affiche_liste(list1);

				printf("Cas 2 : nom de fichier sans extension\n");
				list1 = load_data("tasks");
				affiche_liste(list1);

				printf("Cas 3 : Fichier null \n");
				list1 = load_data(NULL);
				affiche_liste(list1);
			
				printf("Cas 4 : valeur aberrante du nom de fichier\n"
					   "la fonction s'interrompt lors de son exécution.\n");
				break;
			/* Fonction load_data2. */
			case 10 :
				printf("Test fonction load_data2:\n");
				
				printf("Cas 1 : nom de fichier correct\n");
				list1 = load_data2("tasks.dat");
				affiche_liste(list1);

				printf("Cas 2 : nom de fichier sans extension\n");
				list1 = load_data2("tasks");
				affiche_liste(list1);

				printf("Cas 3 : Fichier null \n");
				list1 = load_data2(NULL);
				affiche_liste(list1);
			
				printf("Cas 4 : valeur aberrante du nom de fichier\n"
					   "la fonction s'interrompt lors de son exécution.\n");
					   
				break;
			/* Fonction insere_tache. */
			case 11 :
				printf("Test fonction insere_tache:\n");
				
				printf("Cas 1 : liste et tache classique\n");
				tache = cree_tache("de",30);
				list1 = cree_tache("ab", 10);
				list1 = cree_liste(list1);
				list1 = insere_tache(list1, tache);
				tache = cree_tache("ab", 50);
				list1 = insere_tache(list_tache, t2);
				affiche_list1(list1);
				
				printf("Cas 2 : liste vide\n"
					   "Arret de la fonction.\n");
					   
				printf("Cas 2 bis : tache vide\n"
					   "Arret de la fonction.\n");
				
				printf("Cas 3 : valeur aberrante\n"
					   "Arret de la fonction.\n");
			
				break;
			/* Fonction insere_tache_priorite. */
			case 12 :
				printf("Test fonction insere_tache_priorite:\n");
				
				printf("Cas 1 : valeurs courantes\n");
				list1 = cree_liste(cree_tache("yy", 18));
				list1 = insere_tache_priorite(list1, cree_tache("xx", 7));
				list1 = insere_tache_priorite(list1, cree_tache("rr", 1));
				affiche_liste(list1);
				
				printf("Cas 2 : liste null\n");
				list1 = NULL;
				list1 = insere_tache_priorite(list1, cree_tache("vv", 76));
				affiche_liste(list1);
				
				printf("Cas 2 bis : tache null\n");
				list1 = cree_liste(cree_tache("gg", 8));
				list1 = insere_tache_priorite(list1, NULL);
				affiche_liste(list1);
				
				printf("Cas 3 : liste null et tache null\n");
				list1 = NULL;
				list1 = insere_tache_priorite(list1, NULL);
				affiche_liste(list1);
			
				break;
			/* Fonction fusion_listes. */
			case 13 :
				printf("Test fonction fusion_listes:\n");
				
				printf("Cas 1 : 2 listes classiques\n");
				tache = cree_tache("ab", 10);
				list1 = cree_liste(tache);
				list1 = insere_tache(list1, cree_tache("aa", 4));
				list1 = insere_tache(list1, cree_tache("zz", 1));
				printf("\nListe 1 :\n");
				affiche_liste(list1);

				tache = cree_tache("ee", 7);
				list2 = cree_liste(tache);
				list2 = insere_tache(list2, cree_tache("rr", 25));
				list2 = insere_tache(list2, cree_tache("tt", 8));
				printf("\nListe 2 :\n");
				affiche_liste(l2);

				list1 = fusion_listes(list1, list2);
				printf("\nListe fusionnée:\n");
				affiche_liste(list1);
				
				printf("Cas 2 : l'un des 2 liste est vide\n");
				list1 = cree_liste(cree_tache("yy", 18));
				list1 = insere_tache(list1, cree_tache("uu", 6));
				list1 = insere_tache(list1, cree_tache("ii", 12));
				affiche_liste(list1);
				list1 = fusion_listes(NULL,list1);
				affiche_liste(list1);

				printf("Cas 3 : deux listes vides\n");
				list1 = fusion_listes(NULL,NULL);
				affiche_liste(list1);
			
				break;
			/* Fonction MAJ_priorite. */
			case 14 :
				printf("Test fonction MAJ_priorite:\n");
				
				printf("Cas 1 : liste non vide\n");
				list1 = cree_liste(cree_tache("yy", 18));
				list1 = insere_tache(list1, cree_tache("uu", 6));
				list1 = insere_tache(list1, cree_tache("ii", 12));
				result = MAJ_priorite(list1);
				printf("Resultat : %d\n", result);
				
				printf("Cas 2 : liste vide\n");
				list1 = NULL;
				result = MAJ_priorite(list1);
				printf("Resultat : %d\n", result);
				
				break;

		}
	

	} while (choix != 0);

	return 0;
}
