/*
	Projet		: ELE216 - Laboratoire 1
	Date		: 27 janvier 2021
	Par 		: Gabriel Gandubert et Hugo Cusson-Bouthillier
	Logiciel	: Sublime text & Eclipse
	Definition	: Lecture de chaque ligne de la base de donnee.

	Contient:
		Fait appel aux librairies parser.h et resultats.h pour traiter les lignes.

		FONCTIONS PUBLIQUES:
			% Ouverture et recherche du fichier texte.
			int recherche_fichier(char* nom_fichier, pt_critere critere)

		FONCTIONS PRIVEEs :
			% Fonction privee permettant de verifier si le fichier recu est correct 
			% avant ouverture.
			int verifier_fichier(char* nom_fichier)

*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

// Header file
#include "interface.h"
#define __DEBUG_INTERFACE_H
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*							CONSTANTES D'IMPLEMENTATION     							*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

//fichiers de sortie


static const char FICHIER_SORTIE_NOM[]			="resultat_nom.txt";
static const char FICHIER_SORTIE_TITRE[]		="resultat_titre.txt";
static const char FICHIER_SORTIE_COTE[]			="resultat_cote.txt";
static const char FICHIER_SORTIE_RESULTATS[]	="resultats.txt";

// Caratere de separation de l'adresse du fichier.
#define PATH_SEPARATOR '/'
#define TOKEN_TITRE_ID ','
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*							TYPES ET STRUCTURES OPAQUES     							*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/**
 * @brief  	type t_fichier est une reference au type de base de donnees utilisee 
 * 			presentement. Type opaque de enum_t_fichier
 */
typedef enum tag_fichier{
	tag_fichier_ERREUR = 0, 
	tag_fichier_TITRE, 
	tag_fichier_PERSONNE, 
	tag_fichier_COTE
} t_tag_fichier;


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*							DECLARATIONS FONCTIONS PRIVEES    							*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/**
 * @brief  	Permet de verifier le type de base de donnees et d'indiquer
 *			si elle est inconnue par le programme.
 * @note	HLR15 : Verification du nom du fichier avant ouverture. Les messages 
 *				d'erreur sont generes par la fonction verifier_fichier.
 * @param  	nom_fichier	:	la string d'adresse de la base de donnee.
 * @retval 	Le type de fichier donnee selon l'enum enum_t_fichier. retourne ERREUR si
 *			le fichier est inconnue ou NULL.
 */
t_tag_fichier verifier_fichier(char* const nom_fichier);
extern void ajouter_resultat_titre_hmap(
	void* contexte, const char* const cle, void* valeur);
extern void ajouter_resultat_nom_hmap(
	void* contexte, const char* const cle, void* valeur);
extern void ajouter_resultat_cote_hmap(
	void* contexte, const char* const cle, void* valeur);
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/




/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*					IMPLEMENTATION FONCTIONS PRIVEES           							*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
extern void ajouter_resultat_titre_hmap(
	void* contexte, const char* const cle, void* valeur){

	h_donnee_titre 		donnee_titre 	=(h_donnee_titre) valeur;
	h_hmap 				destination  	=contexte;
	h_donnee_resultat 	resultat		=NULL;
	unsigned int        nouveau			=0;

	if(!contexte || !cle ||!valeur)
		return;

	//on regarde si on l'a deja
	if(!( resultat=(h_donnee_resultat)hmap_get(destination,cle)) ){
		
		// si non on cree un nouveau
		if(! (resultat=donnee_resultat_creer()))
			return;

		nouveau=1;
	}

	//on transfert le data
	donnee_resultat_set_id_titre(resultat,donnee_titre_get_id_titre(donnee_titre));
	donnee_resultat_set_titre(resultat,donnee_titre_get_titre(donnee_titre));
	donnee_resultat_set_annee(resultat,donnee_titre_get_id_titre(donnee_titre));
	donnee_resultat_set_titre(resultat,donnee_titre_get_id_titre(donnee_titre));

	//si nouveau on doit ajouter au map
	if(nouveau)
		hmap_remplacer(destination,cle,resultat,&donnee_resultat_liberer);
	
}
extern void ajouter_resultat_nom_hmap(
	void* contexte, const char* const cle, void* valeur){
	h_hmap 				map				=(h_hmap)contexte;
	h_donnee_nom 		data_nom		=(h_donnee_nom)valeur;
	h_donnee_resultat	destination		=NULL;
	h_table_string  	titre_ids		=NULL;
	int					taille_table	=0;

	if( !contexte || ! cle || !valeur )
		return;
	
	//on obtient le tuple de id de titre et on le tokenize
	if( !(	titre_ids=table_string_creer(
				donnee_nom_get_id_titres(data_nom),
				TOKEN_TITRE_ID
		)	) || !(taille_table=table_string_get_taille(titre_ids))			
	){
		table_string_liberer(titre_ids);
		return;
	}
	

	//pour chaque token obtenu, si il est dans les resultats, on transfere le data
	for(int i=0;i<taille_table;++i){

		if( destination=(h_donnee_resultat)hmap_get( 
				map, 
				table_string_get_element_n(titre_ids,i)
			)
		){
			donnee_resultat_set_nom(destination,donnee_nom_get_nom(data_nom));
		}
	}
	table_string_liberer(titre_ids);
}
extern void ajouter_resultat_cote_hmap(
	void* contexte, const char* const cle, void* valeur){
	h_hmap 				map				=(h_hmap)contexte;
	h_donnee_cote 		data_cote		=(h_donnee_cote)valeur;
	h_donnee_resultat	destination		=NULL;

	if( !contexte || ! cle || !valeur )
		return;
	
	//on obtient le node du hmap si il existe et on transfert le data
	if( destination=(h_donnee_resultat)hmap_get(map,donnee_cote_get_id_titre(data_cote))){
		donnee_resultat_set_cote(destination,donnee_cote_get_cote(data_cote));
	}
}
extern int  verifier_si_resultat_valide(
	void* contexte, const char* const cle, void* valeur){
	pt_critere critere			=(pt_critere)contexte;
	h_donnee_resultat resultat	=(h_donnee_resultat)valeur;

	if(!contexte || !cle || !valeur)
		return EXIT_FAILURE;
	
	//si un type de critere manque a lappel on retourne echec
	if((critere_get_taille(tag_cote,    critere)&& !donnee_resultat_get_cote( resultat))||
	   (critere_get_taille(tag_titre,   critere)&& !donnee_resultat_get_titre(resultat))||
	   (critere_get_taille(tag_personne,critere)&& !donnee_resultat_get_nom(  resultat))||
	   (critere_get_taille(tag_annee,	critere)&& !donnee_resultat_get_annee(resultat))
	){
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

}





/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*							IMPLLEMENTATION FONCTIONS PUBLIQUES							*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
h_hmap recherche_fichier(const char* const nom_fichier, pt_critere critere)
{
	char*  			ligne				 = NULL;
	size_t			taille_ligne 		 = 0;
	FILE*  			fichier_base_donnees = NULL;
	t_tag_fichier 	fichier_present		 = tag_fichier_ERREUR;
	h_hmap			map 				 = NULL;
	/* 
	 * @note	HLR15 : Verification du nom du fichier avant ouverture. Les messages 
	 *				d'erreur sont generes par la fonction verifier_fichier.
	 */
	if((fichier_present = verifier_fichier(nom_fichier) )== tag_fichier_ERREUR)
	{
		return NULL;
	}

	// Ouverture du fichier et gestion d'erreur d'ouverture.
	if((fichier_base_donnees = fopen(nom_fichier, "rt")) == NULL)
	{
		printf("ERROR, COULD NOT OPEN FILE : %s.\n", nom_fichier);
		return NULL;
	}

	// RELATES HLR05
	#ifdef __INTERFACE_H_DEBUG_LECTURE
	int cpt=0;
	/*
	 *	@note	HLR11 : La fonction parcour le fichier ligne par ligne.
	 *				Scan de chaque ligne de texte du fichier jusqu'a EOF.
	 */
	while(getline(&ligne, &taille_ligne, fichier_base_donnees) != -1)
	{
		//RELATE HLR015
		//on imprime la ligne 10 fois
		printf(ligne); 
		if(++cpt>10)
			//juste pour pouvoir tester, on renvoit un espace bidon
			//vue quon appelle juste 3 fois la fonction en cas de test,
			//on neglige le leak
			return (h_hmap)malloc(sizeof(int));
		
		/*
		 * @note	HLR12 : La lecture des champs d'une ligne d'un fichier specifique
		 *				est geree par une fonction du module parser.h.
		 */

		// Recherche des titres
		#ifdef __INTERFACE_H_DEBUG_LECTURE
		switch(fichier_present)
		{
			// Recherche des titres.
			case tag_fichier_TITRE :
				{
					h_donnee_titre donnee =NULL;
					printf("un fichier de titre \n");
				}
				break; // FIN DU CAS TITRE.

			// Recherche des personnes
			case tag_fichier_PERSONNE :
				{
					h_donnee_nom donnee =NULL;
					printf("un fichier de noms \n");
				}
				break; // FIN DU CAS PERSONNE.

			// Recherche des cotes.
			case tag_fichier_COTE :
				{
					h_donnee_cote donnee =NULL;
					printf("un fichier de cotes \n");

				}
				break; // FIN DU CAS COTE.

			default :
				{
					// Si la ligne n'est pas libere, liberer.
					if(ligne != NULL)
					{
						free(ligne);
						ligne = NULL;
						taille_ligne = 0;
					}

					// Impossible a atteindre, mais prudent.
					printf(
						"FATAL ERROR IN : recherche_fichier() : DEFAULT CASE OCCURED.\n");
					fclose(fichier_base_donnees);

					return NULL;

				}// FIN DU CAS PAR DEFAUT.
		}
		#endif
		// Liberation de la ligne et preparation pour la prochaine lecture
		free(ligne);
		ligne = NULL;
		taille_ligne = 0;
	}
	// Si la ligne n'est pas libere, liberer.
	if(ligne != NULL)
	{
		free(ligne);
		ligne = NULL;
		taille_ligne = 0;
	}
	return (h_hmap)malloc(sizeof(int));//retour bidon pour tester

	#else
	//creation du hashmap
	if(!( map = hmap_creer())){

		#ifdef __DEBUG_INTERFACE_H
		printf("ERREUR hmap_creer\n");
		#endif

		return NULL;
	}

	if( !critere ){

		#ifdef __DEBUG_INTERFACE_H
		printf("ERREUR critere null\n");
		#endif

		return NULL;

	} else {
		//on regarde si on a a rechercher quoique ce soit
		switch(fichier_present){

			case tag_fichier_PERSONNE:
				if( !critere_get_taille(tag_personne,critere)){

					#ifdef __DEBUG_INTERFACE_H
					printf("ERREUR critere_get_taille tag_personne\n");
					#endif

					return NULL;
				}
				break;

			case tag_fichier_TITRE:
				if(	!critere_get_taille(tag_titre,critere) || 
					!critere_get_taille(tag_annee,critere)	)
				{
					#ifdef __DEBUG_INTERFACE_H
					printf("ERREUR critere_get_taille tag_titre/annee \n");
					#endif

					return NULL;
				}
				break;

			case tag_fichier_COTE:	
				if( !critere_get_taille(tag_cote,critere)){

					#ifdef __DEBUG_INTERFACE_H
					printf("ERREUR critere_get_taille tag_cote \n");
					#endif
				
					return NULL;
				}
				break;

			default:{

				#ifdef __DEBUG_INTERFACE_H
				printf("ERREUR tag_fichier_erreur \n");
				#endif

				return NULL;
			}

		}
	}
	
	/*
	 *	@note	HLR11 : La fonction parcour le fichier ligne par ligne.
	 *				Scan de chaque ligne de texte du fichier jusqu'a EOF.
	 */
	while(getline(&ligne, &taille_ligne, fichier_base_donnees) != -1)
	{
		/*
		 * @note	HLR12 : La lecture des champs d'une ligne d'un fichier specifique
		 *				est geree par une fonction du module parser.h.
		 */

		// Recherche differente pour chaque fichier.
		switch(fichier_present)
		{
			// Recherche des titres.
			case tag_fichier_TITRE :
				{
					h_donnee_titre donnee =NULL;

					//parse la ligne en la comparant au critere
					if( ( donnee = parse_ligne_titre_et_critere(ligne,critere) ) ){

						#ifdef __DEBUG_INTERFACE_H
						printf("TRACE tag_titre:donnee non nule par parse \n");
						#endif

						//si on a un succes on ajoute au hashmap
						if( hmap_add(	
								map									,
								donnee_titre_get_id_titre(donnee)	,
								(void*) donnee						,
								&donnee_titre_liberer				
							)  == EXIT_FAILURE )
						{
							#ifdef __DEBUG_INTERFACE_H
							printf("ERREUR:recherche_fichier: hmap_add failed titre \n");
							#endif

							hmap_liberer(map);
							return NULL;
						}
					}
				}
				break; // FIN DU CAS TITRE.
				
			// Recherche des personnes
			case tag_fichier_PERSONNE :
				{
					h_donnee_nom donnee =NULL;

					//parse la ligne en la comparant au critere
					if( donnee = parse_ligne_nom_et_critere(ligne,critere) ){

						#ifdef __DEBUG_INTERFACE_H
						printf("TRACE tag_nom:donnee non nule par parse \n");
						#endif


						//si on a un succes on ajoute au hashmap
						if( hmap_add(	
								map								,
								donnee_nom_get_id_nom(donnee)	,
								(void*) donnee					,
								&donnee_nom_liberer				
							)  == EXIT_FAILURE )						
						{
							#ifdef __DEBUG_INTERFACE_H
							printf("ERREUR:recherche_fichier: hmap_add failed nom \n");
							#endif

							hmap_liberer(map);
							map=NULL;

							return NULL;
						}
					}
				}
				break; // FIN DU CAS PERSONNE.
				
			// Recherche des cotes.
			case tag_fichier_COTE :
				{
					h_donnee_cote donnee =NULL;

					//parse la ligne en la comparant au critere
					if( donnee = parse_ligne_cote_et_critere(ligne,critere) ){

						#ifdef __DEBUG_INTERFACE_H
						printf("TRACE tag_cote:donnee non nule par parse \n");
						#endif

						//si on a un succes on ajoute au hashmap
						if( hmap_add(	
								map								,
								donnee_cote_get_id_titre(donnee)	,
								(void*) donnee					,
								&donnee_cote_liberer				
							)  == EXIT_FAILURE )
						{
							#ifdef __DEBUG_INTERFACE_H
							printf("ERREUR:recherche_fichier: hmap_add failed cote \n");
							#endif


							//erreur fatale au niveau du stockage
							hmap_liberer(map);
							map=NULL;
							return NULL;
						}
					}
				}
				break; // FIN DU CAS COTE.
				

			default :
				{
					// Si la ligne n'est pas libere, liberer.
					if(ligne != NULL)
					{
						free(ligne);
						ligne = NULL;
						taille_ligne = 0;
					}

					//on supprime la map
					hmap_liberer(map);
					map=NULL;
					// Impossible a atteindre, mais prudent.
					printf(
						"FATAL ERROR IN : recherche_fichier() : DEFAULT CASE OCCURED.\n");
					fclose(fichier_base_donnees);

					return NULL;

				}// FIN DU CAS PAR DEFAUT.
		}

		// Liberation de la ligne et preparation pour la prochaine lecture
		free(ligne);
		ligne = NULL;
		taille_ligne = 0;
	}

	// Si la ligne n'est pas libere, liberer.
	if(ligne != NULL)
	{
		free(ligne);
		ligne = NULL;
		taille_ligne = 0;
	}

	#endif
	

	/*
	 * @note	HLR13 : Tout fichier est fermee a la fin de l'utilisation.
	 */
	fclose(fichier_base_donnees);

	#ifdef __DEBUG_INTERFACE_H
	printf("TRACE:recherche_fichier: SUCCESS\n\n");
	#endif

	return map;
}
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
unsigned int analyser_resultats(
	pt_critere 	const critere,
	h_hmap 		const map_nom, 
	h_hmap 		const map_titre, 
	h_hmap 		const map_cote
){	
	int return_value=EXIT_FAILURE;
	FILE *fp=NULL;
	h_hmap resultats=NULL;
	h_table_string table_id_titres;

	//validation des entrees. certains hmap peuvent etre null si le critere le justifie
	if( !critere 													|| 
		!map_titre 													||
		( (!map_nom ) && critere_get_taille(tag_personne, critere) )||
		( (!map_cote) && critere_get_taille(tag_cote    , critere) )
	){
		return EXIT_FAILURE;
	}

	
	//ecriture des resultats pour la db de noms au fichier
	if(map_nom){
		if(!( fp = fopen(FICHIER_SORTIE_NOM, "wt") ) ){
			fp=NULL;
			return EXIT_FAILURE;
		}
		if(!hmap_iterer_paires(map_nom,&donnee_afficher_nom, (void*)fp)){
			fclose(fp);
			return EXIT_FAILURE;
		}
		fclose(fp);
		fp=NULL;
	}

	//ecriture des resultats pour la db de noms au fichier
	if(map_cote){
		if(!(fp= fopen(FICHIER_SORTIE_COTE, "wt")) ){
			fp=NULL;
			return EXIT_FAILURE;
		}
		if(!hmap_iterer_paires(map_nom,&donnee_afficher_cote, (void*)fp)){
			fclose(fp);
			return EXIT_FAILURE;
		}
		fclose(fp);
		fp=NULL;
	}

	//ecriture des resultats pour la db de titres au fichier
	if( !( fp = fopen(FICHIER_SORTIE_TITRE, "wt" ) ) ){
		return EXIT_FAILURE;
	}
	if(!hmap_iterer_paires(map_titre,&donnee_afficher_titre, (void*)fp)){
		fclose(fp);
		return EXIT_FAILURE;
	}
	fclose(fp);

	//cree la map des resultats
	if(! ( resultats=hmap_creer() )){
		return EXIT_FAILURE;
	}

	//on ajoute tous les titres trouves au hashmap, retourne si erreur
	if(!hmap_iterer_paires(map_titre,&ajouter_resultat_titre_hmap,(void*)resultats)){
		hmap_liberer(resultats);
		return EXIT_FAILURE;
	}

	if(map_nom){
		//on ajoute tous les noms qui trouvent leur titre dans le hmap au hmap
		if(!hmap_iterer_paires(map_nom,&ajouter_resultat_nom_hmap,(void*)resultats)){
			hmap_liberer(resultats);
			return EXIT_FAILURE;
		}
	}
	if(map_cote){
		//on ajoute toutes les cotes qui trouvent leur titre dans le hmap
		if(!hmap_iterer_paires(map_cote,&ajouter_resultat_cote_hmap,(void*)resultats)){
			hmap_liberer(resultats);
			return EXIT_FAILURE;
		}
	}

	//on imprime tous les resultats qui sont valides
	return_value = hmap_iterer_executer_si( 
		resultats,
		&donnee_afficher_resultat,
		&verifier_si_resultat_valide,
		critere
	);
	
	hmap_liberer(resultats);
	return return_value;
}
/* 
 * @note	HLR15 : Verification du nom du fichier avant ouverture. Les messages 
 *				d'erreur sont generes par la fonction verifier_fichier.
 */
t_tag_fichier verifier_fichier(char* const nom_fichier)
{
	char path_separator[2]={PATH_SEPARATOR,'\0'};
	char* last_token=nom_fichier;

	// Verification de l'existence du parametre.
	if(nom_fichier == NULL)
	{
		printf("ERROR, UNINITIALIZED FILE NAME.\n");
		return tag_fichier_ERREUR;
	}
	/*
	// Allocation dynamique d'une variables tampon de la meme dimension que l'entree.
	char* copie_fichier = (char*) malloc((strlen(nom_fichier)+1)*sizeof(char));

	// Variables pour contenir les chaines entre les separateurs.
	char* token;
	char* last_token;

	// Copie de l'entree pour ne pas l'affecter par le strtok.
	memcpy(copie_fichier, nom_fichier, (strlen(nom_fichier)+1)*sizeof(char));

	
	// Premiere segmentation de la chaine de caractere.
	token = strtok(copie_fichier, path_separator);

	// Detecter le nom du fichier dans la chaine (enlever le path).
	while(token != NULL)
	{
		last_token = token;
		token = strtok(NULL, path_separator);
		printf("token: %s\n last_token: %s\n",token,last_token);
	}
	*/

	// Verification du nom du fichier avec les references.
	if(strcmp(last_token, FICHIER_TITRE)==0)
	{
		//free(copie_fichier);
		return tag_fichier_TITRE;
	}
	else if(0==strcmp(last_token, FICHIER_NOMS))
	{
		//free(copie_fichier);
		return tag_fichier_PERSONNE;
	}
	else if(0==strcmp(last_token, FICHIER_COTE))
	{
		//free(copie_fichier);
		return tag_fichier_COTE;
	}
	else
	{

		// Message d'erreur en cas de nom invalide.
		printf("ERROR, UNKNOWN DATA FILE NAME : %s.   LAST TOKEN:%s\n", 
			nom_fichier,last_token
		);
		//free(copie_fichier);
		return tag_fichier_ERREUR;
	}
}


/*t_fichier verifier_fichier(char* nom_fichier)
{
	// Verification de l'existence du parametre.
	if(nom_fichier == NULL)
	{
		printf("ERROR, UNINITIALIZED FILE NAME.\n");
		return ERREUR;
	}

	// Allocation dynamique d'une variables tampon de la meme dimension que l'entree.
	char* copie_fichier = (char*) malloc((strlen(nom_fichier)+1)*sizeof(char));

	// Variables pour contenir les chaines entre les separateurs.
	char* token;
	char* last_token;

	// Copie de l'entree pour ne pas l'affecter par le strtok.
	memcpy(copie_fichier, nom_fichier, (strlen(nom_fichier)+1)*sizeof(char));

	// Premiere segmentation de la chaine de caractere.
	token = strtok(copie_fichier, PATH_SEPARATOR);

	// Detecter le nom du fichier dans la chaine (enlever le path).
	while(token != NULL)
	{
		last_token = token;
		token = strtok(NULL, PATH_SEPARATOR);
	}

	// Liberer la copie du fichier.
	free(copie_fichier);

	// Verification du nom du fichier avec les references.
	if(!strcmp(last_token, FICHIER_TITRE))
	{
		return TITRE;
	}
	else if(!strcmp(last_token, FICHIER_NOMS))
	{
		return PERSONNE;
	}
	else if(!strcmp(last_token, FICHIER_COTE))
	{
		return COTE;
	}
	else
	{
		// Message d'erreur en cas de nom invalide.
		printf("ERROR, UNKNOWN DATA FILE NAME : %s.\n", nom_fichier);
		return ERREUR;
	}
}
*/