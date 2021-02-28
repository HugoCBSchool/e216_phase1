/*
    Projet      : ELE216 - Laboratoire 1
    Date        : 10 fevrier 2021
    Par         : Gabriel Gandubert et Hugo Cusson-Bouthillier
    Logiciel    : Sublime text & Eclipse
    Definition  : Comparaison des lignes de donnees des bases de donnees de films et des
				  criteres de recherche de l'utilisateur.

    Contient:

        FONCTIONS PUBLIQUES:
			% Comparaison entre une ligne du fichier des titres et les criteres.
        	unsigned int comparer_donnee_titre_critere( 
			    h_donnee_titre const donnee,
			    pt_critere const critere 
			)
            % Comparaison entre une ligne du fichier des cotes et les criteres.
            unsigned int comparer_donnee_cote_critere(  
			    h_donnee_cote const donnee,
			    pt_critere const critere
			)
			% Comparaison entre une ligne du fichier des noms et les criteres.
			unsigned int comparer_donnee_nom_critere(
			    h_donnee_nom    const donnee,
			    pt_critere      const critere
			)
*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

// Header file
#include "comparaison.h"


// Separateur des intervales d'annees provenant des criteres de l'utilisateur.
#define TOKEN_INTERVAL_ANNEE ':'

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*                          IMPLLEMENTATION FONCTIONS PUBLIQUES                         */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
unsigned int comparer_donnee_titre_critere( 
    h_donnee_titre const donnee,
    pt_critere const critere 
){
    // Les donnees et criteres ne doivent pas etre nul.
    if(!donnee || !critere){
        return 0;
    }
    return (
        critere_contient(   
            critere, tag_titre, &str1_dans_str2 ,
            donnee_titre_get_titre(donnee)       
        )
        &&
        critere_contient(
            critere, tag_annee, &annee_dans_interval,
            donnee_titre_get_annee(donnee)
        )             
    );
}

//----------------------------------------------------------------------------------------

unsigned int comparer_donnee_cote_critere(  
    h_donnee_cote const donnee,
    pt_critere const critere
){
    // Les donnees et criteres ne doivent pas etre nul.
    if(!donnee || !critere){
        return 0;
    }

    // Verifier s'il y a au moins une cote dans les criteres.
    if(!critere_get_taille(tag_cote,critere)){
        return 0;
    }

    // Comparaison des criteres.
    return critere_contient(   
        critere, 
        tag_cote, 
        &str2_dans_str1,
        donnee_cote_get_cote(donnee)
    );
}

//----------------------------------------------------------------------------------------

unsigned int comparer_donnee_nom_critere(
    h_donnee_nom    const donnee,
    pt_critere      const critere
){
    // Les donnees et criteres ne doivent pas etre nul.
    if( !donnee|| !critere ){
        return 0;
    }

    // Verifier s'il y a au moins un nom dans les criteres.
    if(!critere_get_taille(tag_personne,critere)){
        return 0;
    }

    // Comparaison des criteres.
    return critere_contient( 
        critere, 
        tag_personne,
        &str1_dans_str2,
        donnee_nom_get_nom(donnee)
    );

}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*                  IMPLEMENTATION FONCTIONS PRIVEES                                    */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

extern unsigned int str1_dans_str2(const char* str1,const char* str2){
    if(!str1 || !str2 )         /* Si les deux chaines ne sont pas nulles, comparer.*/
        return 0;
    return (strcasestr(str2,str1)!=NULL);
}

//----------------------------------------------------------------------------------------

extern unsigned int str2_dans_str1(const char* str1,const char* str2){
    if(!str1 || !str2 )         /* Si les deux chaines ne sont pas nulles, comparer.*/
        return 0;
    return (strcasestr(str1,str2)!=NULL);
}

//----------------------------------------------------------------------------------------

extern unsigned int annee_dans_interval(const char* interval, const char* annee){

    // Separation de la chaine de caractere selon le separateur d'interval.
    h_table_string str_interval = table_string_creer(interval,TOKEN_INTERVAL_ANNEE);

    // Variables locales pour comparaison de l'interval.
    int int_bas = 0;
    int int_haut = 0;
    int int_annee = 0;
    char* bas=NULL;
    char* haut=NULL;
    // En cas de manque/trop d'element d'interval ou valeur nul, signaler l'echec.
    if(!str_interval || !annee || table_string_get_taille(str_interval) != 2){
        table_string_liberer(str_interval);
        return 0;
    }

    //on verifie quon a des numeros
    if( !isdigit(annee[0])||
        !isdigit(table_string_get_element_n(str_interval,0)[0] )||
        !isdigit(table_string_get_element_n(str_interval,1)[0] )
    ){
        table_string_liberer(str_interval);
        return 0;
    }
    //on convertit
    bas=table_string_get_element_n(str_interval,0);
    haut=table_string_get_element_n(str_interval,1);
    int_annee = atoi(annee);
    int_bas   = atoi(bas);
    int_haut  = atoi(haut);


    // Si une annee est negative, signaler un echec.
    if( int_annee<0 || int_bas<0 || int_haut<0){
        table_string_liberer(str_interval);
        return 0;
    }

    // Liberer l'allocation dynamique de la separation de la chaine de caractere.
    table_string_liberer(str_interval);

    // Comparer et retourner le resultat.
    return ((int_bas<=int_annee) && ( int_annee<int_haut));
}

//----------------------------------------------------------------------------------------

extern unsigned int cote_dans_interval(const char* interval,const char* cote){
    
    // Separation de la chaine de caractere selon le separateur d'interval.
    h_table_string str_interval=table_string_creer(interval,TOKEN_INTERVAL_ANNEE);

    // Variables locales pour comparaison de l'interval.
    double d_bas=0;
    double d_haut=0;
    double d_cote=0;

    // En cas de manque d'element d'interval ou valeur nul, signaler l'echec.
    if(!str_interval || !cote || table_string_get_taille(str_interval)<1){
        table_string_liberer(str_interval);
        return 0;
    }

    //on veut des numeros
    if( !isdigit(cote[0])||!isdigit(table_string_get_element_n(str_interval,0)[0])){
        table_string_liberer(str_interval);
        return 0;
    }


    // pointeur de reference pour l'appel de certaines fonctions.
    char *ptr;

    // Pour une seule cote (pas d'interval)
    if(table_string_get_taille(str_interval)==1){
        // Si les valeurs de l'interval sont negatives, echec.
        if( ( d_cote = strtod(cote,&ptr) )<0 ||
            ( d_haut  = strtod(table_string_get_element_n(str_interval,0),&ptr)<0)){
            table_string_liberer(str_interval);
            return 0;
        }
        table_string_liberer(str_interval);
        return (d_cote>=d_haut);
    }

    //on veut des numeros sur lautre cote aussi
    if( !isdigit(table_string_get_element_n(str_interval,1)[0])){
        table_string_liberer(str_interval);
        return 0;
    }

    // Pour plusieurs cotes, verifier si elles sont negatives. Si oui, echec.
    if( ( d_cote = strtod(cote,&ptr) )<0 ||
        ( d_bas  = strtod(table_string_get_element_n(str_interval,0),&ptr)<0 ||
        ( d_haut = strtod(table_string_get_element_n(str_interval,1),&ptr )<0))){
        table_string_liberer(str_interval);
        return 0;
    }

    // Liberer l'allocation dynamique de la separation de la chaine de caractere.
    table_string_liberer(str_interval);

    // Comparer et retourner le resultat.
    return ((d_bas<=d_cote) && ( d_cote<d_haut));
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/