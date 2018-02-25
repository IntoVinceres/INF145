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
/*
typedef struct {

	unsigned int id_fichier; // identifiant unique d'un fichier
	t_block* ptr_bloc; //pointeur donnant acces au tableau dynamique de t_block
	unsigned int taille_tab; //taille du tableau dynamique
	unsigned int nbr_bloc; //nombre de t_bloc dans le tableau dynamique

} t_regroupement;

t_regroupement * reg ----> pointeur vers le regroupement

*/

/*================= FONCTIONS PUBLIQUE ===============*/
// t_regroupement init_regroupement (unsigned int id, int taille)
// Description : recoit l'identifiant unique d'un fichier et la taille maximale de la pile. Elle construit le
//				 tableau dynamique necessaire et en cas de succes de l'allocation va fixer la taille,
//				 l'identifiant unique et le nombre de d'elements (en cas d'echec de l'allocation, tous les 
//				 membres du t_regroupement seront nuls (0 ou NULL). Elle retourne le nouvel objet

t_regroupement init_regroupement(unsigned int id, int taille) {
	t_regroupement objet;

	objet.ptr_bloc = (t_block *)calloc(taille, sizeof(t_block));

	if (objet.ptr_bloc == NULL) {
		objet.taille_tab = 0;
		objet.id_fichier = 0;
		objet.nbr_bloc = 0;
	}
	else {
		objet.taille_tab = taille ;
		objet.id_fichier = id;
		objet.nbr_bloc = 0;
	}

	return objet;
}

// int empiler_bloc (t_regroupement * reg, t_block bloc)
// Description : Va empiler le block recu si les conditions necessaires sont satisfaites, elle 
//				 copie le bloc dans le tableau et retourne 1 si l'action reussit et 0 sinon.

int empiler_bloc(t_regroupement * reg, t_block bloc) {
	int result = 0;
	
	//verification de l'etat de la pile
	if (pile_blocs_pleine(reg) != 0) {
		result = 0; // le push a failli
		printf("\nLA TENTATIVE D'EMPILER A ECHOUER\n");
	}else{
		*(reg->ptr_bloc+pile_blocs_nombre(reg)) = bloc; // depose (push) les informations du bloc \
		dans la case memoire de la pile (prend en compte que la premiere espace memoire \
		est la case 0
		(reg->nbr_bloc)++; // informe du depot du bloc dans la pile
		result = 1; // le push est complete
	}

	return result; // retourne le succes ou l'echec du push
}

// int depiler_bloc (t_regroupement * reg, t_bloc * bloc)
// Description : Va depiler un bloc si les conditions necessaires sont satisfaites, elle copie le 
//				 t_block du haut dans la reference recue en parametre et retourne 1 si l'action
//				 est reussi et 0 sinon.

int depiler_bloc(t_regroupement * reg, t_block * bloc) {
	int result = 0;

	if ((pile_blocs_vide(reg)) != 0) {
		result = 0; //le pop a failli -- impossibilite d'effectuer la tache
		printf("\nLA TENTATIVE DE DEPILER A ECHOUER\n");
	}
	else {
		(reg->nbr_bloc)--; // on enleve un bloc dans la pile
		*bloc = *(reg->ptr_bloc+pile_blocs_nombre(reg)); // on transmet les informations dans le bloc
		result = 1;
	}

	return result;
}

// int pile_blocs_pleine (const t_regroupement * reg)
// Description : Retourne 1 si la pile est pleine et 0 sinon.
int pile_blocs_pleine(const t_regroupement * reg) {
	int result = 0 ;

	if (pile_blocs_nombre(reg) == ( pile_blocs_taille(reg) )) {
		result = 1;
	}
	return result;
}

// int pile_blocs_vide (const t_regroupement * reg)
// Description : retourne 1 si la pile est vide et 0 sinon.
int pile_blocs_vide(const t_regroupement * reg) {
	int result = 0;

	if (pile_blocs_nombre(reg) == 0) {
		result = 1;
	}
	return result; 
}

// int pile_blocs_taille (const t_regroupement * reg)
// Description : Retourne le nombre maximum de t_block dans la pile.
int pile_blocs_taille(const t_regroupement * reg) {
	int taille_max = reg->taille_tab;

	return  taille_max;
}

// int pile_blocs_nombre (const t_regroupement * reg)
// Description : Retourne le nombre de t_block actuellement dans la pile
int pile_blocs_nombre(const t_regroupement * reg) {
	int nbr_actu = 0;
	nbr_actu = reg->nbr_bloc; // transfert la quantite de t_bloc dans le tableau dynamique
	
	return nbr_actu;
}

// void free_pile_blocs (t_regroupement * reg)
// Description : libere le tableau dynamique et remet tous les membres à 0 ou NULL
void free_pile_blocs(t_regroupement * reg) {
	free(reg->ptr_bloc); reg->ptr_bloc = NULL;
	return;
}

/*
typedef struct {

unsigned int id_fichier; // identifiant unique d'un fichier
t_block* ptr_bloc; //pointeur donnant acces au tableau dynamique de t_block
unsigned int taille_tab; //taille du tableau dynamique
unsigned int nbr_bloc; //nombre de t_bloc dans le tableau dynamique

} t_regroupement;

t_regroupement * reg ----> pointeur vers le regroupement

*/
/*==========================================================*/
static t_block block_vide(void);
static t_block block_vide(void) {
	t_block b;

	// simples assignations à zéro
	b.f_identifiant = 0;
	b.num_bloc = 0;
	b.taille_bloc = 0;
	b.buffer = NULL;
	b.bloc_final = 0;

	return b;
}
/*===========================================================*/

