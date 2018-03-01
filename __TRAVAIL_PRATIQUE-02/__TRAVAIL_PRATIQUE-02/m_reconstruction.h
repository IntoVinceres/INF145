/*************************************************************************************************/
//  PAR   : Christophe Lamarche & Frederic Thibault		     

/*************************************************************************************************/

/*
Ce module offre  [...]
*/


/*
Le module offre  :


[...]

[...]

[...]

*/

/*************************************************************************************************/

#ifndef  __MODULE_RECONSTRUCTION__
#define  __MODULE_RECONSTRUCTION__

/*************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS  

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"m_decoupage.h"
#include"m_regroupement.h"
/*************************************************************************************************/


/*************************************************************************************************/
/*											CONSTANTE	   									     */
/*************************************************************************************************/


/*************************************************************************************************/

/*************************************************************************************************/
/*************************************************************************************************/
typedef struct {

	unsigned int id_fichier; // identifiant unique d'un fichier
	t_block* ptr_bloc; //pointeur donnant acces au tableau dynamique de t_block
	unsigned int taille_last_tab; //taille du tableau precedent
	unsigned int nbr_bloc_actu; //nombre de t_bloc actuellement pr�sent
	unsigned int nbr_bloc_tot; //nobre total de t_block du fichier \
					(qu'on obtient en recevant le dernier bloc du d�coupage)

} t_reconstruction;


/**************************************** NOM FONCTION *******************************************/
/*
donne

PARAMETRES :

RETOUR :

SPECIFICATIONS :

*/
/*************************************************************************************************/

/************************************ INIT_RECONSTRUCTION ****************************************/
/* MUTATRICE
Description : re�oit l�identifiant unique d�un fichier et 
la taille initiale de son tableau de reconstruction. Il 
construit le tableau dynamique n�cessaire et en cas de 
succ�s de l�allocation, le tableau est travers� et les 
identifiants-fichier sont tous mis � 0 dans les blocs 
puis la fonction fixe la taille, l�identifiant unique du 
fichier et le nombre total de blocks � 0 (en cas d��chec 
l�allocation, tous les membres du t_reconstruction seront
nuls (0 ou NULL)). On retourne le nouvel objet.

PARAMETRES : id du fichier 
			 taille initiale du tableau

RETOUR : un objet de type t_reconstruction 

SPECIFICATIONS :

*/
t_reconstruction init_reconstruction(unsigned int id, int taille);
/************************************************************************************************/

/**********************************	REDIM_RECONSTRUCTION ****************************************/
/* MUTATRICE
Description : Re�oit l�adresse d�une reconstruction et
d�une taille, elle essaie de redimensionner son tableau
en conservant les blocs pr�sents (allouez un nouveau 
tableau et copiez-y tous les blocs du tableau actuel 
avec memcpy). La fonction met l�identifiant fichier � 0
dans les nouvelles cases du tableau et ajuste les 
autres membres de la structure. On retourne 1 en cas de
succ�s, 0 sinon

PARAMETRES : un pointeur d'un objet de type t_reconstruction
			 la nouvelle taille du tableau dynamique

RETOUR : 0 ->> la modification a echouer
		 1 ->> la modification est un succes

SPECIFICATIONS :

*/
int redim_reconstruction(t_reconstruction * rec, int nouvelle_taille);
/*************************************************************************************************/


/**************************************** AJOUTER_BLOC *******************************************/
/* MUTATRICE
Description : Si les conditions n�cessaires sont
satisfaites, on copie le bloc dans le tableau � sa 
position et on retourne 1 si l�action r�ussit, 0 sinon.
On redimensionne le t_reconstruction si n�cessaire.

PARAMETRES : un pointeur du'un objet de type t_reconstruction
			 le t_bloc a ajouter
RETOUR : 0 ->> l'ajout a echouer
		 1 ->> l'ajout est reussi

SPECIFICATIONS :

*/
int ajouter_bloc(t_reconstruction * rec, t_block bloc);
/*************************************************************************************************/

/************************************* AJOUTER_PILE_BLOCS ****************************************/
/* MUTATRICE
Description : Si les deux structures sont du m�me fichier,
la fonction va d�piler tous les blocs du regroupement pour les
ajouter � la reconstruction (avec la fonction ajouter_bloc).


PARAMETRES : un pointeur du'un objet de type t_reconstruction
			 un pointeur du'un objet de type t_regroupement

RETOUR : RIEN

SPECIFICATIONS :

*/
void ajouter_pile_blocs(t_reconstruction *rec, t_regroupement * reg);
/*************************************************************************************************/

/******************************** BLOC_DANS_RECONSTRUCTION ***************************************/
/*  INFORMATRICE
Description : Retourne le nombre actuel de blocs du 
			  fichier dans la structure.

PARAMETRES : un pointeur d'un objet de type t_reconstruction

RETOUR : le nombre de bloc dans l'objet t_reconstruction

SPECIFICATIONS :

*/
int bloc_dans_reconstruction(const t_reconstruction * rec);
/*************************************************************************************************/

/********************************** ETAT_RECONSTRUCTION ******************************************/
/* INFORMATRICE
Description : Retourne 1 si tous les blocs du fichier
sont dans la structure et 0 sinon. Ceci se produit 
lorsque le nombre de t_block actuellement pr�sents 
devient �gal au nombre total de t_block du fichier.


PARAMETRES : un pointeur de l'objet de type t_reconstruction
			 du fichier

RETOUR : 0 ->> il reste des blocs a ajouter dans l'objet
			   t_reconstruction du fichier
		 1 ->> tous les blocs du fichier sont dans l'objet
			   t_reconstruction du fichier

SPECIFICATIONS :

*/
int etat_reconstruction(t_reconstruction * rec);
/*************************************************************************************************/

/*********************************** RECONSTRUIRE_FICH *******************************************/
/* MUTATRICE
Description : Si la reconstruction est pr�te (avec 
etat_reconstruction) et le fichier binaire est bien ouvert
en �criture, tous les blocs d�octets des t_block sont 
�crits, en ordre, dans le fichier puis le fichier est 
ferm�. La fonction lib�re les tableaux dynamiques d�octets 
dans tous les t_block et lib�re aussi le tableau de 
t_block dans la structure. Elle retourne 1 en cas de 
succ�s et 0 sinon

PARAMETRES : L'objet de type t_reconstruction du fichier
			 Le nom du nouveau fichier
RETOUR : 0 ->> la reconstruction a echouer
		 1 ->> la reconstruction est r�ussi

SPECIFICATIONS :

*/
int reconstruire_fich(t_reconstruction *rec, const char * nom_fichier);
/*************************************************************************************************/

/*************************************** FREE_REC_TAB ********************************************/
/*
Description : libere le tableau dynamique et remet tous les membres � 0 ou NULL

PARAMETRES : pointeur de l'objet de type de t_reconstruction

RETOUR : RIEN

SPECIFICATIONS :

*/
void free_rec_tab(t_reconstruction * rec);
#endif
/*************************************************************************************************/


