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
	int				somme_octet1 = 0, somme_bloc1 = 0, i1 = 0, parti_bloc = 0;
	t_block			un_bloc;
	t_block			tab_bloc1[4000];

	init_decoupage();

	id_fich = ajouter_fichier("affiche.jpg");

	somme_bloc1 = get_taille_fichier(id_fich);

	printf("id = %u   taille total du fichier = %u\n\n", id_fich, somme_bloc1);

	

	if (id_fichier_valide(id_fich))
	{
		do {
			printf("Valide ou pas : %u\n", id_fichier_valide(id_fich));

			somme_octet1 = get_taille_restante(id_fich);
			printf("Taille restante a extraire : %u\n", somme_octet1);
			un_bloc = get_bloc();

			printf("Nombre de bloc emis : %u\n", get_nb_blocs_emis(id_fich));

			somme_octet1 = get_taille_restante(id_fich);
			printf("Taille restante a extraire : %u\n", somme_octet1);

			printf("Il y a actuellement %u fichier actif dans le programme\n", get_nb_fichiers());
			i1=somme_octet1;
		} while (i1 != 0);
	}
	

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
