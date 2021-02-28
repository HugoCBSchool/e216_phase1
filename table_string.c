#include "table_string.h"

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*							TYPES ET STRUCTURES OPAQUES     							*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/**
 * @brief  	type t_table_critere est une table de strings utilisee dans l'implementation 
 * 			de la structure opaque t_critere
 */
struct table_string{
    unsigned int    nb_element;
    char**          table;
};

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*					IMPLEMENTATION FONCTIONS PUBLIQUES         							*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
h_table_string table_string_creer( const char* s_tuple, const char token){
	/**
	 *	La structure sousjascente de cette table de references est en realite un seul 
	 *  tableau de char contenant des '\0' entre les differentes strings. 
	 *  Le debut de la premiere string est stoque dans le premier pointeur du 
	 *  t_table_critere afin de pouvoir liberer sa memoire. Ainsi, la structure retournee 
	 *  contient des pointeurs sur toutes les strings, mais aussi un pointeur sur le 
	 *  tableau sousjascent.
	 */

	char* 			buffer	        =NULL;				//pour copier la string en argument
    char*			copy_tail       =s_tuple;   		//pour le premier char!=au token
	char*			str_extraite    =NULL;              //usage de strtok
    char            token_str[2]    ={token,'\0'};      //format c-string pour strtok
	h_table_string  nouveau         =NULL;				//pour la structure de retour


	if( !s_tuple || !*s_tuple || !token ){ 
        //validation des entrees
		return NULL;
	}


    //on trouve le debut du segment a copier, sil est nul on retourne.
	while( (*copy_tail) == token ){
        //on avance au prochain, on retourne en echec si valeur nule car juste des token
        if( !( *( ++copy_tail ) ) ){
            return NULL;
        }
    }

    //on alloue la memoire pour la copie du segment, renvoie null si echoue
	if(  !(  buffer = (char*) malloc( sizeof(char)*(strlen(copy_tail) + 1) )  )  ){
		return NULL;
	}

    //creation de la struct de retour et initialisation
    if( !( nouveau = (h_table_string)malloc(sizeof( t_table_string ) ) ) ){
        //sur echer, on libere tout ce quon a cree et on renvoie null
        free(buffer);
        buffer=NULL;
        return NULL;
    }
    nouveau->nb_element =0;
    nouveau->table      =NULL;

	//copie de la string, liberation du buffer sous echec et renvoi NULL
	if(!memcpy( buffer 
            ,   copy_tail
            ,   sizeof(char) * (strlen(copy_tail) + 1)  
        ) 
    ){
        free(nouveau);
		free(buffer);
        nouveau=NULL;
		buffer=NULL;
		return NULL;
	}

	//trouvons le premier string, si null, on libere la memoire et retourne NULL
	if( !(   str_extraite = strtok( buffer , token_str )   ) ){
        free(nouveau);
		free(buffer);
        nouveau=NULL;
		buffer=NULL;
		return NULL;
	}
	++(nouveau->nb_element); // on en a 1

	//on compte les token tant que le call reussit a en trouver
	while(  str_extraite=strtok(NULL,token_str) ){ 
        ++(nouveau->nb_element);	
    }

	//on alloue la memoire pour le tableau de references efface tout si erreur
	if(!(   nouveau->table = (char**)malloc( nouveau->nb_element * sizeof(char*))   )){
		free(buffer);
        free(nouveau);
        nouveau=NULL;
		buffer=NULL;
		return NULL;
	}

	//on popule
	nouveau->table[0] =buffer;		     //on memorise le premier token
    str_extraite = buffer+strlen(buffer);//on avance jusquau terminateur du premier token

	for( int i=1; i< nouveau->nb_element; ++i ){	
		while( !(   *( ++str_extraite   ) ) ){}	//on avance jusquau prochain token
		nouveau->table[i]=str_extraite;	        //on lajoute a la table
        while(      *(++str_extraite)   ){}     //on avance jusqua son null terminator		
	}		
	
	/**
	 * on nefface pas buffer car cest lui qui contient les string.
	 * on retourne nouveau. si vous avez suivi jusquici, vous comprenez que
	 * le premier pointeur de nouveau pointe sur le data te la table 
	 * en entier. Par consequent, le destructeur adequat (liberer_table_critere) saura
	 * comment liberer comme il se doit.
	 */
	return nouveau; 
}
//-------------------------------------------
void table_string_liberer(h_table_string table_str){
	/**
	 * Strategie: On doit faire 2 choses seulement.
	 * 	1- on libere le data sousjascent accessible via le premier pointeur du array
	 *  2- on libere la table de pointeur.
	 * Pour plus dinformation, voir implementation de creer_table_critere.
	 */

	if(table_str){
        if(table_str->table){
            free(table_str->table[0]);  //libere le data sousjascent
            table_str->table[0]=NULL;
            free(table_str->table);     //libere linterface
            table_str->table=NULL;
        }
	}
	free(table_str);//libere la table de pointeurs
	table_str=NULL;
}
//-------------------------------------------
unsigned int table_string_get_taille(h_table_string table_str){
	return (
		table_str
		?	table_str->nb_element
		:	0
	);
}
//-------------------------------------------
const char* table_string_get_element_n(h_table_string table_str, unsigned int n){
	return (	
		( table_str && ((table_str->nb_element) > n) )
		?	table_str->table[n]
		:	NULL	
	);
}
//-------------------------------------------
unsigned int table_string_foreach(	const h_table_string 	table_str	,
									const t_fp_foreach		f_do		, 
									void					*f_data	    ){
	if( !table_str || !table_str->table || !f_do ) return 0; //validation des args

	for( int i=0; i<table_str->nb_element; ++i) 
		f_do( table_str->table[i], f_data ); 				 //iteration

	return table_str->nb_element;							//retourne le nombre d'iter
}
//-------------------------------------------
unsigned int table_string_contient(	const h_table_string 	table_str	,
									const t_fp_comparer		f_comparer	,
									const char*				f_str2		){
	if( !table_str || !table_str->table || !f_comparer || !f_str2 ) 
		return 0; //validation des args

	unsigned int retour=0;

	for( int i=0; i<table_str->nb_element; ++i) 
		retour|=f_comparer(table_str->table[i], f_str2 ); 	 //iteration

	return retour;							 //retourne le nombre d'iter
}
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
