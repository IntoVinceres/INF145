/*----------------------------------------------------*/
/* 	par Christophe Lamarche & Frederic Thibault		  */
/*----------------------------------------------------*/

/*====================================================*/
#include "m_reconstruction.h"

/*===================== CONSTANTE ====================*/


/*====================================================*/

/*========= FONCTION DE CONDITION INITIALE ===========*/



/*===================== FONCTION =====================*/



/*======================================================
========================================================
======================================================*/
/*
typedef struct {

	unsigned int id_fichier; // identifiant unique d'un fichier
	t_block* ptr_bloc; //pointeur donnant acces au tableau dynamique de t_block
	unsigned int taille_last_tab; //taille du tableau precedent
	unsigned int nbr_bloc_actu; //nombre de t_bloc actuellement pr�sent
	unsigned int nbr_bloc_tot; //nobre total de t_block du fichier \
	(qu'on obtient en recevant le dernier bloc du d�coupage)

} t_reconstruction;
*/

/*================= FONCTIONS PUBLIQUE ===============*/

// t_reconstruction init_reconstruction(unsigned int id, int taille)
//Description: re�oit l�identifiant unique d�un fichier et
//	la taille initiale de son tableau de reconstruction.Il
//	construit le tableau dynamique n�cessaire et en cas de
//	succ�s de l�allocation, le tableau est travers� et les
//	identifiants - fichier sont tous mis � 0 dans les blocs
//	puis la fonction fixe la taille, l�identifiant unique du
//	fichier et le nombre total de blocks � 0 (en cas d��chec
//	l�allocation, tous les membres du t_reconstruction seront
//	nuls(0 ou NULL)).On retourne le nouvel objet.
t_reconstruction init_reconstruction(unsigned int id, int taille) {

}

// int redim_reconstruction(t_reconstruction * rec, int nouvelle_taille)
//Description: Re�oit l�adresse d�une reconstruction et
//	d�une taille, elle essaie de redimensionner son tableau
//	en conservant les blocs pr�sents(allouez un nouveau
//	tableau et copiez - y tous les blocs du tableau actuel
//	avec memcpy).La fonction met l�identifiant fichier � 0
//	dans les nouvelles cases du tableau et ajuste les
//	autres membres de la structure.On retourne 1 en cas de
//	succ�s, 0 sinon
int redim_reconstruction(t_reconstruction * rec, int nouvelle_taille) {

}

// int ajouter_bloc(t_regroupement * rec, t_block bloc)
//Description: Si les conditions n�cessaires sont
//	satisfaites, on copie le bloc dans le tableau � sa
//	position et on retourne 1 si l�action r�ussit, 0 sinon.//	On redimensionne le t_reconstruction si n�cessaire.
int ajouter_bloc(t_regroupement * rec, t_block bloc) {

}

// void ajouter_pile_blocs(t_reconstruction *rec, t_regroupement * reg)
//Description: Si les deux structures sont du m�me fichier,
//	la fonction va d�piler tous les blocs du regroupement pour les
//	ajouter � la reconstruction(avec la fonction ajouter_bloc).
void ajouter_pile_blocs(t_reconstruction *rec, t_regroupement * reg) {

}

// int bloc_dans_reconstruction(const t_reconstruction * rec)
//Description: Retourne le nombre actuel de blocs du//	fichier dans la structure.
int bloc_dans_reconstruction(const t_reconstruction * rec) {

}

// int etat_reconstruction(t_reconstruction * rec)
//Description: Retourne 1 si tous les blocs du fichier
//	sont dans la structure et 0 sinon.Ceci se produit
//	lorsque le nombre de t_block actuellement pr�sents//	devient �gal au nombre total de t_block du fichier
int etat_reconstruction(t_reconstruction * rec) {

}

// int reconstruire_fich(t_reconstruction *rec, const char * nom_fichier)
//Description: Si la reconstruction est pr�te(avec
//	etat_reconstruction) et le fichier binaire est bien ouvert
//	en �criture, tous les blocs d�octets des t_block sont
//	�crits, en ordre, dans le fichier puis le fichier est
//	ferm�.La fonction lib�re les tableaux dynamiques d�octets
//	dans tous les t_block et lib�re aussi le tableau de
//	t_block dans la structure.Elle retourne 1 en cas de
//	succ�s et 0 sinon
int reconstruire_fich(t_reconstruction *rec, const char * nom_fichier) {

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

	// simples assignations � z�ro
	b.f_identifiant = 0;
	b.num_bloc = 0;
	b.taille_bloc = 0;
	b.buffer = NULL;
	b.bloc_final = 0;

	return b;
}
/*===========================================================*/

