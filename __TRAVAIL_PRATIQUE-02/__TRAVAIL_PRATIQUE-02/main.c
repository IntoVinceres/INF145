/*===============================================================================================*/
/* 											INF145 - TP2										 */
/*===============================================================================================*/

/**************************************************************************************************
Titre				:	Travail pratique numero 2
Auteur				:	Christophe Lamarche 
						&
						Frederic Thibault
Date de creation	:	05/02/2018
Dernier modification:	23/02/2018

Description			:
Ce programme 
Librairie necessaire:	
***************************************************************************************************/


/*===============================================================================================*/
/*
Ce programme repond aux exigences du travail pratique numero
2 pour le cours de INF145 - Programmation avance et langage
C.
*/
/*===============================================================================================*/

//Permet de désactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 

// Librairies usuelles à inclure 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<limits.h>
#include<string.h>

#include "m_decoupage.h"
#include "m_regroupement.h"
/*===============================================================================================*/
/*										  LES CONSTANTES							             */
/*===============================================================================================*/
#define TAILLE_T_BLOC	4000
#define NBR_FICHIER		1
/*===============================================================================================*/
/*										   LES MACROS								             */
/*===============================================================================================*/

/*************************************************************************************************/

/*===============================================================================================*/
/*										  LES FONCTIONS								             */
/*===============================================================================================*/
/*=================================================================================================
TITRE : 
codee par Christophe Lamarche

Cette fonction ...

Parametres : 
Hypotheses : 
Valeur de retour : 

Exemples d'appel :
=================================================================================================*/

/*===============================================================================================*/
/*===============================================================================================*/
/*===============================================================================================*/

/*	Structure du typedef t_bloc // AIDE-MEMOIRE
typedef struct {

	unsigned int f_identifiant; //identifiant unique du fichier

	unsigned int num_bloc;      //numéro de ce bloc dans l'énumération des blocs

	unsigned int taille_bloc;   //nombre d'octets extraits du fichier dans ce bloc

	unsigned char * buffer;     //l'adresse du tableau dynamique contenant le bloc

	unsigned char bloc_final;   //1 si c'est le dernier bloc du découpage, 0 sinon

}t_block;
*/ //  PUBLIC
void proc_decoup(int * taille_octet, t_block * bloc);
void init_bloc(const char * nom, t_block * bloc, t_block * tab_bloc[TAILLE_T_BLOC]);
void transf_bloc(t_block *bloc, t_block *ptr);

/*===============================================================================================*/
/*				    Programme principal: fonction qui retourne un entier (int)					 */
/*===============================================================================================*/
#if(NBR_FICHIER == 1)
int main(void)
{

	int				somme_octet1 = 0;
	t_block			tab_bloc1[TAILLE_T_BLOC]; //JE SAIS PAS CA SERT A QUOI 
	t_block			un_bloc;
	t_block			*ptr = NULL;

	ptr = tab_bloc1;

	init_decoupage(); // commande d'initiation

	init_bloc("affiche1.jpg", &un_bloc, &tab_bloc1);
	
	print_bloc(&un_bloc);

	if (id_fichier_valide(un_bloc.f_identifiant))
	{
		do {

			proc_decoup(&somme_octet1, &un_bloc);
			transf_bloc(&un_bloc, ptr);

			ptr++;
		} while (get_taille_restante(un_bloc.f_identifiant) != 0);
	}
	print_bloc(&tab_bloc1[13]); // TEST DE BLOC DANS LE TABLEAU
	// on termine avec le standard... "APPUYEZ UNE TOUCHE.."
	printf("\n\n");
	system("pause");

	// et ÇA, c'est le retour d'un 0 au système d'exploitation.
	return EXIT_SUCCESS;
}
#endif

/*===============================================================================================*/
/*		 Utile pour faire des proc_decoups. le 2e main est inactif en ce moment puisque (0)  	 */
/*===============================================================================================*/
#if(NBR_FICHIER == 2)
int main(void)
{
	int				taille_octet1 = 0, taille_octet2 = 0; // taille des blocs avant le get_bloc()
	int				compteur = 0;
	t_block			un_bloc,deux_bloc; //bloc recevant le fichier
	t_block			tab_bloc1[TAILLE_T_BLOC] = { 0 }, tab_bloc2[TAILLE_T_BLOC] = { 0 };
	t_block			*ptr_tab1 = NULL, *ptr_tab2 = NULL;
	// Les variables locales y sont déclaré

	init_decoupage();
	init_bloc("affiche.jpg", &un_bloc, &tab_bloc1);
/* ------------ SUBSITITUTION ----------------
	un_bloc.f_identifiant = ajouter_fichier("affiche.jpg"); //Reception du fichier
	un_bloc.taille_bloc = get_taille_fichier(un_bloc.f_identifiant); //avoir la taille en octet du fichier
	un_bloc.num_bloc = get_nb_fichiers();
	un_bloc.buffer = &tab_bloc1; //JE SAIS PAS QUOI FAIRE AVEC CE PARAMETRE
*/
	ptr_tab1 = tab_bloc1;
	print_bloc(&un_bloc);

	init_bloc("affiche1.jpg",&deux_bloc, &tab_bloc2);
	ptr_tab2 = tab_bloc2;

	print_bloc(&deux_bloc);

	printf("\nNOMBRE DE FICHIER ACTIF:%i\n",get_nb_fichiers());

	if (id_fichier_valide(un_bloc.f_identifiant))
	{
		do {
			proc_decoup(&taille_octet1, &un_bloc);
			transf_bloc(&un_bloc, ptr_tab1);

			ptr_tab1++;
		} while (get_taille_restante(un_bloc.f_identifiant) != 0);
	}

	if (id_fichier_valide(deux_bloc.f_identifiant))
	{
		do {
			proc_decoup(&taille_octet2, &deux_bloc);
			transf_bloc(&deux_bloc, ptr_tab2);

			ptr_tab2++;
		} while (get_taille_restante(deux_bloc.f_identifiant) != 0);
	}
	// on termine avec le standard... "APPUYEZ UNE TOUCHE.."
	printf("\n\n");
	system("pause");

	// et ÇA, c'est le retour d'un 0 au système d'exploitation.
	return EXIT_SUCCESS;
}
#endif

/*===============================================================================================*/
/*===============================================================================================*/

#if(NBR_FICHIER == 0) // main de test 
int main(void)
{

	// on termine avec le standard... "APPUYEZ UNE TOUCHE.."
	printf("\n\n");
	system("pause");

	// et ÇA, c'est le retour d'un 0 au système d'exploitation.
	return EXIT_SUCCESS;
}
#endif
/*===============================================================================================*/
/*
Titre : proc_decoup
description : 
In : 
Out : 

*/
/*===============================================================================================*/
/*											PROGRAMME_DECOUPE									 */		
/*===============================================================================================*/
void proc_decoup(int * taille_octet, t_block *bloc) {
	*taille_octet = get_taille_restante(bloc->f_identifiant); // recherche de la taille avant get_bloc()
	*bloc = get_bloc(); // On decoupe un bloc et on offre le reste
	bloc->num_bloc = get_nb_blocs_emis(bloc->f_identifiant);
	printf("BLOC#%u\t(TRANSMIS) ",bloc->num_bloc); // affichage du numero du bloc
	printf("\tID:%u", bloc->f_identifiant); // affichage de l'addresse / ID
	printf("\tTaille : %i\toctets", \
		(*taille_octet - get_taille_restante(bloc->f_identifiant))); //taille du decoupage
	printf("\tRESTANT : %i\toctets\n", get_taille_restante(bloc->f_identifiant)); // taille restant a decouper
	return;
}

/*===============================================================================================*/
/*											TRANSFER BLOC										 */	
/*===============================================================================================*/
void transf_bloc(t_block *bloc, t_block *ptr) {
	*(ptr) = *bloc;
	return;
}

/*===============================================================================================*/
/*											INITIALISATION_BLOC									 */		
/*===============================================================================================*/
void init_bloc(const char * nom_fichier, t_block * bloc, t_block * tab_bloc[TAILLE_T_BLOC]) {
	bloc->f_identifiant = ajouter_fichier(nom_fichier); //Reception du fichier
	bloc->taille_bloc = get_taille_fichier(bloc->f_identifiant); //avoir la taille en octet du fichier
	bloc->num_bloc = get_nb_fichiers(); // nombre de fichier ouvert
	bloc->buffer = tab_bloc; // met l'addresse de la premiere case du tableau
	return;
}
