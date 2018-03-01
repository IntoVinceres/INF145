/*----------------------------------------------------*/
/* 	par hugues saulnier (r�vision E. Th�, hiver 2018) */
/*----------------------------------------------------*/
/*
je ne me sers que de l'infame rand dans cette implementation
notre mersenne twister nous donnerais des capacit�s bien plus grandes
pour varier les distributions (par exemple utiliser une normale pour
la taille des lectures de bytes) mais j'ai choisi de m'en passer.
*//*==========================================================*/
#include "m_decoupage.h"

/*==========================================================*/
// on conserve 256 caracteres maximum du nom du fichier
#define TAILLE_NOM 257

// shift utilis� dans la construction d'un identifiant de fichier
#define DECALAGE 16

/*==========================================================*/
// type priv� g�rant l'acc�s � un fichier pour son d�coupage
typedef struct {

	// infos sur le fichier obtenu lors de l'ajout
	FILE * fichier;               //pointeur du fopen
	unsigned int id_fichier;
	char nom_fichier[TAILLE_NOM]; //simple strcpy() de son nom
	int taille_fichier;           //calcul�e avec fonctions de fichiers

								  // infos mises � date lors de l'�mission des blocs
	int taille_restante;          //initialement = taille_fichier
	int nb_blocks_emis;           //initialement = 0

} t_file_blocks;
/*==========================================================*/

/*==========================================================*/
// les variables priv�es du module 

//  tableau priv� des t_file_blocks
static t_file_blocks tablo_fichiers[MAX_FICHIERS_DECOUPAGE];

// elle est mise � date lorsqu'on ajoute ou retire un fichier
// c'est la valeur retourn�e par get_nb_fichiers
static int fichiers_en_traitement = 0;
/*==========================================================*/



/*==========================================================*/
//  fonctions priv�es factorisant le proc�d� de d�coupage
/*==========================================================*/


/*==========================================================*/
// construire un t_block vide
// dont tous les membres sont nuls
static t_block block_vide(void);
/*==========================================================*/
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
/*==========================================================*/

/*==========================================================*/
//  trouver la une position libre dans  tablo_fichiers
//  retourne une position libre ou -1
static int get_position_libre(void);
/*==========================================================*/
static int get_position_libre(void) {
	int i, depart;

	// STRAT�GIE
	// � partir d'une position al�atoire, on se d�place dans tablo_fichiers  
	// en cherchant le premier fichier dont l'identifiant est 0
	depart = (unsigned)((1.0*rand()) / RAND_MAX) * MAX_FICHIERS_DECOUPAGE;

	for (i = 0; i < MAX_FICHIERS_DECOUPAGE; ++i) {
		int position;
		position = (depart + i) % MAX_FICHIERS_DECOUPAGE;
		if (tablo_fichiers[position].id_fichier == 0) return position;
	}
	return -1;
}
/*==========================================================*/

/*==========================================================*/
//  chercher  un position dans tablo_fichiers dont le d�coupage du fichier
// n'est pas termin�  elle retourne la  position trouv�e  ou -1 sinon
static int get_fichier_aleatoire(void);
/*==========================================================*/
static int get_fichier_aleatoire(void) {
	int i, depart;

	// STRAT�GIE
	// � partir d'une position al�atoire, on se d�place dans tablo_fichiers en cherchant 
	// le premier fichier dont la taille restante est non-nulle
	depart = (unsigned)((1.0*rand()) / RAND_MAX) * MAX_FICHIERS_DECOUPAGE;

	for (i = 0; i < MAX_FICHIERS_DECOUPAGE; ++i) {
		int position;
		position = (depart + i) % MAX_FICHIERS_DECOUPAGE;
		if (tablo_fichiers[position].taille_restante > 0) return position;
	}
	return -1;
}
/*==========================================================*/

/*==========================================================*/
//  trouver la  position d'un identifiant dans le tableau de fichiers en traitement
//  retourne une position du tableau ou -1
static int get_position_id(unsigned int f_identifiant);
/*==========================================================*/
static int get_position_id(unsigned int f_identifiant) {
	int i;

	for (i = 0; i < MAX_FICHIERS_DECOUPAGE; ++i) {
		if (f_identifiant == tablo_fichiers[i].id_fichier) return i;
	}
	return -1;
}
/*==========================================================*/

/*==========================================================*/
//  tester si le nom d'un fichier  est present  dans tablo_fichiers 
//  retourne 0 ou 1
static int tester_nom_fichier(const char * nom_fichier);
/*==========================================================*/
static int tester_nom_fichier(const char * nom_fichier) {
	int i;

	for (i = 0; i < MAX_FICHIERS_DECOUPAGE; ++i) {
		if (strcmp(nom_fichier, tablo_fichiers[i].nom_fichier) == 0) return 1;
	}
	return 0;
}

/*==========================================================*/
//  cr�er un nouveau identifiant de fichier qui n'est pas actif  
static unsigned int get_nouvel_id(void);
/*==========================================================*/
static unsigned int get_nouvel_id(void) {
	unsigned int nouveau;

	// probabilit� quasi nulle d'obtenir une valeur d�j�
	// utilis�e mais on teste tout de m�me avec la boucle
	do {
		nouveau = (rand() << DECALAGE);
		// le typecast �vite un warning
		nouveau += (unsigned)((1.0*nouveau) / RAND_MAX) * rand();
	} while (get_position_id(nouveau) > -1);

	return nouveau;
}
/*==========================================================*/

/*==========================================================*/
//  initialiser une case fichier dans tablo_fichiers
//  c'est annuler  tous les membres du t_file_blocks 
static void mettre_fichier_null(int position);
/*==========================================================*/
static void mettre_fichier_null(int position) {
	tablo_fichiers[position].fichier = NULL;
	tablo_fichiers[position].id_fichier = 0;
	tablo_fichiers[position].nb_blocks_emis = 0;

	// annuler ici c'est mettre la string vide
	tablo_fichiers[position].nom_fichier[0] = 0;

	tablo_fichiers[position].taille_fichier = 0;
	tablo_fichiers[position].taille_restante = 0;
}
/*==========================================================*/
/*==========================================================*/

// LES D�FINITIONS DES FONCTIONS D'INTERFACE

/*==========================================================*/

/*==========================================================*/
//  initialiser le module de d�coupage
/*==========================================================*/
void init_decoupage(void) {
	int i;

	// STRATEGIE 
	// toutes les cases de tablo_fichiers sont
	// mises dans un �tat vide (propri�t�s nulles)
	// le nombre de fichiers est remis � 0
	// initialiser rand() pour obtenir des id_fichier originaux
	// ou des positions al�atoires dans tablo_fichiers
	for (i = 0; i < MAX_FICHIERS_DECOUPAGE; ++i) {
		mettre_fichier_null(i);
	}

	fichiers_en_traitement = 0;

	// le typecast �vite un warning
	srand((unsigned)time(0));
}
/*==========================================================*/

/*==========================================================*/
//  connaitre le nombre de fichiers en traitement dans le module 
/*==========================================================*/
int get_nb_fichiers(void) {
	// simple retour du compteur statique
	return fichiers_en_traitement;
}
/*==========================================================*/

/*==========================================================*/
//  tester si un  identifiant est actuellement valide
/*==========================================================*/
int id_fichier_valide(unsigned int f_identifiant) {
	// STRATEGIE 
	// tester si sa position existe dans tablo_fichiers
	return (get_position_id(f_identifiant) == -1) ? 0 : 1;
}
/*==========================================================*/

/*==========================================================*/
// connaitre la taille d'un fichier en traitement
/*==========================================================*/
int get_taille_fichier(unsigned int f_identifiant) {
	int p;

	// STRATEGIE  
	// obtenir sa position  dans le tableau des fichiers
	// retourner la taille du fichier ou 0
	p = get_position_id(f_identifiant);
	return (p == -1) ? -1 : tablo_fichiers[p].taille_fichier;
}
/*==========================================================*/

/*==========================================================*/
// connaitre la taille restant � traiter  dans un fichier
/*==========================================================*/
int get_taille_restante(unsigned int f_identifiant) {
	int p;

	// STRATEGIE 
	// obtenir sa position  dans le tableau des fichiers
	// retourner la taille restante du fichier ou -1
	p = get_position_id(f_identifiant);
	return (p == -1) ? -1 : tablo_fichiers[p].taille_restante;
}
/*==========================================================*/

/*==========================================================*/
// obtenir le nombre de blocs �mis � date de ce fichier par le module
/*==========================================================*/
int get_nb_blocs_emis(unsigned int f_identifiant) {
	int p;

	// STRATEGIE 
	// obtenir sa position dans le tableau des fichiers
	// retourner le nombre de blocs �mis ou 0
	p = get_position_id(f_identifiant);
	return (p == -1) ? 0 : tablo_fichiers[p].nb_blocks_emis;

}
/*==========================================================*/

/*==========================================================*/
/*
ajouter un fichier au  module de d�coupage

PARAMETRE(s): le nom du fichier � traiter

SORTIE: l'identifiant unique du fichier ( autre que 0 )
son handle qui doit �tre conserv� pour obtenir des infos
sur l'�tat actuel du traitement du fichier
le fichier pourra �tre d�coup� en blocs
0 sinon

SPECS:  C'est une erreur de vouloir ouvrir un fichier d�ja ouvert
le module le refuse
*/
unsigned int ajouter_fichier(const char * nom_fichier) {
	FILE * lecture;
	int position = 0;

	// si le fichier est en traitement retour 0
	if (tester_nom_fichier(nom_fichier)) return 0;

	// si on a place pour un nouveau fichier retour 0
	position = get_position_libre();
	if (position == -1) return 0;

	// si on est incapable d'ouvrir le fichier retour 0
	lecture = fopen(nom_fichier, "rb");
	if (lecture == NULL) return 0;

	// le fichier est accept�, on remplit le t_file_blocks
	tablo_fichiers[position].fichier = lecture;
	tablo_fichiers[position].id_fichier = get_nouvel_id();
	tablo_fichiers[position].nb_blocks_emis = 0;
	strncpy(tablo_fichiers[position].nom_fichier, nom_fichier, TAILLE_NOM - 1);

	// obtenir la taille du fichier
	fseek(lecture, 0, SEEK_END);
	tablo_fichiers[position].taille_fichier = ftell(lecture);
	fseek(lecture, 0, SEEK_SET);

	// initialement les deux tailles sont �gales
	tablo_fichiers[position].taille_restante = tablo_fichiers[position].taille_fichier;

	// ajouter 1 au nombre de fichiers
	fichiers_en_traitement += 1;

	//retourner son identifiant unique
	return tablo_fichiers[position].id_fichier;
}
/*==========================================================*/

/*==========================================================*/
// retirer un fichier compl�tement d�coup� de tablo_fichiers
/*==========================================================*/
int retirer_fichier(unsigned int f_identifiant) {
	int p;

	// STRATEGIE
	// si l'identifiant est absent return 0
	// si le decoupage n'est pas fini, return 0
	// sinon initialiser la position dans tablo_fichiers,
	//       fermer le fichier,
	//       d�cr�menter fichiers_en_traitement
	//       retour de 1
	p = get_position_id(f_identifiant);
	if (p == -1) return 0;
	if (tablo_fichiers[p].taille_restante) return 0;
	fclose(tablo_fichiers[p].fichier);
	mettre_fichier_null(p);
	fichiers_en_traitement -= 1;

	return 1;
}
/*==========================================================*/

/*==========================================================*/
/* STRAT�GIE
checher un fichier qui peut encore emettre un bloc (selection aleatoire)
si non return d'un bloc vide
si oui un vrai bloc sera emis

on va lire un bloc de bytes du fichier ( ce peut etre le dernier)
puis on ajuste les membres du bloc et du fichier
/*==========================================================*/
t_block get_bloc(void) {

	t_block nouveau;         // le variable de retour
	int position_fichier;    // le choix du fichier sera al�atoire
	int taille_alea, taille;
	int taille_lecture;      // pour le nombre de bytes lus  dans le fichier

							 // buffer local pour la lecture dans le fichier
	unsigned char local[TAILLE_MAX_BLOCK];

	nouveau = block_vide(); // initialement tous ses champs nuls

							// chercher aleatoirement  un fichier
	position_fichier = get_fichier_aleatoire();
	// si y'en a pas retour du bloc vide
	if (position_fichier == -1) return nouveau;

	// simple verification en debogage, cette ligne deviendra 
	// inutile apres les tests complets
	assert(tablo_fichiers[position_fichier].taille_restante > 0);

	// fixer l'identifiant du nouveau bloc
	nouveau.f_identifiant = tablo_fichiers[position_fichier].id_fichier;

	// fixer le num�ro du nouveau bloc
	// remarquez ici le ++ en postfixe, je ne m'en sers que dans des cas precis
	nouveau.num_bloc = tablo_fichiers[position_fichier].nb_blocks_emis++;

	// le cas du dernier bloc, lecture de tous les bytes qui restent
	if (tablo_fichiers[position_fichier].taille_restante < TAILLE_MAX_BLOCK) {
		taille = tablo_fichiers[position_fichier].taille_restante;
		taille_lecture = fread(local, 1, taille, tablo_fichiers[position_fichier].fichier);
	}
	// sinon lecture d'un nombre aleatoire de bytes 
	else {
		taille_alea = TAILLE_MIN_BLOCK
			+ (int)(((1.0*rand()) / RAND_MAX) * (TAILLE_MAX_BLOCK - TAILLE_MIN_BLOCK));
		taille_lecture = fread(local, 1, taille_alea, tablo_fichiers[position_fichier].fichier);
	}

	// on termine le travail :
	// 1 obtenir la memoire dynamique du nouveau bloc
	assert(nouveau.buffer = malloc(taille_lecture + 4));

	// 2 ajuster la taille restante du fichier
	tablo_fichiers[position_fichier].taille_restante = tablo_fichiers[position_fichier].taille_fichier
		- ftell(tablo_fichiers[position_fichier].fichier);
	// 3 fixer la taille du nouveau bloc
	nouveau.taille_bloc = taille_lecture;

	// 4 copier les bytes du buffer local dans le buffer du nouveau bloc
	memcpy(nouveau.buffer, local, taille_lecture);

	// 5 test de fixation du bloc final
	if (tablo_fichiers[position_fichier].taille_restante == 0) nouveau.bloc_final = 1;

	// le nouveau bloc est retourn�
	return nouveau;
}
/*==========================================================*/

/*==========================================================*/
// Cette proc�dure ne fait que donner un affichage simple
// des propri�t�s d'un bloc re�u en r�f�rence
/*==========================================================*/
void print_bloc(const t_block * p_bloc) {

	printf("\nBloc #%u ", p_bloc->num_bloc);
	print_etat_fichier(p_bloc->f_identifiant);
	(p_bloc->bloc_final == (unsigned char)'1') ? printf(" ( FINAL )") : 0;
	printf("\n\t>ID : %u", p_bloc->f_identifiant);
	printf("\t>Taille : %u", p_bloc->taille_bloc);
	printf("\t>Adresse : %X", p_bloc->buffer);
	printf("\n");

	return;
}
/*==========================================================*/

/*==========================================================*/
// Cette proc�dure ne fait que donner un affichage simple de 
// l'�tat d'un fichier dont vous avez l'identifiant unique.
// faites des printf expliquant les r�sultats des informations
// obtenues avec l'identifiant re�u
/*==========================================================*/
void print_etat_fichier(unsigned int f_identifiant) {
	(id_fichier_valide(f_identifiant) == 1) ? printf("( VALIDE )") : printf(" ( NON_VALIDE )");
	return;
}
/*==========================================================*/
/*==========================================================*/


