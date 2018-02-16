/*----------------------------------------------------*/
/* 	par Christophe Lamarche & Frederic Thibault		  */
/*----------------------------------------------------*/

/*====================================================*/
#include "m_regroupement.h"

/*===================== CONSTANTE ====================*/


/*====================================================*/

/*========= FONCTION DE CONDITION INITIALE ===========*/

// TEST BON IDENTIFIANT FICHIER

// TEST EMPILER SI LE NOMBRE ACTUEL DE T_BLOCK EST INFERIEUR A TAILLE DU TABLEAU

// TEST DEPILER SI LE NOMBRE ACTUEL DE T_BLOCK EST SUPÉRIEUR A ZERO

/*===================== FONCTION =====================*/

// FONCTION DE PUSH ( A LA POSITION DU NOMBRE ACTUEL DE T_BLOCK QU'ON INCREMENTE ENSUITE

// FONCITON DE POP ( ON DECREMENTE LE NOMBRE ACTUEL DE T_BLOCK & ON RETOURNE CE T_BLOC

/*======================================================
========================================================
======================================================*/

/*================= FONCTIONS PUBLIQUE ===============*/
// t_regroupement init_regroupement (unsigned int id, int taille)
// Description : recoit l'identifiant unique d'un fichier et la taille maximale de la pile. Elle construit le
//				 tableau dynamique necessaire et en cas de succes de l'allocation va fixer la taille,
//				 l'identifiant unique et le nombre de d'elements (en cas d'echec de l'allocation, tous les 
//				 membres du t_regroupement seront nuls (0 ou NULL). Elle retourne le nouvel objet

t_regroupement init_regroupement(unsigned int id, int taille) {
	t_regroupement objet;

	//initialisation BIDON
	objet.id_fichier = 0;
	objet.nbr_bloc = 0;
	objet.ptr_bloc = &objet;
	objet.taille_tab = 0;
	return objet;
}

// int empiler_bloc (t_regroupement * reg, t_block bloc)
// Description : Va empiler le block recu si les conditions necessaires sont satisfaites, elle copie le bloc
//				 dans le tableau et retourne 1 si l'action reussit et 0 sinon.

int empiler_bloc(t_regroupement * reg, t_block bloc) {
	int result=0;
	return result;
}

// int depiler_bloc (t_regroupement * reg, t_bloc * bloc)
// Description : Va depiler un bloc si les conditions necessaires sont satisfaites, elle copie le t_block
//				 du haut dans la reference recue en parametre et retourne 1 si l'action est reussi et 0 sinon.

int depiler_bloc(t_regroupement * reg, t_block * bloc) {
	int result = 0;
	return result;
}

// int pile_blocs_pleine (const t_regroupement * reg)
// Description : Retourne 1 si la pile est pleine et 0 sinon.
int pile_blocs_pleine(const t_regroupement * reg) {
	int result = 0;
	return result;
}

// int pile_blocs_vide (const t_regroupement * reg)
// Description : retourne 1 si la pile est vide et 0 sinon.
int pile_blocs_vide(const t_regroupement * reg) {
	int result = 0;
	return result; 
}

// int pile_blocs_taille (const t_regroupement * reg)
// Description : Retourne le nombre maximum de t_block dans la pile.
int pile_blocs_taille(const t_regroupement * reg) {
	int taille_max = 0;
	return  taille_max;
}

// int pile_blocs_nombre (const t_regroupement * reg)
// Description : Retourne le nombre de t_block actuellement dans la pile
int pile_blocs_nombre(const t_regroupement * reg) {
	int nbr_actu = 0;
	return nbr_actu;
}

// void free_pile_blocs (t_regroupement * reg)
// Description : libere le tableau dynamique et remet tous les membres à 0 ou NULL
void free_pile_blocs(t_regroupement * reg) {
	return;
}

/*==========================================================*/
/*static t_block block_vide(void) {
	t_block b;

	// simples assignations à zéro
	b.f_identifiant = 0;
	b.num_bloc = 0;
	b.taille_bloc = 0;
	b.buffer = NULL;
	b.bloc_final = 0;
	return b;
}*/
/*===========================================================*/

