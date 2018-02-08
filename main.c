/*===============================================================================================*/
/* 											INF145 - TP2										 */
/*===============================================================================================*/

/*
Par    :	Frédéric Thibault	
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



/*===============================================================================================*/
/*												Main											 */		
/*===============================================================================================*/

#if(1)
int main(void)
{
	unsigned int	id_fich;
	int				somme_octet1 = 0, somme_block1 = 0, i1 = 0;
	t_block			un_block;
	t_block			tab_block1[4000];

	// Les variables locales y sont déclaré

	init_decoupage();

	id_fich = ajouter_fichier("affiche.jpg");

	printf("id = %u\n", id_fich);



	// on termine avec le standard... "APPUYEZ UNE TOUCHE.."
	printf("\n\n");
	system("pause");

	// et ÇA, c'est le retour d'un 0 au système d'exploitation.
	return EXIT_SUCCESS;
}
#endif

//Utile pour faire des tests. le 2e main est inactif en ce moment puisque (0)
#if(0)
int main(void)
{
	unsigned int	id_fich;
	int				somme_octet1 = 0, somme_block1 = 0, i1 = 0;
	int				somme_octet2 = 0, somme_block2 = 0, i2 = 0;
	t_block			un_block;
	t_block			tab_block1[4000];

	// Les variables locales y sont déclaré

	init_decoupage();

	id_fich = ajouter_fichier("affiche.jpg");

	printf("id = %u\n", id_fich);



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
