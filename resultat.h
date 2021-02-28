/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/* 	Projet		:	ELE216 - Laboratoire 1 
	Date		:	09 fevrier 2021 
	Par 		:	Gabriel Gandubert et Hugo Cusson-Bouthillier 
	Definition	:	Encapsulation des resultats
					recu par le module interface.h

	Contient:
		TYPES:
			Declaration des types opaques t_donnee_fichier et h_donnee_titre_fichier, 
			son handle pour tous les types de fichier : titres, noms et cotes.

		FONCTIONS:

		%% BASE DE DONNEES DES TITRES %%
			
			% Taille de la strcuture t_donnee_titre.
			size_t donnee_titre_sizeof(void);
			% Creation d'une structure pour les titres.
			h_donnee_titre donnee_titre_creer(	const char* const id_titre,
										const char* const titre,
										const char* const annee,
										const char* const genre,
										const char* const ligne
								 )
			% Liberation du contenu de la structure.
			void donnee_titre_liberer(void* donnee)
			% Retourne le numero de reference du titre.
			const char* const donnee_titre_get_id_titre(const h_donnee_titre const donnee)
			% Retourne le titre du film
			const char* const donnee_titre_get_titre(const h_donnee_titre const donnee)
			% Retourne l'annee de sortie du film.
			const char* const donnee_titre_get_annee(const h_donnee_titre const donnee)
			% Retourne la ligne de la base de donne d'ou elle provient.
			const char* const donnee_titre_get_ligne(const h_donnee_titre const donnee)
			% Ecriture dans un fichier texte des resultats des titres.
			void donnee_afficher_titre(		void* contexte, 
									const char* const cle, 
									void* valeur
						  )

		%% BASE DE DONNEES DES NOMS %%
			
			% Taille de la strcuture t_donnee_nom.
			size_t donnee_nom_sizeof(void);
			% Creation d'une structure pour les noms.
			h_donnee_nom donnee_nom_creer(const char* const id_nom,
											const char* const nom,
											const char* const id_titres,
											const char* const ligne
										 )
			% Liberation du contenu de la strucutre
			void                donnee_nom_liberer(void* donnee)
			% Retourne le numero de reference du titre.
			const char* const   donnee_nom_get_id_nom(const h_donnee_nom const donnee)
			Retourne le nom de l'acteur
			const char* const   donnee_nom_get_nom(const h_donnee_nom const donnee)
			% Retourne le numero de reference du titre.
			const char* const   donnee_nom_get_id_titres(const h_donnee_nom const donnee)
			% Retourne la ligne de la base de donne d'ou elle provient.
			const char* const   donnee_nom_get_ligne(const h_donnee_nom const donnee)
			% Ecriture dans un fichier texte des resultats des noms.
			void donnee_afficher_nom(		void* contexte, 
									const char* const cle, 
									void* valeur
						  )
			

		%% BASE DE DONNEES DES COTES %%
			
			% Taille de la strcuture t_donnee_cote.
			size_t donnee_cote_sizeof(void);
			% Creation d'une structure pour les cotes.
			h_donnee_cote	  donnee_cote_creer(		const char* const id_titre,
														const char* const cote,
														const char* const ligne
												 )
			% Liberation du contenu de la strucutre
			void                donnee_cote_liberer(void* donnee)
			% Retourne le numero de reference du titre.
			const char* const donnee_cote_get_id_titre(const h_donnee_cote const donnee)
			% Retourne la cote du film
			const char* const donnee_cote_get_cote(	const h_donnee_cote const donnee)
			% Retourne la ligne de la base de donne d'ou elle provient.
			const char* const donnee_cote_get_ligne(const h_donnee_cote const donnee)
			% Ecriture dans un fichier texte des resultats des cotes.
			void donnee_afficher_cote(		void* contexte, 
									const char* const cle, 
									void* valeur
						  )
			

		%% BASE DE DONNEES DES RESULTATS %%
			
			% Taille de la strcuture t_donnee_resultat.
			size_t donnee_resultat_sizeof(void);
			% Creation d'une structure pour les resultats.
			h_donnee_resultat	donnee_resultat_creer(void);
			%Liberation de la structure et de son contenu.
			void donnee_resultat_liberer(void* donnee);
			% Lecture de l'element identifiant de titre de la structure.
			const char* const donnee_resultat_get_id_titre(
											const h_donnee_resultat const donnee);
			% Lecture de l'element titre de la structure.
			const char* const donnee_resultat_get_titre(
											const h_donnee_resultat const donnee);
			% Lecture de l'element annee de la structure.
			const char* const   donnee_resultat_get_annee(
											const h_donnee_resultat const donnee);
			% Lecture de l'element nom de la structure.
			const char* const   donnee_resultat_get_nom(
											const h_donnee_resultat const donnee);
			% Lecture de l'element cote de la structure.
			const char* const   donnee_resultat_get_cote(
											const h_donnee_resultat const donnee);
			% Lecture de l'element ligne de titre de la structure.
			const char* const   donnee_resultat_get_ligne_titre(
											const h_donnee_resultat const donnee);
			% Ajoute l'element id_titre dans le contenu de la structure de donnees 
			% combinees.
			int donnee_resultat_set_id_titre(h_donnee_resultat donnee,
											const char* const id_titre);
			% Ajoute l'element titre dans le contenu de la structure de donnees 
			% combinees.
			int donnee_resultat_set_titre(h_donnee_resultat donnee, 
											const char* const titre);
			% Ajoute l'element annee dans le contenu de la structure de donnees 
			% combinees.
			int donnee_resultat_set_annee(h_donnee_resultat donnee,
											const char* const annee);
			% Ajoute l'element nom dans le contenu de la structure de donnees 
			% combinees.
			int donnee_resultat_set_nom(h_donnee_resultat donnee,
											const char* const nom);
			% Ajoute l'element cote dans le contenu de la structure de donnees 
			% combinees.
			int donnee_resultat_set_cote(h_donnee_resultat donnee, 
											const char* const cote);
			% Ajoute l'element ligne_titre dans le contenu de la structure de donnees
			% combinees.
			int donnee_resultat_set_ligne_titre(h_donnee_resultat donnee, 
										const char* const ligne_titre
									);
			% Ecrit le contenu d'une ligne dans le fichier texte de reference.
			void donnee_afficher_resultat(		void* contexte, 
										const char* const cle, 
										void* valeur
								  );
*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#ifndef __RESULTAT_H
#define __RESULTAT_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*							CONSTANTES                    								*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/**
 * @brief  constantes des titres des fichiers de resultat.
 */
static const char* FICHIER_ECRITURE_TITRE =	"titles.tsv";
static const char* FICHIER_ECRITURE_NOMS =	"names.tsv";
static const char* FICHIER_ECRITURE_COTES =	"ratings.tsv";

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/




/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*							Definitions de types          								*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/**
 * @brief  : Structure encapsulant les criteres passes en argument a l'executable.
 * @note   : HLR23 Definition "typedef" de la structure dans ce module et le 
 *			 contenu de la structure defini dans critere.c.
 */
typedef struct donnee_titre 	t_donnee_titre,		*h_donnee_titre;
typedef struct donnee_nom   	t_donnee_nom,		*h_donnee_nom;
typedef struct donnee_cote  	t_donnee_cote,		*h_donnee_cote;
typedef struct donnee_resultat	t_donnee_resultat,	*h_donnee_resultat;

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/




/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*							Debut des fonctions publiques								*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/**
 * @brief  Permet d'obtenir la taille de la strcuture t_donnee_titre.
 * @retval La taille de la structure t_donnee_titre.
 */
size_t donnee_titre_sizeof();

/**
 * @brief  Creation d'un pointeur vers la strucutre de donnees des titres
 * @note   HLR24: Encapsulation des resultats basee sur le fichier des titres.
 * @param  id_titre: numero d'identification du titre.
 * @param  titre: nom du titre du film.
 * @param  annee: annee de sortie du film.
 * @param  ligne: ligne complete de la base de donnees de reference.
 * @retval La structure allouee dynamiquement.
 */
h_donnee_titre		donnee_titre_creer(			const char* const id_titre,
											const char* const titre,
											const char* const annee,
											const char* const ligne
									  );

/**
 * @brief  Liberation de la structure et de son contenu.
 * @param  donnee: structure de la base de donnees des titres.
 * @retval None.
 */
extern void donnee_titre_liberer(void* donnee);

/**
 * @brief  Lecture de l'element identifiant du titre de la structure.
 * @param  donnee: structure de la base de donnees des titres.
 * @retval l'identifiant du titre.
 */
const char* const   donnee_titre_get_id_titre(	const h_donnee_titre const donnee);

/**
 * @brief  Lecture de l'element titre de la structure.
 * @param  donnee: structure de la base de donnees des titres.
 * @retval le titre.
 */
const char* const   donnee_titre_get_titre(		const h_donnee_titre const donnee);

/**
 * @brief  Lecture de l'element annee de la structure.
 * @param  donnee: structure de la base de donnees des titres.
 * @retval l'annee.
 */
const char* const   donnee_titre_get_annee(		const h_donnee_titre const donnee);

/**
 * @brief  Lecture de l'element ligne de la structure.
 * @param  donnee: structure de la base de donnees des titres.
 * @retval la ligne de la base de donnees de reference.
 */
const char* const	donnee_titre_get_ligne(		const h_donnee_titre const donnee);

/**
 * @brief  Ecrit le contenu d'une ligne dans le fichier texte de reference.
 * @note   HLR31: Visualisation des resultats dans un fichier texte de chaque structure.
 * @param  contexte: fichier texte ouvert dans lequel ecrire.
 * @param  cle: cle de la valeur a lire dans le Hmap.
 * @param  valeur: structure de type h_donnee_titre.
 * @retval None.
 */
extern void	donnee_afficher_titre(		void* contexte, 
										const char* const cle, 
										void* valeur
								  );

//----------------------------------------------------------------------------

//----------------------------------------------------------------------------

/**
 * @brief  Permet d'obtenir la taille de la strcuture t_donnee_nom.
 * @retval La taille de la structure t_donnee_nom.
 */
size_t donnee_nom_sizeof();

/**
 * @brief  Creation d'un pointeur vers la strucutre de donnees des noms
 * @note   HLR24: Encapsulation des resultats basee sur le fichier des noms.
 * @param  id_nom: numero d'identification du nom.
 * @param  nom: nom de l'acteur.
 * @param  id_titre: numeros d'identification des titres de films de carriere.
 * @param  ligne: ligne complete de la base de donnees de reference.
 * @retval La structure allouee dynamiquement.
 */
h_donnee_nom		donnee_nom_creer(			const char* const id_nom,
											const char* const nom,
											const char* const id_titre,
											const char* const ligne
									);

/**
 * @brief  Liberation de la structure et de son contenu.
 * @param  donnee: structure de la base de donnees des noms.
 * @retval None.
 */
extern void donnee_nom_liberer(void* donnee);

/**
 * @brief  Lecture de l'element identifiant du nom de la structure.
 * @param  donnee: structure de la base de donnees des noms.
 * @retval l'identifiant de reference du nom de l'acteur.
 */
const char* const   donnee_nom_get_id_nom(   	const h_donnee_nom const donnee);

/**
 * @brief  Lecture de l'element nom de la structure.
 * @param  donnee: structure de la base de donnees des noms.
 * @retval le nom de l'acteur.
 */
const char* const   donnee_nom_get_nom(      	const h_donnee_nom const donnee);

/**
 * @brief  Lecture de l'element identifiant de titre de la structure.
 * @param  donnee: structure de la base de donnees des noms.
 * @retval les identifiants des titres dans lesquels l'acteur a joue.
 */
const char* const   donnee_nom_get_id_titres(	const h_donnee_nom const donnee);

/**
 * @brief  Lecture de l'element ligne de la structure.
 * @param  donnee: structure de la base de donnees des noms.
 * @retval la ligne de la base de donnees de reference.
 */
const char* const   donnee_nom_get_ligne(		const h_donnee_nom const donnee);

/**
 * @brief  Ecrit le contenu d'une ligne dans le fichier texte de reference.
 * @note   HLR31: Visualisation des resultats dans un fichier texte de chaque structure.
 * @param  contexte: fichier texte ouvert dans lequel ecrire.
 * @param  cle: cle de la valeur a lire dans le Hmap.
 * @param  valeur: structure de type h_donnee_nom.
 * @retval None.
 */
extern void donnee_afficher_nom(	void* contexte, 
								const char* const cle, 
								void* valeur
								);

//----------------------------------------------------------------------------

/**
 * @brief  Permet d'obtenir la taille de la strcuture t_donnee_cote.
 * @retval La taille de la structure t_donnee_cote.
 */
size_t donnee_cote_sizeof();

/**
 * @brief  Creation d'un pointeur vers la strucutre de donnees des cotes
 * @note   HLR24: Encapsulation des resultats basee sur le fichier des cotes.
 * @param  id_titre: numero d'identification du titre.
 * @param  cote: cote du film de reference.
 * @param  ligne: ligne complete de la base de donnees de reference.
 * @retval La structure allouee dynamiquement.
 */
h_donnee_cote		donnee_cote_creer(			const char* const id_titre,
											const char* const cote,
											const char* const ligne
									 );

/**
 * @brief  Liberation de la structure et de son contenu.
 * @param  donnee: structure de la base de donnees des cotes.
 * @retval None.
 */
extern void donnee_cote_liberer(void* donnee);

/**
 * @brief  Lecture de l'element identifiant de titre de la structure.
 * @param  donnee: structure de la base de donnees des cotes.
 * @retval l'identifiant du titre evaluee par la cote.
 */
const char* const   donnee_cote_get_id_titre(	const h_donnee_cote const donnee);

/**
 * @brief  Lecture de l'element cote de la structure.
 * @param  donnee: structure de la base de donnees des cotes.
 * @retval la cote du film referencee.
 */
const char* const   donnee_cote_get_cote(	const h_donnee_cote const donnee);

/**
 * @brief  Lecture de l'element ligne de la structure.
 * @param  donnee: structure de la base de donnees des cotes.
 * @retval la ligne de la base de donnees de reference.
 */
const char* const   donnee_cote_get_ligne(		const h_donnee_cote const donnee);

/**
 * @brief  Ecrit le contenu d'une ligne dans le fichier texte de reference.
 * @note   HLR31: Visualisation des resultats dans un fichier texte de chaque structure.
 * @param  contexte: fichier texte ouvert dans lequel ecrire.
 * @param  cle: cle de la valeur a lire dans le Hmap.
 * @param  valeur: structure de type h_donnee_cote.
 * @retval None.
 */
extern void donnee_afficher_cote(	void* contexte, 
									const char* const cle, 
									void* valeur
									);

//----------------------------------------------------------------------------

/**
 * @brief  Permet d'obtenir la taille de la strcuture t_donnee_resultat.
 * @retval La taille de la structure t_donnee_resultat.
 */
size_t donnee_resultat_sizeof();

/**
 * @brief  Creation d'un pointeur vers la strucutre de la combinaison des bases de donnees.
 * @note   HLR24: Encapsulation des resultats basee sur les trois fichiers.
 * @retval La structure vide allouee dynamiquement.
 */
h_donnee_resultat	donnee_resultat_creer(void);

/**
 * @brief  Liberation de la structure et de son contenu.
 * @param  donnee: structure de la combinaison des trois bases de donnees.
 * @retval None.
 */
extern void donnee_resultat_liberer(void* donnee);

/**
 * @brief  Lecture de l'element identifiant de titre de la structure.
 * @param  donnee: structure de la combinaison des trois bases de donnees.
 * @retval la ligne de la base de donnees de reference.
 */
const char* const   donnee_resultat_get_id_titre(	const h_donnee_resultat const donnee);

/**
 * @brief  Lecture de l'element titre de la structure.
 * @param  donnee: structure de la combinaison des trois bases de donnees.
 * @retval le titre du film trouvee.
 */
const char* const   donnee_resultat_get_titre(		const h_donnee_resultat const donnee);

/**
 * @brief  Lecture de l'element annee de la structure.
 * @param  donnee: structure de la combinaison des trois bases de donnees.
 * @retval l'annee de sortie du film trouvee.
 */
const char* const   donnee_resultat_get_annee(		const h_donnee_resultat const donnee);

/**
 * @brief  Lecture de l'element nom de la structure.
 * @param  donnee: structure de la combinaison des trois bases de donnees.
 * @retval le nom le l'acteur trouvee.
 */
const char* const   donnee_resultat_get_nom(		const h_donnee_resultat const donnee);

/**
 * @brief  Lecture de l'element cote de la structure.
 * @param  donnee: structure de la combinaison des trois bases de donnees.
 * @retval la cote du film trouvee.
 */
const char* const   donnee_resultat_get_cote(		const h_donnee_resultat const donnee);

/**
 * @brief  Lecture de l'element ligne de titre de la structure.
 * @param  donnee: structure de la combinaison des trois bases de donnees.
 * @retval ligne de la base de donnee des titres du film trouvee.
 */
const char* const   donnee_resultat_get_ligne_titre(const h_donnee_resultat const donnee);

/**
 * @brief  Ajoute l'element id_titre dans le contenu de la structure de donnees combinees.
 * @note   HLR25: Mutateur des resultats de la recherche combinee.
 * @param  donnee: structure de la combinaison des trois bases de donnees.
 * @param  id_titre: identificateur du titre a ecrire dans la structure combinee.
 * @retval 1 si une erreur est detectee, sinon 0.
 */
int donnee_resultat_set_id_titre(	h_donnee_resultat donnee, const char* const id_titre);

/**
 * @brief  Ajoute l'element titre dans le contenu de la structure de donnees combinees.
 * @note   HLR25: Mutateur des resultats de la recherche combinee.
 * @param  donnee: structure de la combinaison des trois bases de donnees.
 * @param  titre: titre du film a ecrire dans la structure combinee.
 * @retval 1 si une erreur est detectee, sinon 0.
 */
int donnee_resultat_set_titre(		h_donnee_resultat donnee, const char* const titre);

/**
 * @brief  Ajoute l'element annee dans le contenu de la structure de donnees combinees.
 * @note   HLR25: Mutateur des resultats de la recherche combinee.
 * @param  donnee: structure de la combinaison des trois bases de donnees.
 * @param  annee: annee de sortie du film a ecrire dans la structure combinee.
 * @retval 1 si une erreur est detectee, sinon 0.
 */
int donnee_resultat_set_annee(		h_donnee_resultat donnee, const char* const annee);

/**
 * @brief  Ajoute l'element nom dans le contenu de la structure de donnees combinees.
 * @note   HLR25: Mutateur des resultats de la recherche combinee.
 * @param  donnee: structure de la combinaison des trois bases de donnees.
 * @param  nom: nom de l'acteur a ecrire dans la structure combinee.
 * @retval 1 si une erreur est detectee, sinon 0.
 */
int donnee_resultat_set_nom(		h_donnee_resultat donnee, const char* const nom);

/**
 * @brief  Ajoute l'element cote dans le contenu de la structure de donnees combinees.
 * @note   HLR25: Mutateur des resultats de la recherche combinee.
 * @param  donnee: structure de la combinaison des trois bases de donnees.
 * @param  cote: cote du film a ecrire dans la structure.
 * @retval 1 si une erreur est detectee, sinon 0.
 */
int donnee_resultat_set_cote(		h_donnee_resultat donnee, const char* const cote);

/**
 * @brief  Ajoute l'element ligne_titre dans le contenu de la structure de donnees combinees.
 * @note   HLR25: Mutateur des resultats de la recherche combinee.
 * @param  donnee: structure de la combinaison des trois bases de donnees.
 * @param  ligne_titre: ligne de la base de donnees titre a ecrire dans la structure.
 * @retval 1 si une erreur est detectee, sinon 0.
 */
int donnee_resultat_set_ligne_titre(h_donnee_resultat donnee, 
										const char* const ligne_titre
									);

/**
 * @brief  Ecrit le contenu d'une ligne dans le fichier texte de reference.
 * @note   HLR31: Visualisation des resultats dans un fichier texte de chaque structure.
 * @param  contexte: fichier texte ouvert dans lequel ecrire.
 * @param  cle: cle de la valeur a lire dans le Hmap.
 * @param  valeur: structure de type h_donnee_resultat.
 * @retval None.
 */
extern void donnee_afficher_resultat(		void* contexte, 
										const char* const cle, 
										void* valeur
								  );

//----------------------------------------------------------------------------

#endif //__RESULTAT_H