/*
	Projet		: ELE216 - Laboratoire 1
	Date		: 21 janvier 2021
	Par 		: Gabriel Gandubert et Hugo Cusson-Bouthillier
	Logiciel	: Sublime text & Eclipse
	Definition	: Encapsulation des criteres de recherche pour la base de donnee de films

	Contient:
		Structure des criteres qui permet de separer les types de criteres (commandes)
		La structure est defini ici, mais le "typedef" est dans le module critere.h.

		FONCTIONS PUBLIQUES:
			% Creation de la structure
			void creer_critere(void)

			% Changement du contenu
			void set_t(char* titre, pt_critere crit)
			void set_a(char* annees, pt_critere crit)
			void set_p(char* pers, pt_critere crit)
			void set_r(char* cote, pt_critere crit)

			% Lire les criteres de type -t, -a, -p et -r.
			char** get_t(pt_critere)
			char** get_a(pt_critere)
			char** get_p(pt_critere)
			char** get_r(pt_critere)
			
			% Lire le nombre de lignes dans les criteres de type -t, -a, -p et -r.
			int get_nb_t(pt_critere)
			int get_nb_a(pt_critere)
			int get_nb_p(pt_critere)
			int get_nb_r(pt_critere)

			% Liberation de la structure.
			void clear_critere(pt_critere crit)

		FONCTIONS PRIVEEs :
			% Copie une chaine de caracteres simple dans une chaine
			% de caractere double (separation par le caractere
			% CARATERE_SEPARATEUR_CRITERE).
			void copy_double_string(char* src, char** dest);
			
			% Determine le nombre de chaine de caratere separer 
			% par le caractere CARATERE_SEPARATEUR_CRITERE et determine 
			% la longeur de la plus longue chaine.
			char** argument_transfer(char* src, int* nb_string);
			
			% Liberation des criteres d'un argument de la strcuture.
			void free_critere(char** s_critere, int nb_critere);

*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

// Header file
#include "critere.h"


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*							CONSTANTES D'IMPLEMENTATION     							*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
// Caratere de separation des criteres.
#define 	C_CRITERE_TOKEN_C ','
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/




/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*							TYPES ET STRUCTURES OPAQUES     							*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/**
 * @note HLR03	: 	Structure de donnees permettant de contenir tous les arguments recu
 * 			  		dans le programme principal.
 */
struct critere
{
	h_table_string titre;
	h_table_string personne;
	h_table_string annee;
	h_table_string cote;
};
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/




/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*							DECLARATIONS FONCTIONS PRIVEES    							*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/**
 * @brief  	permet d'obtenir une reference sur la table de string du critere 
 * 			voulu de la structure de critere
 * @param  	critere:	la structure de critere
 * @param  	tag: 		le tag du critere voulu
 * @retval 	succes:		un pointeur sur la table de string du critere
 * 			echec:		NULL
 */
h_table_string critere_get_table_string(pt_critere 	const critere,t_tag_critere tag);

/**
 * @brief  	permet d'obtenir une reference sur le handle de la table de string du critere 
 * 			voulu de la structure de critere
 * @param  	critere:	la structure de critere
 * @param  	tag: 		le tag du critere voulu
 * @retval 	succes:		un pointeur sur la table de string du critere
 * 			echec:		NULL
 */
h_table_string* critere_select_table_string_handle(	pt_critere 	const critere	,
													t_tag_critere 	tag			);
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/




/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*							IMPLLEMENTATION FONCTIONS PUBLIQUES							*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
unsigned int tag_critere_valide(char tag){
	return	(	(tag==CHAR_TAG_ANNEE	)||
				(tag==CHAR_TAG_COTE		)||
				(tag==CHAR_TAG_PERSONNE	)||
				(tag==CHAR_TAG_TITRE	)	);
}
//-------------------------------------------
pt_critere critere_creer(void){
	//on utilise calloc pour avoir 1 espace contigu de taille de la struct tout a 0
	//sil plante il va renvoyer NULL par lui meme
	return (pt_critere)calloc( 1 , sizeof(struct critere) );
}
//-------------------------------------------
extern void critere_liberer(void* critere)
{
	//libere le data
	table_string_liberer(((pt_critere)critere)->annee);
	table_string_liberer(((pt_critere)critere)->personne);
	table_string_liberer(((pt_critere)critere)->cote);
	table_string_liberer(((pt_critere)critere)->titre);

	//libere le pointeur
	free((pt_critere)critere);
	critere=NULL;
}
//-------------------------------------------
unsigned int critere_set(	pt_critere 	const 	critere			,
							const char* 		s_tuple_critere	,
							t_tag_critere 		tag				)
{	
	h_table_string* selection=NULL;

	//validation des entrees et de la selection
	if(	!s_tuple_critere 	|| !*s_tuple_critere	|| !critere	 		||
		!( selection=critere_select_table_string_handle(critere,tag) )	){
		return 0;
	}

	//on reset la table de string
	if(*selection){
		table_string_liberer(*selection);
	}

	//retourne le booleen du succes de lallocation
	return (((*selection)=table_string_creer(s_tuple_critere,C_CRITERE_TOKEN_C)) != NULL);
}
//-------------------------------------------
unsigned int critere_get_taille(	t_tag_critere 		tag		, 
									pt_critere 	const 	critere	){
	return (unsigned int)table_string_get_taille(critere_get_table_string(critere,tag));
}
//-------------------------------------------
const char* critere_get_element_i(	pt_critere 	const 	critere	, 
									t_tag_critere 		tag		, 
									unsigned int 		i		){
	//on transfert la validation aux deux fonctions secures ci dessous
	return table_string_get_element_n(critere_get_table_string( critere, tag ) , i );
}
//-------------------------------------------
unsigned int critere_foreach( 	pt_critere 	const 	critere		,
								const t_fp_foreach 	f_do		,
								t_tag_critere		tag			, 	
								void 				*f_data		)
{
	//selection du critere
	h_table_string* selection =critere_select_table_string_handle(critere,tag);

	return (
		( selection && *selection )						  /* validation 			  */
		?	table_string_foreach(*selection,f_do,f_data) /* iter et retourne nb iter */
		:	0											  /* aucunes iter retourne 0  */
	);
}
//-------------------------------------------
unsigned int critere_contient( 	pt_critere 	const 		critere	, t_tag_critere tag,
								const t_fp_comparer		f_comparer	,
								const char*				f_str2		){
	h_table_string* selection=critere_select_table_string_handle(critere,tag);

	return (
		( selection && *selection )						 		/* validation 				 */
		?	table_string_contient(*selection,f_comparer,f_str2) /* iter et retourne nb iter */
		:	0											 		/* aucunes iter retourne 0  */
	);
}
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/




/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*					IMPLEMENTATION FONCTIONS PRIVEES           							*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
h_table_string 	critere_get_table_string(pt_critere const critere,t_tag_critere tag){
	return *critere_select_table_string_handle(critere,tag);
}
//-------------------------------------------
h_table_string* critere_select_table_string_handle(
	pt_critere 	const critere,
	t_tag_critere tag
){
	if(!critere||!tag_critere_valide(tag)){
		return NULL;
	}
	switch(tag){
		case tag_titre:		return &(critere->titre);
		case tag_cote:		return &(critere->cote);
		case tag_personne:	return &(critere->personne);
		case tag_annee:		return &(critere->annee);
		default:			return NULL;
	}
}
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


