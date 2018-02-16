/*---------------------------------------------------*/
/* 	par hugues saulnier 	*/
/*---------------------------------------------------*/

/*==========================================================*/
/*
Le module de découpage de fichiers en blocs disjoints offre
le type t_block et plusieurs fonctions publiques.

Vous pourrez découper un maximum de fichiers simultanement
ce nombre est donné par la constante : MAX_FICHIERS_DECOUPAGE

Le module offre plusieurs fonctions d'interface, certaines modifient le
système de découpage(mutatrices) et d'autres le renseigent sans
modifications (informatrices).
Tout est clairement indiqué dans les déclarations.

*/
/*==========================================================*/
#ifndef __PAQUETAGE__MULTI__
#define __PAQUETAGE__MULTI__

/*==========================================================*/
/*=========================================================*/
//qui permet de désactiver certains warnings du compilateur
#define _CRT_SECURE_NO_WARNINGS
/*=========================================================*/

// Librairies usuelles à inclure
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

// pour définir les tailles minimum et maximum d'un bloc
// de bytes issu du processus de découpage
// ATTENTION le dernier bloc obtenu d'un fichier pourrait être plus petit
// que TAILLE_MIN_BLOCK

#define TAILLE_MIN_BLOCK 400		// NE PAS CHANGER
#define TAILLE_MAX_BLOCK 8000		// NE PAS CHANGER
/*==========================================================*/

/*==========================================================*/
// le type t_block est publique,
// il donne les propriétés d'un élément obtenu du processus de découpage

typedef struct{

	unsigned int f_identifiant; //identifiant unique du fichier

	unsigned int num_bloc;      //numéro de ce bloc dans l'énumération des blocs

	unsigned int taille_bloc;   //nombre d'octets extraits du fichier dans ce bloc

	unsigned char * buffer;     //l'adresse du tableau dynamique contenant le bloc

	unsigned char bloc_final;   //1 si c'est le dernier bloc du découpage, 0 sinon

}t_block; //  PUBLIC
/*==========================================================*/

// DÉCLARATIONS DES FONCTIONS PUBLIQUES

/*==========================================================*/
/* MUTATRICE
initialiser le module de découpage, une action obligée pour
ensuite obtenir l'ensemble des services offerts par le module

PARAMETRE(s): rien

SORTIE: rien

SPECS: aucun fichier n'est en découpage
*/
void init_decoupage(void);		// appeler au debut dans le main
/*==========================================================*/


/*==========================================================*/
/* MUTATRICE
ajouter un fichier au module de découpage

PARAMETRE(s): le nom du fichier à traiter

SORTIE: l'identifiant unique du fichier ( autre que 0 )
		ce "handle" qui doit être conservé pour obtenir des infos
		sur l'état actuel du traitement de ce fichier
		et pour reconnaitre un bloc

		0 si le nombre de fichiers est complet ou si le fichier
		ne peut être ouvert en lecture

SPECS:  C'est une erreur de donner en parametre le nom d'un fichier
		déja ouvert, le module le refuse et retour de 0
*/
unsigned int ajouter_fichier(const char * nom_fichier);
/*==========================================================*/

/*==========================================================*/
/* MUTATRICE
retirer un fichier complètement découpé du module de découpage

PARAMETRE(s): l'identifiant unique du fichier

SORTIE: 1 (succès) ou 0 (erreur)

SPECS: l'usage de cette fonction est obligatoire pour
	   liberer la place occupée par un fichier au découpage terminé
*/
int retirer_fichier(unsigned int f_identifiant);
/*==========================================================*/

/*==========================================================*/
/* MUTATRICE
obtenir un bloc d'un des fichiers du module dont le découpage
n'est pas complété
le fichier est choisi aléatoirement parmi ceux dans cet état

PARAMETRE(s): rien

SORTIE: un t_block aux propriétés toute nulles (= 0) si aucun fichier
		n'est en découpage actif,
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
connaitre le nombre d'octets restant à traiter dans un fichier

PARAMETRE(s): l'identifiant d'un fichier

SORTIE: -1 si l'identifiant n'est pas valide,
		 sinon la taille en octets restant à mettre en blocs

SPECS: aucune
*/
int get_taille_restante(unsigned int f_identifiant);
/*==========================================================*/

/*==========================================================*/
/* INFORMATRICE
obtenir le nombre de blocs émis à date pour un fichier

PARAMETRE(s): l'identifiant d'un fichier

SORTIE: le nombre de blocs extraits du fichier, -1 sinon

SPECS: on ne tient aucun compte de la validité de l'identifiant
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

// ATTENTION CES DEUX PROCÉDURES VOUS SERONT TRÈS UTILES EN DÉBUG
// c'est à vous de les implémenter

/*==========================================================*/
// Cette procédure ne fait que donner un affichage simple
// des propriétés d'un bloc reçu en référence
// printf(); Attention on recoit l'adresse (référence
void print_bloc(const t_block * p_bloc);

/*==========================================================*/
// Cette procédure ne fait que donner un affichage simple de 
// l'état d'un fichier dont vous avez l'identifiant unique.
// faites des printf expliquant les résultats des informations
// obtenues avec l'identifiant reçu
void print_etat_fichier(unsigned int f_identifiant);

/*==========================================================*/
#endif


