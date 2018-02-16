/*****************************************************/
//  PAR   : Christophe Lamarche & Frederic Thibault		     

/*****************************************************/

/*
Ce module offre  [...]
*/


/*
Le module offre  :


[...]

[...]

[...]

*/

/**********************************************************/

#ifndef  __MODULE_REGROUPEMENT__
#define  __MODULE_REGROUPEMENT__

/*****************************************************/

#define _CRT_SECURE_NO_WARNINGS  

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"m_decoupage.h"
/*****************************************************/


/*****************************************************/
/*		             CONSTANTE	   				     */
/*****************************************************/


/*****************************************************/

/*****************************************************/
/*****************************************************/
typedef struct {

	unsigned int id_fichier; // identifiant unique d'un fichier
	t_block* ptr_bloc; //pointeur donnant acces au tableau dynamique de t_block
	unsigned int taille_tab; //taille du tableau dynamique
	unsigned int nbr_bloc; //nombre de t_bloc dans le tableau dynamique

} t_regroupement;


/****************** NOM FONCTION **********************/
/*
donne 

PARAMETRES : 

RETOUR : 

SPECIFICATIONS :

*/
/*****************************************************/

/**************** INIT_REGROUPEMENT ******************/
/*
Description : recoit l'identifiant unique d'un fichier
	et la taille maximale de la pile. Elle construit le
	tableau dynamique necessaire et en cas de succes de
	l'allocation va fixer la taille, l'identifiant unique 
	et le nombre de d'elements (en cas d'echec de 
	l'allocation, tous les membres du t_regroupement seront 
	nuls (0 ou NULL). Elle retourne le nouvel objet
PARAMETRES :

RETOUR :

SPECIFICATIONS :

*/
t_regroupement init_regroupement(unsigned int id, int taille);
/*****************************************************/

/******************	EMPILER_BLOC *********************/
/*
Description : Va empiler le block recu si les 
conditions necessaires sont satisfaites, elle copie le bloc
dans le tableau et retourne 1 si l'action reussit et 0 sinon.

PARAMETRES :

RETOUR :

SPECIFICATIONS :

*/
int empiler_bloc(t_regroupement * reg, t_block bloc);
/*****************************************************/
 

/****************** DEPILER_BLOC **********************/
/*
Description : Va depiler un bloc si les conditions 
necessaires sont satisfaites, elle copie le t_block
du haut dans la reference recue en parametre et 
retourne 1 si l'action est reussi et 0 sinon.

PARAMETRES :

RETOUR :

SPECIFICATIONS :

*/
int depiler_bloc(t_regroupement * reg, t_block * bloc);
/*****************************************************/

/*************** PILE_BLOCS_PLEINE *******************/
/*
Description : Retourne 1 si la pile est pleine et 0 sinon.

PARAMETRES :

RETOUR :

SPECIFICATIONS :

*/
int pile_blocs_pleine(const t_regroupement * reg);
/*****************************************************/

/***************** PILE_BLOCS_VIDE *******************/
/*
Description : retourne 1 si la pile est vide et 0 sinon.

PARAMETRES :

RETOUR :

SPECIFICATIONS :

*/
int pile_blocs_vide(const t_regroupement * reg);
/*****************************************************/

/**************** PILE_BLOCS_TAILLE ******************/
/*
Description : Retourne le nombre maximum de t_block dans la pile.

PARAMETRES :

RETOUR :

SPECIFICATIONS :

*/
int pile_blocs_taille(const t_regroupement * reg);
/*****************************************************/

/****************** NOM FONCTION **********************/
/*
Description : Retourne le nombre de t_block actuellement dans la pile

PARAMETRES :

RETOUR :

SPECIFICATIONS :

*/
int pile_blocs_nombre(const t_regroupement * reg);
/*****************************************************/

/****************** NOM FONCTION **********************/
/*
Description : libere le tableau dynamique et remet tous les membres à 0 ou NULL

PARAMETRES :

RETOUR :

SPECIFICATIONS :

*/
void free_pile_blocs(t_regroupement * reg);
/*****************************************************/
#endif
/**********************************************************/


