/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*
	Projet		: ELE216 - Laboratoire 1
	Date		: 21 janvier 2021
	Par 		: Gabriel Gandubert et Hugo Cusson-Bouthillier
	Definition	: Encapsulation des criteres recu par le programme principal

	Contient:
		TYPES:
			Declaration de la structure opaque t_critere et son handle, pt_critere.
			
			Declaration du type enumere t_tag definissant les types de tag valides comme
				precurseurs d'arguments de commande

		FONCTIONS:
			unsigned int 	tag_valide(t_tag tag) 			--validatrice de t_tag

			pt_critere 		creer_critere(void)				--constructrice de t_critere
			void 			clear_critere(pt_critere crit)  --destructrice de t_critere
			
			unsigned int    set_critere(					--mutatrice de t_critere
				const char* 		s_tuple_critere,
				t_tag				tag,
				const pt_critere	critere 
			)												

			const char*		get_critere_index_i(			--informatrice indicielle
				const pt_critere    critere,
				t_tag				tag,
				unsigned int 		index
			)

			unsigned int 	critere_foreach(				--iteratrice fonctionnelle de 
				const pt_critere	critere,					t_critere
				t_tag 				tag,
				void 				(*pf)(const char*,void*), 	
				const void 			*pf_data
			)
*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


#ifndef __CRITERE_H
#define __CRITERE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "table_string.h"

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*							CONSTANTES                    								*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/**
 * @brief  constantes exposant les characteres en bijection avec les t_tag valides
 */
#define CHAR_TAG_TITRE 		't'
#define CHAR_TAG_PERSONNE 	'p'
#define CHAR_TAG_ANNEE 		'a'
#define CHAR_TAG_COTE 		'r'


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/




/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*							Definitions de types          								*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


/**
 * @brief  : Structure encapsulant les criteres passes en argument a l'executable.
 * @note   : HLR04 Definition "typedef" de la structure dans ce module et le contenu de                     
 * 			 la structure defini dans critere.c.
 */
typedef struct critere 	t_critere	,
 						*pt_critere	;	 // Pointeur vers le type t_critere


/**
 * @brief  type enumere pour encapsuler le tag d'argument de commandes au programme.
 * 		   Chaque element est en bijection avec la valeur (int) du (char) associé
 * 		   pour permettre la comparaison ternaire standard.
 */
typedef enum tag_critere{
	tag_titre		= CHAR_TAG_TITRE,
	tag_personne	= CHAR_TAG_PERSONNE,
	tag_annee		= CHAR_TAG_ANNEE,
	tag_cote		= CHAR_TAG_COTE
}t_tag_critere; 
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/




/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*							Debut des fonctions publiques								*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/**
 * @brief  informatrice permettant de valider qu'un char est un tag valide
 * @retval 1 si le tag est valide, 0 sinon
 */
unsigned int tag_critere_valide(char tag);

/**
 * @brief  Constructeur dynamique de t_critere. Il en renvoit l'adresse dans un pointeur.
 * @note   HLR05: Fonction publique permettant d'allouer dynamiquement la structure HLR03.
 * @retval Un pointeur sur la structure creee et vide. Sil echoue, renvoie NULL.
 */
pt_critere critere_creer(void);

/**
 * @brief  Destructeur permettant de liberer la memoire allouee par creer_critere.
 * @note   HLR05: Fonction publique permettant d'allouer dynamiquement la structure HLR03.
 * @param  critere: une reference sur l'instance a detruire.
 * @retval None
 */
extern void	critere_liberer(void* critere);


/**
 * @brief 	fonction permettant de remplacer le contenu d'un critere associe au tag donne
 * 				dans la structure. Sil est vide, il est popule.
 * @note  	HLR06: Serie de fonction permettant d'ajouter des donnees dans la 
 * 				strcuture des criteres.
 *   
 * @param  	s_tuple_critere:	adresse de la string c-style contenant toutes les 
 * 									valeurs a ajouter au critere specifier
 * @param  	critere: 			le critere a muter avec l'appel de fonction
 * @param	tag: 				le t_tag du critere a muter. Le t_tag peut resulter du 
 * 									typecast du char extrait du command line en t_tag.
 * 
 * @retval  1 lors de succes, 0 sinon
 */
unsigned int critere_set(	pt_critere const    critere			,
							const char* 		s_tuple_critere	,
							t_tag_critere		tag				);


/**
 * @brief  
 * @note   HLR08	: Permet de lire les valeurs dans la structure.
 * @param  tag		: le tag du critere dont on veut connaitre le nombre.
 * @param  critere	: une reference sur le critere a observer.
 * @retval Le nombre d'elements du tag donne contenu dans la structure donnee,
 * 			mauvais arguments engendrent retour nul.
 */
unsigned int critere_get_taille( t_tag_critere tag	, pt_critere const critere); 


/**
 * @brief  fonction permettant d'observer un critere de tag donne par indexe
 * @note   HLR08	: Permet de lire les valeurs dans la structure.
 * @param  tag		: le tag des criteres cibles par l'appel
 * @param  i		: l'index du critere de tag donne a renvoyer 
 * @param  critere: : reference sur la structure sous observation
 * @retval une reference constante sur le string du critere demande, NULL si erreur.
 */
const char* critere_get_element_i(	pt_critere 	const   critere	, 
									t_tag_critere 		tag		, 
									unsigned int 		i		);


/**
 * @brief  	Fonction permettant d'iterer sur tous les criteres du meme tag de la structure 
 * 			fournie en appelant la fonction pf donnée en référence en lui donnant comme 
 * 			premier argument le critere de l'iteration actuelle.
 * 
 * @note   	HLR08	: Permet de lire les valeurs dans la structure.
 * 
 * @param  	tag		: le tag des criteres sur lesquels iterer 
 * @param   critere : une reference constante sur la structure ciblee par l'iteration
 * @param   f_do	: reference sur une fonction a appeler lors de chaque iteration
 * 						Elle prend en premier argument une string c-style constante pour
 * 							recevoir le critere de l'iteration actuelle.
 * 						Elle prend en second argument une reference void
 * 							dont le type est implicite a l'implementation de la fonction 
 * 							appelante de sorte que celle-ci puisse manipuler son etat de 
 * 							fonctionnement et son retour.
 * @param	f_data	: l'adresse de la plage de memoire donnee en second parametre a la 
 * 						fonction pf, dont la structure est implicite a l'implementation 
 * 						de l'argument fonctionnel pf. Elle peut etre nule, tant pour 
 * 						autant que la fonction pf ne tente pas d'y acceder. 
 * 						Sinon, la responsabilite de gestion de cette plage est celle de
 * 						l'appelant de critere_foreach.
 * @retval Elle retourne le nombre d'iterations completees avec succes.
 */
unsigned int critere_foreach( 	pt_critere 	const   critere		,
								const t_fp_foreach 	f_do		,
								t_tag_critere		tag			, 	
								void 				*f_data		);

/**
 * @brief  	Fonction permettant d'iterer sur tous les string de la structure en 
 *  		comparant avec une string passee en argument pour voir si la table contient
 * 			un string qui contient celle donnee en argument.
 * @param   critere     :   une reference constante sur le critere sur laquel iterer
 * @param   tag			:   le tag permettant de selectionner le critere a tester
 * @param   f_do        :   reference sur une fonction de type t_fp_foreach a appeler sur
 *                          chaque element de la table
 * 						    -   Elle prend en premier argument une string c-style constant
 * 							    pour recevoir le critere de l'iteration actuelle.
 * 						    -   Elle prend en second argument une seconde string
 * 								sur laquelle comparer.
 * @param	f_str2	    :   la seconde string avec comparer la collection.
 * @retval Elle retourne la reduction OR de toutes les operations de comparaison.
 */
unsigned int critere_contient( 	pt_critere const        critere	, 
								t_tag_critere 			tag,
								const t_fp_comparer		f_comparer	,
								const char*				f_str2		);
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#endif
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/