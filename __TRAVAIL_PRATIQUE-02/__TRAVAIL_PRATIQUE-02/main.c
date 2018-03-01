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
#include "m_reconstruction.h"

/*===============================================================================================*/
/*									DÉFINITION DES CONSTANTES			                         */
/*===============================================================================================*/
#define TAILLE_T_BLOC	4000
#define NBR_FICHIERS		5
//Permet de naviger dans les mandats selon les tests désirés
#define NBR_FICHIER			1
#define MANDAT				0
//---> La  valeur 0 correspond au main de test
#define TAILLE_PILE			30
#define TAILLE_TAB_REC_INI	40
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

void demande_fichier(char * nom_fichier, char * nom_copie);
void reception_fichier(int i, char* nom_fichier1, char* nom_copie1, char* nom_fichier2, \
	char* nom_copie2, char* nom_fichier3, char* nom_copie3);
int alea(int max);
void init_reg_et_rec(const char * nom_fichier, t_regroupement *reg, t_reconstruction *rec);
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

	retirer_fichier(un_bloc.f_identifiant);

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

	retirer_fichier(un_bloc.f_identifiant);
	retirer_fichier(deux_bloc.f_identifiant);
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
	int				reussite = 0, i = 0;
	int				somme_octet1 = 0;
	t_block			tab_bloc1[TAILLE_T_BLOC]; //Va devenir la pile -- Tableau dynamique
	t_block			un_bloc;
	t_block			*ptr = NULL; // pointeur du tableau
	t_regroupement	un_reg;

	init_decoupage(); // commande d'initiation

	init_bloc("affiche.jpg", &un_bloc, tab_bloc1, &ptr);
	un_reg = init_regroupement(un_bloc.f_identifiant, 500/*un_bloc.taille_bloc*/);
	print_bloc(&un_bloc);
	/*
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
	*/
	do {
		if (pile_blocs_pleine(&un_reg) == 0) {

			while (get_taille_restante(un_bloc.f_identifiant) != 0 \
				&& pile_blocs_pleine(&un_reg) == 0)	{

				proc_decoup(&somme_octet1, &un_bloc);
				//			transf_bloc(&un_bloc, ptr);
				reussite = empiler_bloc(&un_reg, un_bloc);

				
			}

		}

		while (pile_blocs_nombre(&un_reg) != 0)
		{
			reussite = depiler_bloc(&un_reg, &un_bloc);
			tab_bloc1[i] = un_bloc;
			i++;
			print_bloc(&un_bloc);
		}

	} while (get_taille_restante(un_bloc.f_identifiant) !=0 );

	retirer_fichier(un_bloc.f_identifiant);





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
	int				somme_octet1 = 0, somme_octet2 = 0; // taille des blocs avant le get_bloc()
	int				compteur = 0,  compteur2 = 0;
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
	un_reg = init_regroupement(un_bloc.f_identifiant, TAILLE_PILE/*un_bloc.taille_bloc*/);
	print_bloc(&un_bloc);

	init_bloc("ELE105_cours_07.pdf", &deux_bloc, tab_bloc2, &ptr_tab2);
	deux_reg = init_regroupement(deux_bloc.f_identifiant, TAILLE_PILE/*deux_bloc.taille_bloc*/);

	print_bloc(&deux_bloc);
	printf("\nNOMBRE DE FICHIER ACTIF:%i\n", get_nb_fichiers());

	/*
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
	*/
	do {
		if (pile_blocs_pleine(&un_reg) == 0) {

			while (get_taille_restante(un_bloc.f_identifiant) != 0 \
				&& pile_blocs_pleine(&un_reg) == 0) {

				proc_decoup(&somme_octet1, &un_bloc);
				//			transf_bloc(&un_bloc, ptr);
				reussite = empiler_bloc(&un_reg, un_bloc);

				
			}

		}

		while (pile_blocs_nombre(&un_reg) != 0)
		{
			reussite = depiler_bloc(&un_reg, &un_bloc);
			tab_bloc1[compteur++] = un_bloc;
			print_bloc(&un_bloc);
		}

	} while (get_taille_restante(un_bloc.f_identifiant) != 0);

	do {
		if (pile_blocs_pleine(&deux_reg) == 0) {

			while (get_taille_restante(deux_bloc.f_identifiant) != 0 \
				&& pile_blocs_pleine(&deux_reg) == 0)	{

				proc_decoup(&somme_octet2, &deux_bloc);
				//			transf_bloc(&un_bloc, ptr);
				reussite = empiler_bloc(&deux_reg, deux_bloc);

				
			}

		}

		while (pile_blocs_nombre(&deux_reg) != 0)
		{
			reussite = depiler_bloc(&deux_reg, &deux_bloc);
			tab_bloc2[compteur2++] = deux_bloc;
			print_bloc(&deux_bloc);
		}

	} while (get_taille_restante(un_bloc.f_identifiant) !=0 );

	retirer_fichier(un_bloc.f_identifiant);
	retirer_fichier(deux_bloc.f_identifiant);
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
	int				 reussite = 0;
	int				 somme_octet1 = 0;
	t_block			 tab_bloc1[TAILLE_T_BLOC]; //Va devenir la pile -- Tableau dynamique
	t_block			 un_bloc;
	t_block			 *ptr = NULL; // pointeur du tableau
	t_regroupement 	 un_reg;
	t_reconstruction un_rec;

	init_decoupage(); // commande d'initiation

	init_bloc("ELE105_cours_07.pdf", &un_bloc, tab_bloc1, &ptr);
	un_reg = init_regroupement(un_bloc.f_identifiant, TAILLE_PILE);
	un_rec = init_reconstruction(un_bloc.f_identifiant, TAILLE_TAB_REC_INI); 
	print_bloc(&un_bloc);

	do {
		if (pile_blocs_pleine(&un_reg) == 0) {

			while (get_taille_restante(un_bloc.f_identifiant) != 0 \
				&& pile_blocs_pleine(&un_reg) == 0) {

				proc_decoup(&somme_octet1, &un_bloc);
				reussite = empiler_bloc(&un_reg, un_bloc);

				
			}

		}
		
		ajouter_pile_blocs(&un_rec, &un_reg);

	} while (get_taille_restante(un_bloc.f_identifiant) != 0);

	for (int i = 0; i < un_rec.nbr_bloc_actu ; i++) {
		print_bloc(un_rec.ptr_bloc + i);
	}

	reconstruire_fich(&un_rec, "poster2.pdf");

	retirer_fichier(un_bloc.f_identifiant);
	free_pile_blocs(&un_reg);
	free_rec_tab(&un_reg);
	//	print_bloc(&tab_bloc1[13]); // TEST DE BLOC DANS LE TABLEAU
	// on termine avec le standard... "APPUYEZ UNE TOUCHE.."
	printf("\n\n");
	system("pause");

	// et ÇA, c'est le retour d'un 0 au système d'exploitation.
	return EXIT_SUCCESS;
}
#endif
/*===============================================================================================*/
/*							         MANDAT 3 - 2 FICHIERS										 */
/*===============================================================================================*/
//Utile pour faire des proc_decoups. le 2e main est inactif en ce moment puisque (0)
#if(MANDAT == 3 && NBR_FICHIER == 2)
int main(void)
{	
	int				 reussite = 0;
	int				 somme_octet1 = 0, somme_octet2 = 0;
	t_block			 tab_bloc1[TAILLE_T_BLOC],tab_bloc2[TAILLE_T_BLOC]; //Va devenir la pile -- Tableau dynamique
	t_block			 un_bloc,deux_bloc;
	t_block			 *ptr_tab1 = NULL, *ptr_tab2 = NULL; // pointeur du tableau
	t_regroupement 	 un_reg, deux_reg;
	t_reconstruction un_rec, deux_rec;

	init_decoupage(); // commande d'initiation

	init_bloc("affiche.jpg", &un_bloc, tab_bloc1, &ptr_tab1);
	un_reg = init_regroupement(un_bloc.f_identifiant, TAILLE_PILE);
	un_rec = init_reconstruction(un_bloc.f_identifiant, TAILLE_TAB_REC_INI);
	print_bloc(&un_bloc);

	init_bloc("affiche1.jpg", &deux_bloc, tab_bloc2, &ptr_tab2);
	deux_reg = init_regroupement(deux_bloc.f_identifiant, TAILLE_PILE);
	deux_rec = init_reconstruction(deux_bloc.f_identifiant, TAILLE_TAB_REC_INI);
	print_bloc(&deux_bloc);

	print_bloc(&deux_bloc);
	printf("\nNOMBRE DE FICHIER ACTIF:%i\n", get_nb_fichiers());

	do {
		if (pile_blocs_pleine(&un_reg) == 0) {

			while (get_taille_restante(un_bloc.f_identifiant) != 0 \
				&& pile_blocs_pleine(&un_reg) == 0) {

				proc_decoup(&somme_octet1, &un_bloc);
				reussite = empiler_bloc(&un_reg, un_bloc);

				
			}

		}
		ajouter_pile_blocs(&un_rec, &un_reg);

	} while (get_taille_restante(un_bloc.f_identifiant) != 0);

	for (int i = 0; i < un_rec.nbr_bloc_actu; i++) {
		print_bloc(un_rec.ptr_bloc + i);
	}
/*===============================================================================================*/
	do {
		if (pile_blocs_pleine(&deux_reg) == 0) {
			//division du fichier 
			while (get_taille_restante(deux_bloc.f_identifiant) != 0 \
				&& pile_blocs_pleine(&deux_reg) == 0) {
				// tant que le fichier n'est pas tout diviser et que la pile n'est pas pleine
				proc_decoup(&somme_octet2, &deux_bloc); //decoupe un bloc du fichier
				reussite = empiler_bloc(&deux_reg, deux_bloc);

				
			}

		}
		ajouter_pile_blocs(&deux_rec, &deux_reg);

	} while (get_taille_restante(deux_bloc.f_identifiant) != 0);

	// affichage du contenu du tableau de t_block de deux_rec
	for (int i = 0; i < deux_rec.nbr_bloc_actu; i++) {
		print_bloc(deux_rec.ptr_bloc + i);
	}
	//reconstruction des deux fichiers
	reconstruire_fich(&un_rec, "poster.jpg");
	reconstruire_fich(&deux_rec, "poster1.jpg");
	//liberation des variables en lien avec le premier fichier
	retirer_fichier(un_bloc.f_identifiant);
	free_pile_blocs(&un_reg);
	free_rec_tab(&un_reg);
	//liberation des variables en lien avec le deuxieme fichier
	retirer_fichier(deux_bloc.f_identifiant);
	free_pile_blocs(&deux_reg);
	free_rec_tab(&deux_reg);

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
#if(NBR_FICHIER == 0 || MANDAT == 0) // main de test 
int main(void)
{
	int reussite = 0, i = 0, j = 0;
	int somme_octet = 0;
	char *nom_fich[5];
	char nom_compie[5][50];
	t_block bloc;
	t_regroupement reg[5];
	t_reconstruction rec[5];

	nom_fich[0] = "affiche.jpg";
	nom_fich[1] = "affiche1.jpg";
	nom_fich[2] = "affiche2.jpg";
	nom_fich[3] = "affiche3.jpg";
	nom_fich[4] = "affiche4.jpg";

	printf("%i", MAX_FICHIERS_DECOUPAGE);

	init_decoupage(); // commande d'initiation

	for (i = 0; i < MAX_FICHIERS_DECOUPAGE; i++) {
		init_reg_et_rec(nom_fich[i], (reg + i), (rec + i));
	}

	do {
		while (pile_blocs_pleine(reg) == 0 && \
			get_taille_restante((rec+(MAX_FICHIERS_DECOUPAGE-1))->id_fichier) != 0) {

			proc_decoup(&somme_octet, &bloc);

			reussite = empiler_bloc(reg, bloc);
		}

		for (i = 0; i < MAX_FICHIERS_DECOUPAGE; i++) {
			ajouter_pile_blocs((rec + i), reg);
		}

	} while (get_taille_restante((rec + (MAX_FICHIERS_DECOUPAGE - 1))->id_fichier) != 0);

	for (i = 0; i < NBR_FICHIERS; i++) {
		for (j = 0; j < (rec+i)->nbr_bloc_actu; j++) {
			print_bloc((rec+i)->ptr_bloc + j);
		}
	}

	for (i = 0; i < NBR_FICHIERS; i++) {
		retirer_fichier((rec+i)->id_fichier);
		free_pile_blocs(reg+i);
		free_rec_tab(rec+i);
	}
	//reconstruire_fich(&un_rec, nom_copie1);


	
	//	print_bloc(&tab_bloc1[13]); // TEST DE BLOC DANS LE TABLEAU
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
	//transforme bloc #0 ->> bloc #1
	//bloc->num_bloc = get_nb_blocs_emis(bloc->f_identifiant);
	// affichage du numero du bloc
	printf("\nBLOC#%u\t(TRANSMIS) ", bloc->num_bloc);
	// affichage de l'addresse / ID
	printf("\tID:%u", bloc->f_identifiant);
	//	taille du decoupage
	printf("\tTaille : %i\toctets", \
		(bloc->taille_bloc));
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
	if (bloc->f_identifiant == 0) {
		printf("\nERREUR FICHIER NON-VALIDE\n");
	}
	else {
		//avoir la taille en octet du fichier
		bloc->taille_bloc = get_taille_fichier(bloc->f_identifiant);
		// nombre de fichier ouvert
		bloc->num_bloc = get_nb_fichiers();
		// met l'addresse de la premiere case du tableau
		bloc->buffer = NULL;
	}
	return;
}

void demande_fichier(char * nom_fichier, char * nom_copie) {
	printf("\nNom du fichier a ouvrir :\n >>"); scanf("%s", nom_fichier);
	printf("\nComment voulez-vous appeler votre copie :\n>>"); scanf("%s", nom_copie);
	return;
}

void reception_fichier(int i, char* nom_fichier1, char* nom_copie1, char* nom_fichier2, \
	char* nom_copie2, char* nom_fichier3, char* nom_copie3) {
	if (i >= 1) 
		demande_fichier(nom_fichier1, nom_copie1);
	if (i >= 2) 
		demande_fichier(nom_fichier2, nom_copie2);
	if (i >= 3) 
		demande_fichier(nom_fichier3, nom_copie3);
}

int alea(int max) {
	srand(time(NULL)*rand());
	return ((int)rand()%max);
}

void init_reg_et_rec(const char * nom_fichier, t_regroupement *reg, t_reconstruction *rec) {
	int id = 0;
	id = ajouter_fichier(nom_fichier);
	if (id == 0) {
		printf("\nERREUR FICHIER NON-VALIDE\n");
	}
	*reg = init_regroupement(id, TAILLE_PILE);
	*rec = init_reconstruction(id, TAILLE_TAB_REC_INI);
	
	return;
}

