/*===============================================================================================*/
/* 											INF145 - TP2										 */
/*===============================================================================================*/

/*
Par    :	Fr�d�ric Thibault	
Date   :	8 f�vrier 2018


*/

/*===============================================================================================*/

//Permet de d�sactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 

// Librairies usuelles � inclure 
#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#include	<time.h>
#include	<string.h>

#include	"m_decoupage.h"

/*===============================================================================================*/
/*                   			  D�claration des sous-programmes				                 */
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

	// Les variables locales y sont d�clar�

	init_decoupage();

	id_fich = ajouter_fichier("affiche.jpg");

	printf("id = %u\n", id_fich);



	// on termine avec le standard... "APPUYEZ UNE TOUCHE.."
	printf("\n\n");
	system("pause");

	// et �A, c'est le retour d'un 0 au syst�me d'exploitation.
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

	// Les variables locales y sont d�clar�

	init_decoupage();

	id_fich = ajouter_fichier("affiche.jpg");

	printf("id = %u\n", id_fich);



	// on termine avec le standard... "APPUYEZ UNE TOUCHE.."
	printf("\n\n");
	system("pause");

	// et �A, c'est le retour d'un 0 au syst�me d'exploitation.
	return EXIT_SUCCESS;
}
#endif




/*===============================================================================================*/


/*===============================================================================================*/
/*                   				D�finition des sous-programmes					             */
/*===============================================================================================*/
