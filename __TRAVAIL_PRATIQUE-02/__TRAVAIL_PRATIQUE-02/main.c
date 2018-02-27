/*===============================================================================================*/
/* 											INF145 - TP2										 */
/*===============================================================================================*/

/**************************************************************************************************
Titre				:	Travail pratique numero 2
Auteur				:	Christophe Lamarche 
						&
						Frederic Thibault
Date de creation	:	05/02/2018
Dernier modification:	26/02/2018

Description			:
Ce programme 
Librairie necessaire:	
**************************************************************************************************/


/*===============================================================================================*/
/*
	Ce programme repond aux exigences du travail pratique numero
	2 pour le cours de INF145 - Programmation avance et langage
	C.
*/
/*===============================================================================================*/

//Permet de désactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 

/*===============================================================================================*/
/*											LIBRAIRIES											 */
/*===============================================================================================*/

// Librairies usuelles à inclure 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<limits.h>
#include<string.h>

// Librairies supplémentaire à inclure
#include "m_decoupage.h"
#include "m_regroupement.h"

/*===============================================================================================*/
/*									DÉFINITION DES CONSTANTES			                         */
/*===============================================================================================*/
#define TAILLE_T_BLOC	4000
//Permet de naviger dans les mandats selon les tests désirés
#define NBR_FICHIER		2
#define MANDAT			1
//---> La  valeur 0 correspond au main de test
/*===============================================================================================*/
/*									DÉFINITION DES MACROS						                 */
/*===============================================================================================*/

/*************************************************************************************************/

/*===============================================================================================*/
/*											AIDE-MEMOIRE 					                     */
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

/*===============================================================================================*/
/*									DÉCLARATION DES SOUS-PROGRAMMES				                 */
/*===============================================================================================*/
/*=================================================================================================
TITRE : prog_decoup
codee par Christophe Lamarche

Cette fonction ...

Parametres :
Hypotheses :
Valeur de retour :

Exemples d'appel :
=================================================================================================*/
void proc_decoup(int * taille_octet, t_block * bloc);
/*=================================================================================================
TITRE : init_bloc
codee par Christophe Lamarche

Cette fonction ...

Parametres :
Hypotheses :
Valeur de retour :

Exemples d'appel :
=================================================================================================*/
void init_bloc(const char * nom, t_block * bloc, t_block * tab_bloc, t_block* *ptr);
/*=================================================================================================
TITRE : transf_bloc
codee par Christophe Lamarche

Cette fonction ...

Parametres :
Hypotheses :
Valeur de retour :

Exemples d'appel :
=================================================================================================*/
void transf_bloc(t_block *bloc, t_block *ptr);

/*-----------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------*/

/*===============================================================================================*/
/*											MANDAT 1 - 1 FICHIER								 */
/*===============================================================================================*/
//Programme principal: fonction qui retourne un entier (int)
#if(MANDAT == 1 && NBR_FICHIER == 1)
int main(void)
{
	int				reussite = 0;
	int				somme_octet1 = 0;
	t_block			tab_bloc1[TAILLE_T_BLOC]; //Va devenir la pile -- Tableau dynamique
	t_block			un_bloc;
	t_block			*ptr = NULL; // pointeur du tableau

	init_decoupage(); // commande d'initiation

	init_bloc("affiche.jpg", &un_bloc, tab_bloc1, &ptr);
	print_bloc(&un_bloc);

	if (id_fichier_valide(un_bloc.f_identifiant))
	{
		do 
		{

			proc_decoup(&somme_octet1, &un_bloc);
			transf_bloc(&un_bloc, ptr);
			
			ptr++;
		} while (get_taille_restante(un_bloc.f_identifiant) != 0);
	}

	
	//	print_bloc(&tab_bloc1[13]); // TEST DE BLOC DANS LE TABLEAU
	// on termine avec le standard... "APPUYEZ UNE TOUCHE.."
	printf("\n\n");
	system("pause");

	// et ÇA, c'est le retour d'un 0 au système d'exploitation.
	return EXIT_SUCCESS;
}
#endif

/*===============================================================================================*/
/*											MANDAT 1 - 2 FICHIERS								 */	
/*===============================================================================================*/
#if(MANDAT == 1 && NBR_FICHIER == 2)
int main(void)
{
	int				reussite;
	int				taille_octet1 = 0, taille_octet2 = 0; // taille des blocs avant le get_bloc()
	int				compteur = 0;
	t_block			un_bloc, deux_bloc; //bloc recevant le fichier
	t_block			tab_bloc1[TAILLE_T_BLOC] = { 0 }, tab_bloc2[TAILLE_T_BLOC] = { 0 };
	t_block			*ptr_tab1 = NULL, *ptr_tab2 = NULL;

	// Les variables locales y sont déclaré

	init_decoupage();

	init_bloc("affiche.jpg", &un_bloc, tab_bloc1, &ptr_tab1);
	/* ------------ SUBSITITUTION ----------------
	ptr_tab1=tab_bloc1
	un_bloc.f_identifiant = ajouter_fichier("affiche.jpg"); //Reception du fichier
	un_bloc.taille_bloc = get_taille_fichier(un_bloc.f_identifiant); //avoir la taille en octet \
	du fichier
	un_bloc.num_bloc = get_nb_fichiers();
	un_bloc.buffer = &tab_bloc1; //JE SAIS PAS QUOI FAIRE AVEC CE PARAMETRE
	*/
	print_bloc(&un_bloc);

	init_bloc("affiche1.jpg", &deux_bloc, tab_bloc2, &ptr_tab2);
	
	print_bloc(&deux_bloc);
	printf("\nNOMBRE DE FICHIER ACTIF:%i\n", get_nb_fichiers());

	if (id_fichier_valide(un_bloc.f_identifiant))
	{
		do 
		{
			proc_decoup(&taille_octet1, &un_bloc);
			transf_bloc(&un_bloc, ptr_tab1);
			
			ptr_tab1++;
		} while (get_taille_restante(un_bloc.f_identifiant) != 0);
	}

	if (id_fichier_valide(deux_bloc.f_identifiant))
	{
		do
		{
			proc_decoup(&taille_octet2, &deux_bloc);
			transf_bloc(&un_bloc, ptr_tab2);

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
/*											MANDAT 2 - 1 FICHIER								 */	
/*===============================================================================================*/
#if(MANDAT == 2 && NBR_FICHIER == 1)
int main(void)
{
	int				reussite = 0;
	int				somme_octet1 = 0;
	t_block			tab_bloc1[TAILLE_T_BLOC]; //Va devenir la pile -- Tableau dynamique
	t_block			un_bloc;
	t_block			*ptr = NULL; // pointeur du tableau
	t_regroupement	un_reg;

	init_decoupage(); // commande d'initiation

	init_bloc("affiche.jpg", &un_bloc, tab_bloc1, &ptr);
	un_reg = init_regroupement(un_bloc.f_identifiant, un_bloc.taille_bloc);
	print_bloc(&un_bloc);

	if (id_fichier_valide(un_bloc.f_identifiant))
	{
		do 
		{

			proc_decoup(&somme_octet1, &un_bloc);
//			transf_bloc(&un_bloc, ptr);
			reussite = empiler_bloc(&un_reg, un_bloc);
			ptr++;
		} while (get_taille_restante(un_bloc.f_identifiant) != 0);
	}
	
	while (pile_blocs_nombre(&un_reg) != 0) 
	{
		reussite = depiler_bloc(&un_reg, &un_bloc);
		print_bloc(&un_bloc);
	}

	free_pile_blocs(&un_reg);
//	print_bloc(&tab_bloc1[13]); // TEST DE BLOC DANS LE TABLEAU
	// on termine avec le standard... "APPUYEZ UNE TOUCHE.."
	printf("\n\n");
	system("pause");

	// et ÇA, c'est le retour d'un 0 au système d'exploitation.
	return EXIT_SUCCESS;
}
#endif
/*===============================================================================================*/
/*											MANDAT 2 - 2 FICHIERS								 */			
/*===============================================================================================*/
//Utile pour faire des proc_decoups. le 2e main est inactif en ce moment puisque (0)
#if(MANDAT == 2 && NBR_FICHIER == 2)
int main(void)
{
	int				reussite;
	int				taille_octet1 = 0, taille_octet2 = 0; // taille des blocs avant le get_bloc()
	int				compteur = 0;
	t_block			un_bloc,deux_bloc; //bloc recevant le fichier
	t_block			tab_bloc1[TAILLE_T_BLOC] = { 0 }, tab_bloc2[TAILLE_T_BLOC] = { 0 };
	t_block			*ptr_tab1 = NULL, *ptr_tab2 = NULL;
	t_regroupement	un_reg, deux_reg;

	// Les variables locales y sont déclaré

	init_decoupage();

	init_bloc("affiche.jpg", &un_bloc, tab_bloc1, &ptr_tab1);
/* ------------ SUBSITITUTION ----------------
	ptr_tab1=tab_bloc1
	un_bloc.f_identifiant = ajouter_fichier("affiche.jpg"); //Reception du fichier
	un_bloc.taille_bloc = get_taille_fichier(un_bloc.f_identifiant); //avoir la taille en octet \
	du fichier
	un_bloc.num_bloc = get_nb_fichiers();
	un_bloc.buffer = &tab_bloc1; //JE SAIS PAS QUOI FAIRE AVEC CE PARAMETRE
*/
	un_reg = init_regroupement(un_bloc.f_identifiant, un_bloc.taille_bloc);
	print_bloc(&un_bloc);

	init_bloc("affiche1.jpg",&deux_bloc, tab_bloc2, &ptr_tab2);
	deux_reg = init_regroupement(deux_bloc.f_identifiant, deux_bloc.taille_bloc);

	print_bloc(&deux_bloc);
	printf("\nNOMBRE DE FICHIER ACTIF:%i\n",get_nb_fichiers());

	if (id_fichier_valide(un_bloc.f_identifiant))
	{
		do
		{
			proc_decoup(&taille_octet1, &un_bloc);
//			transf_bloc(&un_bloc, ptr);
			reussite = empiler_bloc(&un_reg, un_bloc);

			ptr_tab1++;
		} while (get_taille_restante(un_bloc.f_identifiant) != 0);
	}

	if (id_fichier_valide(deux_bloc.f_identifiant))
	{
		do 
		{
			proc_decoup(&taille_octet2, &deux_bloc);
//			transf_bloc(&un_bloc, ptr);
			reussite = empiler_bloc(&deux_reg, deux_bloc);
			
			ptr_tab2++;
		} while (get_taille_restante(deux_bloc.f_identifiant) != 0);
	}


	while (pile_blocs_nombre(&un_reg) != 0) {
		reussite = depiler_bloc(&un_reg, &un_bloc);
		print_bloc(&un_bloc);
	}

	while (pile_blocs_nombre(&deux_reg) != 0) {
		reussite = depiler_bloc(&deux_reg, &deux_bloc);
		print_bloc(&deux_bloc);
	}

	free_pile_blocs(&un_reg);
	free_pile_blocs(&deux_reg);
	// on termine avec le standard... "APPUYEZ UNE TOUCHE.."
	printf("\n\n");
	system("pause");

	// et ÇA, c'est le retour d'un 0 au système d'exploitation.
	return EXIT_SUCCESS;
}
#endif
/*===============================================================================================*/
/*											MANDAT 3 - 1 FICHIER								 */	
/*===============================================================================================*/
#if(MANDAT == 3 && NBR_FICHIER == 1)
int main(void)
{
	int				reussite = 0;
	int				somme_octet1 = 0;
	t_block			tab_bloc1[TAILLE_T_BLOC]; //Va devenir la pile -- Tableau dynamique
	t_block			un_bloc;
	t_block			*ptr = NULL; // pointeur du tableau
	t_regroupement	un_reg;

	init_decoupage(); // commande d'initiation

	init_bloc("affiche.jpg", &un_bloc, tab_bloc1, &ptr);
	un_reg = init_regroupement(un_bloc.f_identifiant, un_bloc.taille_bloc);
	print_bloc(&un_bloc);

	if (id_fichier_valide(un_bloc.f_identifiant))
	{
		do 
		{

			proc_decoup(&somme_octet1, &un_bloc);
			//			transf_bloc(&un_bloc, ptr);
			reussite = empiler_bloc(&un_reg, un_bloc);
			ptr++;
		} while (get_taille_restante(un_bloc.f_identifiant) != 0);
	}

	while (pile_blocs_nombre(&un_reg) != 0) 
	{
		reussite = depiler_bloc(&un_reg, &un_bloc);
		print_bloc(&un_bloc);
	}

	free_pile_blocs(&un_reg);
	//	print_bloc(&tab_bloc1[13]); // TEST DE BLOC DANS LE TABLEAU
	// on termine avec le standard... "APPUYEZ UNE TOUCHE.."
	printf("\n\n");
	system("pause");

	// et ÇA, c'est le retour d'un 0 au système d'exploitation.
	return EXIT_SUCCESS;
}
#endif
/*===============================================================================================*/
/*											MANDAT 3 - 2 FICHIERS								 */
/*===============================================================================================*/
//Utile pour faire des proc_decoups. le 2e main est inactif en ce moment puisque (0)
#if(MANDAT == 3 && NBR_FICHIER == 2)
int main(void)
{
	int				reussite;
	int				taille_octet1 = 0, taille_octet2 = 0; // taille des blocs avant le get_bloc()
	int				compteur = 0;
	t_block			un_bloc, deux_bloc; //bloc recevant le fichier
	t_block			tab_bloc1[TAILLE_T_BLOC] = { 0 }, tab_bloc2[TAILLE_T_BLOC] = { 0 };
	t_block			*ptr_tab1 = NULL, *ptr_tab2 = NULL;
	t_regroupement	un_reg, deux_reg;

	// Les variables locales y sont déclaré

	init_decoupage();

	init_bloc("affiche.jpg", &un_bloc, tab_bloc1, &ptr_tab1);
	/* ------------ SUBSITITUTION ----------------
	ptr_tab1=tab_bloc1
	un_bloc.f_identifiant = ajouter_fichier("affiche.jpg"); //Reception du fichier
	un_bloc.taille_bloc = get_taille_fichier(un_bloc.f_identifiant); //avoir la taille en octet \
	du fichier
	un_bloc.num_bloc = get_nb_fichiers();
	un_bloc.buffer = &tab_bloc1; //JE SAIS PAS QUOI FAIRE AVEC CE PARAMETRE
	*/
	un_reg = init_regroupement(un_bloc.f_identifiant, un_bloc.taille_bloc);
	print_bloc(&un_bloc);

	init_bloc("affiche1.jpg", &deux_bloc, tab_bloc2, &ptr_tab2);
	deux_reg = init_regroupement(deux_bloc.f_identifiant, deux_bloc.taille_bloc);

	print_bloc(&deux_bloc);
	printf("\nNOMBRE DE FICHIER ACTIF:%i\n", get_nb_fichiers());

	if (id_fichier_valide(un_bloc.f_identifiant))
	{
		do 
		{
			proc_decoup(&taille_octet1, &un_bloc);
			//			transf_bloc(&un_bloc, ptr);
			reussite = empiler_bloc(&un_reg, un_bloc);

			ptr_tab1++;
		} 
		while (get_taille_restante(un_bloc.f_identifiant) != 0);
	}

	if (id_fichier_valide(deux_bloc.f_identifiant))
	{
		do 
		{
			proc_decoup(&taille_octet2, &deux_bloc);
			//			transf_bloc(&un_bloc, ptr);
			reussite = empiler_bloc(&deux_reg, deux_bloc);

			ptr_tab2++;
		} 
		while (get_taille_restante(deux_bloc.f_identifiant) != 0);
	}


	while (pile_blocs_nombre(&un_reg) != 0) 
	{
		reussite = depiler_bloc(&un_reg, &un_bloc);
		print_bloc(&un_bloc);
	}

	while (pile_blocs_nombre(&deux_reg) != 0) 
	{
		reussite = depiler_bloc(&deux_reg, &deux_bloc);
		print_bloc(&deux_bloc);
	}

	free_pile_blocs(&un_reg);
	free_pile_blocs(&deux_reg);
	// on termine avec le standard... "APPUYEZ UNE TOUCHE.."
	printf("\n\n");
	system("pause");

	// et ÇA, c'est le retour d'un 0 au système d'exploitation.
	return EXIT_SUCCESS;
}
#endif

/*===============================================================================================*/
/*											PROGRAMME PRINCIPAL									 */
/*===============================================================================================*/
#if(NBR_FICHIER == 0) // main de test 
int main(void)
{
	t_regroupement test_reg;
	t_block test_bloc;
	t_block* ptr;
	int taille_octet;
	int reussite;


	init_decoupage();
	init_bloc("affiche.jpg", &test_bloc,NULL, &ptr);
	test_reg = init_regroupement(test_bloc.f_identifiant, test_bloc.taille_bloc);
	
	print_bloc(&test_bloc);

	//affichage de l'etat du regroupement
	printf("\nId fichier  : %u\
			\nNbr bloc    : %u\
			\nAdresse tab : %X\
			\nTaille tab  : %u" 
		, test_reg.id_fichier, test_reg.nbr_bloc, test_reg.ptr_bloc, test_reg.taille_tab);
	
	for (int i = 0; i < 3; i++) 
	{

		proc_decoup(&taille_octet, &test_bloc);
		reussite = empiler_bloc(&test_reg, test_bloc);
		(reussite >= 0) ? printf("\nReussi\n") : printf("\nECHOUER\n");
		printf("\nId fichier  : %u\
			\nNbr bloc    : %u\
			\nAdresse tab : %X\
			\nTaille tab  : %u"
			, test_reg.id_fichier, test_reg.nbr_bloc, test_reg.ptr_bloc, test_reg.taille_tab);
	
	}
	while (pile_blocs_nombre(&test_reg)!= 0) 
	{
		(reussite > 0) ? printf("\nReussi\n") : printf("\nECHOUER\n");
		reussite = depiler_bloc(&test_reg, &test_bloc);
		print_bloc(&test_bloc);
	}

	
	
	

	free_pile_blocs(&test_reg);
	// on termine avec le standard... "APPUYEZ UNE TOUCHE.."
	printf("\n\n");
	system("pause");

	// et ÇA, c'est le retour d'un 0 au système d'exploitation.
	return EXIT_SUCCESS;
}
#endif

/*************************************************************************************************/

/*===============================================================================================*/
/*									DÉFINITION DES SOUS-PROGRAMMES								 */
/*===============================================================================================*/

/*===============================================================================================*/
/*
Titre : proc_decoup
description : 
In : 
Out : 

*/
/*===============================================================================================*/
void proc_decoup(int * taille_octet, t_block *bloc)
{

	// recherche de la taille avant get_bloc()
	*taille_octet = get_taille_restante(bloc->f_identifiant); 
	// On decoupe un bloc et on offre le reste														
	*bloc = get_bloc(); 
	bloc->num_bloc = get_nb_blocs_emis(bloc->f_identifiant);
	// affichage du numero du bloc
	printf("\nBLOC#%u\t(TRANSMIS) ",bloc->num_bloc); 
	// affichage de l'addresse / ID
	printf("\tID:%u", bloc->f_identifiant); 
	//	taille du decoupage
	printf("\tTaille : %i\toctets", \
		(*taille_octet - get_taille_restante(bloc->f_identifiant)));
	// taille restant a decouper
	printf("\tRESTANT : %i\toctets\n", get_taille_restante(bloc->f_identifiant)); 
	return;
}
/*===============================================================================================*/
/*
Titre : trans_bloc
description :
In :
Out :

*/
/*===============================================================================================*/
void transf_bloc(t_block *bloc, t_block *ptr)
{
	*(ptr) = *bloc;
	return;
}
/*===============================================================================================*/
/*
Titre : init_bloc
description :
In :
Out :

*/
/*===============================================================================================*/
void init_bloc(const char * nom_fichier, t_block * bloc, t_block * tab_bloc, t_block* *ptr)
{
	*ptr = tab_bloc;
	//Reception du fichier
	bloc->f_identifiant = ajouter_fichier(nom_fichier);
	//avoir la taille en octet du fichier
	bloc->taille_bloc = get_taille_fichier(bloc->f_identifiant); 
	// nombre de fichier ouvert
	bloc->num_bloc = get_nb_fichiers();
	// met l'addresse de la premiere case du tableau
	bloc->buffer = tab_bloc; 
	return;
}
