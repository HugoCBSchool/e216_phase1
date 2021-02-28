/*
 *  main.c
 *	
 *	Project 	: ELE216 - Laboratoire 1
 *  Created on	: J21 janvier 2021
 *  Auteurs		: Hugo Cusson-Bouthillier & Gabriel Gandubert
 *
 *	Ce programme recois une liste de parametres contenant des commandes specifiques
 *	afin d'indiquer le type de critere de recherche pour une base de donnee de films.
 *	Les parametres -t, -a, -p et -r sont reconnu par le programme et enregistre ces
 *	donnees dans une structure defini par le moducle critere.h. Chaque commande
 *	peut recevoir plusieurs valeurs differentes si le caractere de separation est
 *	connu. Chaque critere enregistre ses donnees et les affiche dans le terminal.
 *
 *	Ce programme ne contient que la phase 1 du projet.
 */

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

// Appel des librairies necessaire pour ce programme.
#include <stdio.h>
#include <stdlib.h>

#include "debug_include.h"
#include "critere.h"
#include "hashmap.h"
#include "table_string.h"
#include "resultat.h"
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


//void test_hashmap(void);
void test_critere(void);
void test_resultat(void);
void	test_hashmap(void);

extern unsigned int str2_dans_str1(const char* str1,const char* str2){
    if(!str1 || !str2 )         /* Si les deux chaines ne sont pas nulles, comparer.*/
        return 0;
    return (strstr(str1,str2)!=NULL);
};
extern unsigned int imprimer_critere_foreach(const char* critere,void* not_used){
	if(critere)printf("    %s\n",critere);
	
	return EXIT_SUCCESS;
};
extern void imprimer_paire_critere_foreach(
	void* contexte,const char* cle,void* valeur){
	
	pt_critere p=(pt_critere)valeur;
	if(!cle ||!valeur)
		return;

	printf("TAG[%s]:\n",cle);
	critere_foreach(p,imprimer_critere_foreach,tag_titre,NULL);
	

};
/**
 * @brief  Fonction permettant dimprimer le contenu dun critere a la console
 * @note   HLR09-01	: Fonction temporaire pour afficher le contenu de la structure.
 * @param  critere	: le critere a imprimer
 * @retval None
 */
void imprimer_critere(pt_critere const critere){

	t_fp_foreach f=&imprimer_critere_foreach;
	printf("Titre : \n");
	critere_foreach(critere,f,tag_titre,NULL);
	printf("Personne : \n");
	critere_foreach(critere,f,tag_personne,NULL);
	printf("Annee : \n");
	critere_foreach(critere,f,tag_annee,NULL);
	printf("Cote : \n");
	critere_foreach(critere,f,tag_cote,NULL);
};
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
static const char* const tag[]={
	"tt1234567","tt0001111","nm0001114","t1234567","ttt1234567"};
static const char* const titre[]={"Lord of the ring","James Bond"};
static const char* const annee[]={"2015","1900:2025","1900:1901","2025:1900","2025:2025"};
static const char* const ratings[]={"2.2:3.3","1.1:5.5","1.1:10000.0"};
static const char* crit2={"tt1234567,,tt0001111,nm0001114,t1234567,ttt1234567"};

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*                           Fonction main                                          */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
int main(int argc, char **argv){
	test_hashmap();
	return 0;
}
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void test_critere(void){
	pt_critere c=critere_creer();
	if(!c){
		printf("erreur critere_creer\n");
		return;
	}
	if(!critere_set(c,annee[0],tag_annee)){
		printf("mauvais critere_set\n");
		return;
	}
	if(!critere_set(c,crit2,tag_titre)){
		printf("mauvais critere_set\n");
		return;
	}
	if(critere_get_taille(tag_titre,c)!=5){
		printf("gettaille mauvais\n");
	}
	if(!critere_get_element_i(c,tag_titre,4)||critere_get_element_i(c,tag_titre,5)){
		printf("getelement mauvais\n");
	}
	printf("getelement 4 titre: %s\n",critere_get_element_i(c,tag_titre,4));

	critere_foreach(c,&imprimer_critere_foreach,tag_titre,NULL);
	if(critere_contient(c,tag_titre,str2_dans_str1,"eee")||
		!critere_contient(c,tag_titre,str2_dans_str1,"ttt1234567"))
	{printf("bad critere contient");}
	critere_liberer(c);
}


void test_hashmap(void){
	pt_critere c=critere_creer();
	h_hmap h=hmap_creer();
	pt_critere ct[5]={NULL,NULL,NULL,NULL,NULL};
	pt_critere ct2[5]={NULL,NULL,NULL,NULL,NULL};

	if(!c||!h){
		printf("erreur creer\n");
		return;
	}
	if(!critere_set(c,annee[0],tag_annee)){
		printf("mauvais critere_set\n");
		return;
	}
	if(!critere_set(c,crit2,tag_titre)){
		printf("mauvais critere_set\n");
		return;
	}

	if(hmap_get(h,tag[0])){
		printf("mauvais get,pas suposer marcher\n");
		return;
	}
	for(int i=0;i<5;++i){
		pt_critere e=NULL;
		if(!(e=critere_creer())){
			printf("bad creer critere\n");
		}
		if(!critere_set(e,crit2,tag_titre)){
			printf("mauvais critere_set\n");
			return;
		}
		if(hmap_add(h,tag[i],(void*)e,&critere_liberer)==EXIT_FAILURE){
			if(i<=2){
				printf("tag[%s]:add a pas marche quand il devrait\n",tag[i]);
			}
		}else{
			if(i>2){
				printf("tag[%s]:add a marche mais devait pas\n",tag[i]);
			}
		}
		ct[i]=e;
	}
	printf("\n\nTEST ITER0:\n\n");
	hmap_iterer_paires(h,imprimer_paire_critere_foreach,NULL);
	printf("\n\nTEST_REMPLACER\n\n");

	for(int i=0;i<5;++i){
		pt_critere e=NULL;
		if(!(e=(pt_critere)hmap_get(h,tag[i]))){
			if(i<=2){
				printf("tag[%s]:get a pas marche mais devait \n",tag[i]);
			}
		}else{
			if(i>2){
				printf("tag[%s]:get a  marche mais devait pas \n",tag[i]);
			}
			if(!critere_get_element_i(e,tag_titre,4)){
				printf("mauvais critere_get\n");
				return;
			}	
		}	
	}
	
	printf("\n\nTEST ITER1:\n\n");
	hmap_iterer_paires(h,imprimer_paire_critere_foreach,NULL);
	printf("\n\nTEST_REMPLACER\n\n");

	for(int i=0;i<5;++i){
		pt_critere e=NULL;
		if(!(e=critere_creer())){
			printf("bad creer critere\n");
		}
		if(!critere_set(e,crit2,tag_titre)){
			printf("mauvais critere_set\n");
			return;
		}
		if(hmap_remplacer(h,tag[4-i],(void*)e,&critere_liberer)==EXIT_FAILURE){
			if(4-i<=2){
				printf("tag[%s]:rempl a pas marche quand il devrait\n",tag[4-i]);
			}
		}else{
			if(4-i<=2){
				printf("tag[%s]:rempl a marche mais devait pas\n",tag[4-i]);
			}
		}
		ct2[i]=e;
	}
	for(int i=0;i<5;++i){
		if(!ct[i]){
			printf("C[%d]: est nul\n",i);
		}
		else{
			if(hmap_get(h,tag[i])==ct[i]){
				if(i<2){
					printf("C[%d]: remplacer mais devait pas\n",i);
				}
			}else{
				if(i==2){
					if(hmap_get(h,tag[i])!=ct2[4-i]){
						printf("C2[%d]: le remplacement a echoue.\n",i);
					}
				}
			}
		}
	}
	printf("\n\nTEST ITER2:\n\n");
	hmap_iterer_paires(h,imprimer_paire_critere_foreach,NULL);
	printf("\n\nTEST_DETRUIRE\n\nDUMP C[i]\n");
	for(int i=0;i<5;++i){
		pt_critere pp=hmap_get(h,tag[i]);
		if(pp){
			printf("GET[%s]: %s\n   supprimer:->GET[]",
				tag[i],
				critere_get_element_i(pp,tag_titre,i));
			hmap_supprimer_element(h,tag[i]);
			if(hmap_get(h,tag[i])){
				printf("FAIL\n");
			}else{
				printf("SUCCESS\n");
			}
		}
	}
	printf("\n\nTEST ITER3:\n\n");
	hmap_iterer_paires(h,imprimer_paire_critere_foreach,NULL);
	printf("repopule\n");
	for(int i=0;i<5;++i){
		pt_critere e=NULL;
		if(!(e=critere_creer())){
			printf("bad creer critere\n");
		}
		if(!critere_set(e,crit2,tag_titre)){
			printf("mauvais critere_set\n");
			return;
		}
		if(hmap_remplacer(h,tag[i],(void*)e,&critere_liberer)==EXIT_FAILURE){
			if(i<=2){
				printf("tag[%s]:add a pas marche quand il devrait\n",tag[i]);
			}
		}else{
			if(i>2){
				printf("tag[%s]:add a marche mais devait pas\n",tag[i]);
			}
		}
		ct[i]=e;
	}
	printf("\n\nCHECK PRINT BEFORE DELETE\n\n");
	for(int i=0;i<3;++i){
		printf("C[%d]: %s   HMAP:%s MEME:",
			i,
			critere_get_element_i(ct[i],tag_titre,4),
			critere_get_element_i((pt_critere)hmap_get(h,tag[i]),tag_titre,4)
		);
		if(hmap_get(h,tag[i])==ct[i]){
			printf("YES\n");
		}else{
			printf("NO\n");
		}

	}

	printf("\n\nDELETE\n\n");
	hmap_liberer(h);
	//uncomment to see segfault
	/*
	for(int i=0;i<3;++i){
		printf("C[%d]: %s\n",
			i,
			critere_get_element_i(ct[i],tag_titre,4));
	}*/

}
/*void test_resultat(void){

}
/*void test_table_string(void){

}*/