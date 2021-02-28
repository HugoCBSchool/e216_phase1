/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/* 	Projet		:	ELE216 - Laboratoire 1 
	Date		:	21 janvier 2021 
	Par 		:	Gabriel Gandubert et Hugo Cusson-Bouthillier 
	Definition	:	Encapsulation des criteres
					recu par le programme principal

	Contient:
		FONCTION:
			int recherche_fichier(							--Recherche de criteres dans
				char* nom_fichier, 							  un fichier
				pt_critere critere
			)
*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#ifndef __INTERFACE_H
#define __INTERFACE_H
#define __GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "critere.h"
#include "parser.h"
#include "hashmap.h"
#include "debug_include.h"
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*							CONSTANTES D'IMPLEMENTATION     							*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/* 
 * @note	HLR15 : Ouverture possible uniquement pour certains fichiers specifiques.
 */
// Constantes des noms des fichiers de reference.
static const char FICHIER_TITRE[]	= "./data/bd-films-imdb/title_basics.tsv";
static const char FICHIER_NOMS[]	= "./data/bd-films-imdb/name_basics.tsv";
static const char FICHIER_COTE[]	= "./data/bd-films-imdb/title_ratings.tsv";

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*							Debut des fonctions publiques								*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


/**
 * @brief 	fonction permettant de trouver les lignes correspondantes aux criteres
 *				dans le fichier de base de donnees referencee.
 * @note  	HLR10: Fonction permettant de lire dans un fichier texte les criteres.
 *   
 * @param  	nom_fichier:		L'adresse vers le fichier de base de donnee a balayer
 									afin de trouver les criteres. seul certains fichiers
 									peuvent acceptees
 * @param  	critere: 			les criteres a trouver dans le fichier texte.
 * 
 * @retval  le hashmap des resultats de recherche dans le fichier
 */
h_hmap recherche_fichier(const char* const nom_fichier, pt_critere critere);

unsigned int analyser_resultats(
	pt_critere 	const critere,
	h_hmap 		const map_nom, 
	h_hmap 		const map_titre, 
	h_hmap 		const map_cote
);

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#endif
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/