/*===============================================================================================*/
/* 											INF145 - TP2										 */
/*===============================================================================================*/

/*
Par    :	Frédéric Thibault	
		Christophe Lamarche
Date   :	8 février 2018


*/

/*===============================================================================================*/

//Permet de désactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 

// Librairies usuelles à inclure 
#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#include	<time.h>
#include	<string.h>

#include	"m_decoupage.h"

/*===============================================================================================*/
/*                   			  Déclaration des sous-programmes				                 */
/*===============================================================================================*/

/*===============================================================================================*/
/*                   					LES CONSTANTES							                 */
/*===============================================================================================*/
#define TAILLE_T_BLOC	4000
#define NBR_FICHIER	2	// on change selon la quantite de fichier 


/*===============================================================================================*/
/*												Main											 */		
/*===============================================================================================*/

#if(NBR_FICHIER == 1) // un seul fichier
int main(void)
{
//	unsigned int	id_fich1;
	int				somme_octet1 = 0;
	t_block			tab_bloc1[TAILLE_T_BLOC]; //JE SAIS PAS CA SERT A QUOI 
	t_block			un_bloc;

	init_decoupage(); // commande d'initiation

	un_bloc.f_identifiant = ajouter_fichier("affiche.jpg"); //Reception du fichier
	un_bloc.taille_bloc = get_taille_fichier(un_bloc.f_identifiant); //avoir la taille en octet du fichier
	un_bloc.num_bloc = get_nb_fichiers();
	un_bloc.buffer = &tab_bloc1; //JE SAIS PAS QUOI FAIRE AVEC CE PARAMETRE
	
	print_bloc(&un_bloc);

	if (id_fichier_valide(un_bloc.f_identifiant))
	{
		do {

			un_bloc = get_bloc();
			somme_octet1 = get_taille_restante(un_bloc.f_identifiant);


			printf("BLOC #%u (TRANSMIS) ", get_nb_blocs_emis(un_bloc.f_identifiant));
			printf("\t Taille restante : %u \t octet\n", get_taille_restante(un_bloc.f_identifiant));

		} while (get_taille_restante(un_bloc.f_identifiant) != 0);
	}


	// on termine avec le standard... "APPUYEZ UNE TOUCHE.."
	printf("\n\n");
	system("pause");

	// et ÇA, c'est le retour d'un 0 au système d'exploitation.
	return EXIT_SUCCESS;
}
#endif

//Utile pour faire des tests. le 2e main est inactif en ce moment puisque (0)
#if(NBR_FICHIER == 2) // lorsqu'il y a deux fichiers
int main(void)
{
	int				somme_octet1 = 0, somme_octet2 = 0;
	t_block			un_bloc,deux_bloc;
	t_block			tab_bloc1[TAILLE_T_BLOC]; //JE SAIS PAS CA SERT A QUOI LIVE

	// Les variables locales y sont déclaré

	init_decoupage();

	un_bloc.f_identifiant = ajouter_fichier("affiche.jpg"); //Reception du fichier
	un_bloc.taille_bloc = get_taille_fichier(un_bloc.f_identifiant); //avoir la taille en octet du fichier
	un_bloc.num_bloc = get_nb_fichiers();
	un_bloc.buffer = &tab_bloc1; //JE SAIS PAS QUOI FAIRE AVEC CE PARAMETRE

	print_bloc(&un_bloc);

	deux_bloc.f_identifiant = ajouter_fichier("affiche1.jpg"); //Reception du fichier
	deux_bloc.taille_bloc = get_taille_fichier(deux_bloc.f_identifiant); //avoir la taille en octet du fichier
	deux_bloc.num_bloc = get_nb_fichiers();
	deux_bloc.buffer = &tab_bloc1; //JE SAIS PAS QUOI FAIRE AVEC CE PARAMETRE

	print_bloc(&deux_bloc);

	if (id_fichier_valide(un_bloc.f_identifiant))
	{
		do {
			somme_octet1 = get_taille_restante(un_bloc.f_identifiant);
			un_bloc = get_bloc();
			
			printf("BLOC#%u\t(TRANSMIS) ", get_nb_blocs_emis(un_bloc.f_identifiant));
			printf("\tID:%u",un_bloc.f_identifiant);
			printf("\tTaille : %i\toctets\n", \
				(somme_octet1-get_taille_restante(un_bloc.f_identifiant)));
			
		} while (get_taille_restante(un_bloc.f_identifiant) != 0);
	}
	if (id_fichier_valide(deux_bloc.f_identifiant))
	{
		do {
			somme_octet2 = get_taille_restante(deux_bloc.f_identifiant);
			deux_bloc = get_bloc();

			printf("BLOC#%u\t(TRANSMIS) ", get_nb_blocs_emis(deux_bloc.f_identifiant));
			printf("\tID:%u", deux_bloc.f_identifiant);
			printf("\tTaille : %i\toctets\n", \
				(somme_octet2-get_taille_restante(deux_bloc.f_identifiant)));
			
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
/*                   				Définition des sous-programmes					             */
/*===============================================================================================*/
