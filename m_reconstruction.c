/*----------------------------------------------------*/
/* 	par Christophe Lamarche & Frederic Thibault		  */
/*----------------------------------------------------*/

/*====================================================*/
#include "m_reconstruction.h"

/*===================== CONSTANTE ====================*/

#define AUGMENTE_TAB	4

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
	unsigned int nbr_bloc_actu; //nombre de t_bloc actuellement présent
	unsigned int nbr_bloc_tot; //nobre total de t_block du fichier \
	(qu'on obtient en recevant le dernier bloc du découpage)

} t_reconstruction;
*/

/*================= FONCTIONS PUBLIQUE ===============*/

// t_reconstruction init_reconstruction(unsigned int id, int taille)
//Description: reçoit l’identifiant unique d’un fichier et
//	la taille initiale de son tableau de reconstruction.Il
//	construit le tableau dynamique nécessaire et en cas de
//	succès de l’allocation, le tableau est traversé et les
//	identifiants - fichier sont tous mis à 0 dans les blocs
//	puis la fonction fixe la taille, l’identifiant unique du
//	fichier et le nombre total de blocks à 0 (en cas d’échec
//	l’allocation, tous les membres du t_reconstruction seront
//	nuls(0 ou NULL)).On retourne le nouvel objet.
t_reconstruction init_reconstruction(unsigned int id, int taille) {
	t_reconstruction rec;
	
rec.ptr_bloc = (t_block *)calloc(taille, sizeof(t_block));

if (rec.ptr_bloc == NULL) {
	rec.id_fichier = 0;
	rec.ptr_bloc = NULL;
	rec.taille_last_tab = 0;
	rec.nbr_bloc_actu = 0;
	rec.nbr_bloc_tot = 0;
}
else {
	rec.id_fichier = id;
	//		rec.ptr_bloc => adresse du tableau dynamique
	rec.taille_last_tab = taille;
	rec.nbr_bloc_actu = 0;
	rec.nbr_bloc_tot = taille;
}

return rec;
}

// int redim_reconstruction(t_reconstruction * rec, int nouvelle_taille)
//Description: Reçoit l’adresse d’une reconstruction et
//	d’une taille, elle essaie de redimensionner son tableau
//	en conservant les blocs présents(allouez un nouveau
//	tableau et copiez - y tous les blocs du tableau actuel
//	avec memcpy).La fonction met l’identifiant fichier à 0
//	dans les nouvelles cases du tableau et ajuste les
//	autres membres de la structure.On retourne 1 en cas de
//	succès, 0 sinon
int redim_reconstruction(t_reconstruction * rec, int nouvelle_taille) {
	int reussite = 0;

	rec->ptr_bloc = realloc(rec->ptr_bloc, nouvelle_taille);

	if (rec->ptr_bloc != NULL) {
		reussite = 1;
	}

	return reussite;
}

// int ajouter_bloc(t_reconstruction * rec, t_block bloc)
//Description: Si les conditions nécessaires sont
//	satisfaites, on copie le bloc dans le tableau à sa
//	position et on retourne 1 si l’action réussit, 0 sinon.
//	On redimensionne le t_reconstruction si nécessaire.
int ajouter_bloc(t_reconstruction * rec, t_block bloc) {
	int reussite = 0; // variable de la reussite de la fonction
	t_block* ptr_tab = rec->ptr_bloc;
	int plus = bloc.num_bloc;

	if (pile_rec_pleine(rec)) { // verification qu'il reste de l'espace dans le tableau
		redim_reconstruction(rec, (rec->nbr_bloc_tot + AUGMENTE_TAB)); // redimensionner du tableau
	}

	*((ptr_tab)+plus) = bloc; // on incorpore le bloc a la position du numero du bloc \
									   dans le tableau de reconstruction
	rec->nbr_bloc_actu++; //augmentation du nombre de bloc dans le tableau de reconstruction

	if ((ptr_tab + plus)->taille_bloc != 0) { //si la valeur de la taille de bloc a ete modifiee
		reussite = 1; // la modification a reussi
	}

	return reussite;
}

// void ajouter_pile_blocs(t_reconstruction *rec, t_regroupement * reg)
//Description: Si les deux structures sont du même fichier,
//	la fonction va dépiler tous les blocs du regroupement pour les
//	ajouter à la reconstruction(avec la fonction ajouter_bloc).
void ajouter_pile_blocs(t_reconstruction *rec, t_regroupement * reg) {
	int i = 0; // variable sur l'indice du bloc transfere

	if (rec->id_fichier == reg->id_fichier) { // si la reconstruction et le regroupement travaille \
												 sur le meme fichier 
		while (i < reg->taille_tab) { // on transfert tous les blocs de la pile dans le tableau \
										  de reconstruction
			ajouter_bloc(rec, *((reg->ptr_bloc) + i)); // on ajoute le ieme bloc de la pile 
			i++; // on incremente la 
		}
	}

	return;
}

// int bloc_dans_reconstruction(const t_reconstruction * rec)
//Description: Retourne le nombre actuel de blocs du
//	fichier dans la structure.
int bloc_dans_reconstruction(const t_reconstruction * rec) {
	return rec->nbr_bloc_actu;
}

// int etat_reconstruction(t_reconstruction * rec)
//Description: Retourne 1 si tous les blocs du fichier
//	sont dans la structure et 0 sinon.Ceci se produit
//	lorsque le nombre de t_block actuellement présents
//	devient égal au nombre total de t_block du fichier
int etat_reconstruction(t_reconstruction * rec) {
	int fini = 0; // 0 ->> la reconstruction n'est pas fini \
					 1 ->> la reconstruction est fini
	if (get_taille_restante(rec->id_fichier) == 0) { //si on a fini de couper le fichier en bloc
		if (rec->nbr_bloc_actu == get_nb_blocs_emis(rec->id_fichier)) { 
			//si la quantite de bloc dans la reconstruction est egale a la quantite de bloc \
			  emis pour le fichier
			fini = 1;
		}
	}

	return fini;
}

// int reconstruire_fich(t_reconstruction *rec, const char * nom_fichier)
//Description: Si la reconstruction est prête(avec
//	etat_reconstruction) et le fichier binaire est bien ouvert
//	en écriture, tous les blocs d’octets des t_block sont
//	écrits, en ordre, dans le fichier puis le fichier est
//	fermé.La fonction libère les tableaux dynamiques d’octets
//	dans tous les t_block et libère aussi le tableau de
//	t_block dans la structure. Elle retourne 1 en cas de
//	succès et 0 sinon
int reconstruire_fich(t_reconstruction *rec, const char * nom_fichier) {
	int i = 0; //compteur des differents blocs dans le tableau de reconstruction
	int succes = 0; // 0 ->> la reconstruction n'est pas fini \
					  1 ->> la reconstruction est fini
	FILE * ptr_fich = NULL;
	ptr_fich = fopen(nom_fichier, "ab"); // ouvrir le nouveau fichier
	
	if (ptr_fich != NULL) {
		while (i < (rec->nbr_bloc_tot)) { //si on a fait la transcription de tous les blocs dans le \
											tableau de reconstruction
			fwrite((rec->ptr_bloc + i)->buffer, (rec->ptr_bloc + i)->taille_bloc, 1, ptr_fich);
			// ecriture du contenu du bloc dans le fichier
			i++; // incrementation du bloc observe
		}
		succes = 1; 
	}
	return succes;
}

// void free_rec_tab(t_reconstruction * reg)
//Description: libere le tableau dynamique et remet tous les 
//  membres à 0 ou NULL
void free_rec_tab(t_reconstruction * rec) {
	if (rec->ptr_bloc != NULL) {
		free(rec->ptr_bloc); rec->ptr_bloc = NULL;
	}
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
int pile_rec_pleine(t_reconstruction *rec);
int pile_rec_pleine(t_reconstruction *rec) {
	int plein = 0;
	if (rec->nbr_bloc_actu >= rec->nbr_bloc_tot) {
		plein = 1;
	}
	return plein;
}
/*===========================================================*/
