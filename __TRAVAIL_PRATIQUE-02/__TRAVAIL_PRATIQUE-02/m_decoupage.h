/*---------------------------------------------------*/
/* 	par hugues saulnier 	*/
/*---------------------------------------------------*/

/*==========================================================*/
/*
Le module de d�coupage de fichiers en blocs disjoints offre
le type t_block et plusieurs fonctions publiques.

Vous pourrez d�couper un maximum de fichiers simultanement
ce nombre est donn� par la constante : MAX_FICHIERS_DECOUPAGE

Le module offre plusieurs fonctions d'interface, certaines modifient le
syst�me de d�coupage(mutatrices) et d'autres le renseigent sans
modifications (informatrices).
Tout est clairement indiqu� dans les d�clarations.

*/
/*==========================================================*/
#ifndef __PAQUETAGE__MULTI__
#define __PAQUETAGE__MULTI__

/*==========================================================*/
/*=========================================================*/
//qui permet de d�sactiver certains warnings du compilateur
#define _CRT_SECURE_NO_WARNINGS
/*=========================================================*/

// Librairies usuelles � inclure
/*=========================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <assert.h>


/*==========================================================*/
// LES CONSTANTES

// le nombre maximum de fichiers que peut traiter simultanement le module

#define MAX_FICHIERS_DECOUPAGE  5  //<=====  <=====  <=======  <=====  <========  <=====  <==== A CHANGER PLUS TARD !!!!

// pour d�finir les tailles minimum et maximum d'un bloc
// de bytes issu du processus de d�coupage
// ATTENTION le dernier bloc obtenu d'un fichier pourrait �tre plus petit
// que TAILLE_MIN_BLOCK

#define TAILLE_MIN_BLOCK 400		// NE PAS CHANGER
#define TAILLE_MAX_BLOCK 8000		// NE PAS CHANGER
/*==========================================================*/

/*==========================================================*/
// le type t_block est publique,
// il donne les propri�t�s d'un �l�ment obtenu du processus de d�coupage

typedef struct{

	unsigned int f_identifiant; //identifiant unique du fichier

	unsigned int num_bloc;      //num�ro de ce bloc dans l'�num�ration des blocs

	unsigned int taille_bloc;   //nombre d'octets extraits du fichier dans ce bloc

	unsigned char * buffer;     //l'adresse du tableau dynamique contenant le bloc

	unsigned char bloc_final;   //1 si c'est le dernier bloc du d�coupage, 0 sinon

}t_block; //  PUBLIC
/*==========================================================*/

// D�CLARATIONS DES FONCTIONS PUBLIQUES

/*==========================================================*/
/* MUTATRICE
initialiser le module de d�coupage, une action oblig�e pour
ensuite obtenir l'ensemble des services offerts par le module

PARAMETRE(s): rien

SORTIE: rien

SPECS: aucun fichier n'est en d�coupage
*/
void init_decoupage(void);		// appeler au debut dans le main
/*==========================================================*/


/*==========================================================*/
/* MUTATRICE
ajouter un fichier au module de d�coupage

PARAMETRE(s): le nom du fichier � traiter

SORTIE: l'identifiant unique du fichier ( autre que 0 )
		ce "handle" qui doit �tre conserv� pour obtenir des infos
		sur l'�tat actuel du traitement de ce fichier
		et pour reconnaitre un bloc

		0 si le nombre de fichiers est complet ou si le fichier
		ne peut �tre ouvert en lecture

SPECS:  C'est une erreur de donner en parametre le nom d'un fichier
		d�ja ouvert, le module le refuse et retour de 0
*/
unsigned int ajouter_fichier(const char * nom_fichier);
/*==========================================================*/

/*==========================================================*/
/* MUTATRICE
retirer un fichier compl�tement d�coup� du module de d�coupage

PARAMETRE(s): l'identifiant unique du fichier

SORTIE: 1 (succ�s) ou 0 (erreur)

SPECS: l'usage de cette fonction est obligatoire pour
	   liberer la place occup�e par un fichier au d�coupage termin�
*/
int retirer_fichier(unsigned int f_identifiant);
/*==========================================================*/

/*==========================================================*/
/* MUTATRICE
obtenir un bloc d'un des fichiers du module dont le d�coupage
n'est pas compl�t�
le fichier est choisi al�atoirement parmi ceux dans cet �tat

PARAMETRE(s): rien

SORTIE: un t_block aux propri�t�s toute nulles (= 0) si aucun fichier
		n'est en d�coupage actif,
		sinon un t_block valide

SPECS: aucune
*/
t_block get_bloc(void);
/*==========================================================*/

/*==========================================================*/
/* INFORMATRICE
connaitre le nombre de fichiers actuellement en traitement dans le module

PARAMETRE(s): rien

SORTIE: un entier >= 0

SPECS: aucune
*/
int get_nb_fichiers(void);
/*==========================================================*/

/*==========================================================*/
/* INFORMATRICE
connaitre la taille en octets d'un fichier en traitement

PARAMETRE(s): l'identifiant  d'un  fichier

SORTIE: -1 si l'identifiant n'est pas valide,
		sinon la taille en octets du fichier

SPECS: aucune
*/
int get_taille_fichier(unsigned int f_identifiant);
/*==========================================================*/

/*==========================================================*/
/* INFORMATRICE
connaitre le nombre d'octets restant � traiter dans un fichier

PARAMETRE(s): l'identifiant d'un fichier

SORTIE: -1 si l'identifiant n'est pas valide,
		 sinon la taille en octets restant � mettre en blocs

SPECS: aucune
*/
int get_taille_restante(unsigned int f_identifiant);
/*==========================================================*/

/*==========================================================*/
/* INFORMATRICE
obtenir le nombre de blocs �mis � date pour un fichier

PARAMETRE(s): l'identifiant d'un fichier

SORTIE: le nombre de blocs extraits du fichier, -1 sinon

SPECS: on ne tient aucun compte de la validit� de l'identifiant
*/
int get_nb_blocs_emis(unsigned int f_identifiant);
/*==========================================================*/

/*==========================================================*/
/* INFORMATRICE
tester si l'identifiant d'un fichier est actuellement valide dans le module

PARAMETRE(s): l'identifiant d'un fichier

SORTIE: 0 (non-valide) ou 1 (valide)

SPECS: aucune
*/
int id_fichier_valide(unsigned int f_identifiant);
/*==========================================================*/


/*==========================================================*/
/*==========================================================*/

// ATTENTION CES DEUX PROC�DURES VOUS SERONT TR�S UTILES EN D�BUG
// c'est � vous de les impl�menter

/*==========================================================*/
// Cette proc�dure ne fait que donner un affichage simple
// des propri�t�s d'un bloc re�u en r�f�rence
// printf(); Attention on recoit l'adresse (r�f�rence
void print_bloc(const t_block * p_bloc);

/*==========================================================*/
// Cette proc�dure ne fait que donner un affichage simple de 
// l'�tat d'un fichier dont vous avez l'identifiant unique.
// faites des printf expliquant les r�sultats des informations
// obtenues avec l'identifiant re�u
void print_etat_fichier(unsigned int f_identifiant);

/*==========================================================*/
#endif


