#include "hashmap.h"

#ifndef HMAP_TAILLE
#define HMAP_TAILLE 1001
#endif

#ifndef HMAP_CLE_STR_LEN
#define HMAP_CLE_STR_LEN 9
#endif

/* We need to keep keys and values. */
typedef struct paire t_paire, *h_paire;
struct paire{
  char                      *cle;
  void                      *donnee;
  h_paire                   next;
  func_t_paire_liberer_data liberer_data;
};



void    liberer_paire(  h_paire paire);

h_paire hmap_get_paire(h_hmap map, const char *cle);
h_paire hmap_get_paire_precedente(h_hmap map, const char *cle);
int64_t hash(h_hmap map,const char *cle);

/* A hashmap has some maximum size and current size, as well as the data to
 * hold. */
struct hmap {
    int64_t   taille_table;
    h_paire   table_paire[HMAP_TAILLE];
};


h_hmap hmap_creer( ){

    h_hmap map=NULL;

    //allocation de la struct du map
    if( !(  map = (h_hmap)malloc(sizeof(t_hmap)) )){
        return NULL;
    }
    map->taille_table=HMAP_TAILLE;
    memset(map->table_paire,0,sizeof(h_paire)*HMAP_TAILLE);

    return map;
}





int hmap_add(   h_hmap const        map     ,   
                const  char*  const cle     , 
                void*               valeur  ,
                const  func_t_paire_liberer_data const f_liberer_valeur
){
    void*    val = NULL;
    h_paire pair = NULL;
    int64_t hashval=hash(map,cle);

    if(hashval<0)
        return EXIT_FAILURE;

    //si on ne le trouve pas dans la table
    if( !( pair = hmap_get_paire( map , cle ) ) ){

        //on cree un nouveau noeud
        if( !( pair = (h_paire) malloc( sizeof(t_paire) ) ) )  
            return EXIT_FAILURE;

        //on popule
        if( !( pair->cle = strdup(cle) ) ){
            free(pair);
            return EXIT_FAILURE;
        }
        if(valeur){
            pair->donnee=valeur;
            pair->liberer_data=f_liberer_valeur;
        }else{
            free(pair);
            return EXIT_FAILURE;
        }
        pair->next = NULL;                  //popule le next
        map->table_paire[hashval] = pair;   //popule le bucket du hash

    } else {

        if(!pair->donnee){
            if( valeur ){
                pair->donnee=valeur;
                pair->liberer_data=f_liberer_valeur;
            } else {
                return EXIT_FAILURE;
            }
        }else{
            return EXIT_FAILURE;
        }
    
    }

    return (EXIT_SUCCESS);
}

int hmap_remplacer( h_hmap const        map     ,
                    const  char*  const cle     , 
                    void*               valeur  ,
                    const  func_t_paire_liberer_data const f_liberer_valeur 
){
    void*   val = NULL;
    h_paire pair = NULL;
    int64_t hashval=hash( map , cle );

    if(hashval<0)
        return EXIT_FAILURE;

    //si on ne le trouve pas dans la table
    if( !( pair = hmap_get_paire( map , cle ) ) ){

        //on cree un nouveau noeud
        if( !( pair = (h_paire) malloc( sizeof(t_paire) ) ) )  
            return  EXIT_FAILURE;

        //on popule
        if( !( pair->cle = strdup(cle) ) ){
            free(pair);
            return EXIT_FAILURE;
        }

        if(valeur){
            pair->donnee=valeur;
            pair->liberer_data=f_liberer_valeur;
        }else{
            free(pair);
            return EXIT_FAILURE;
        }

        pair->next = NULL;                  //popule le next
        map->table_paire[hashval] = pair;   //popule le bucket du hash

    } else {

        if(!pair->donnee){

            if( valeur ){
                pair->donnee=valeur;
                pair->liberer_data=f_liberer_valeur;
            } else 
                return EXIT_FAILURE;

        } else {

            if(pair->liberer_data){
                pair->liberer_data(pair->donnee);
            }
            pair->donnee=NULL;
            
            if( valeur ){
                pair->donnee=valeur;
                pair->liberer_data=f_liberer_valeur;
            } else 
                return EXIT_FAILURE;
        }
    }
    
    return EXIT_SUCCESS;
}


void *hmap_get( h_hmap const map, const char *const   cle ){

    h_paire pair=hmap_get_paire(map,cle);

    return ( 
        pair 
        ?   (pair->donnee)
        :   NULL
    );

}


int64_t hash(h_hmap map,const char *cle){
    if( !map || !cle || 
        (strlen(cle)!=HMAP_CLE_STR_LEN&&strlen(cle)!=1+HMAP_CLE_STR_LEN)
    ){

        #ifdef __DEBUG_HASHMAP
        if(!map)
            printf("Hash debug: null map arg\n");
        if(!cle)
            printf("Hash debug: null cle arg\n");
        else
            printf("hash debug: strlen(cle)=%lu",strlen(cle));  
        #endif

        return -1;
    }
    long long int hash=0;
    hash = ( hash + ( ( cle[0] >> 3 ) << 1 ) + ( cle[0] % 2 )  ) << 4;

    #ifdef __DEBUG_HASHMAP
    printf("hash debug: result step 1= %lld\n",hash);
    #endif

    hash = ( hash + ( ( cle[1] >> 3 ) << 2 ) + ( cle[1] % 4 )  ) << 0;

    #ifdef __DEBUG_HASHMAP
    printf("hash debug: result step 2= %lld\n",hash);
    #endif

    for( int i=0 ; cle[i] ; ++i ){
        hash = ( hash << 4 ) + cle[i] % 16;
    }

    #ifdef __DEBUG_HASHMAP
    printf("hash debug: result step 3= %lld\n",hash);
    #endif

    return (hash % map->taille_table );
}

void* hmap_pop_element( h_hmap const map, const char *const cle){
    
    h_paire pair=hmap_get_paire_precedente(map,cle);

    if(!pair){
        return NULL;
    }
    h_paire temp=pair->next;

    if(pair->next->next){
        pair->next=temp->next;
    }

    void* retour=temp->donnee;
    free(temp);

    return retour;
}


void  hmap_supprimer_element( h_hmap const map, const char *const cle){
    
    h_paire pair=hmap_get_paire_precedente(map,cle);
    h_paire cible=NULL;
    int64_t hval=hash(map,cle);

    if(hval<0){
        return;
    }
    if(!pair){
        if(!(pair=hmap_get_paire(map,cle))){
            return;
        }
        if(pair==map->table_paire[hval]){
            if(pair->next){
                map->table_paire[hval]=pair->next;
                liberer_paire(pair);
            }else{
                liberer_paire(pair);
                map->table_paire[hval]=NULL;
            }
        }else{
            //NEVER
            printf("MEMORY LEAK ASSERTED IN HMAP: UNRELATED PAIR IN GRAPH.\n");
        }
    }else{
        cible=pair->next;

        if(cible->next){
            pair->next=cible->next;
        }

        liberer_paire(cible);
    }

}


int hmap_iterer_paires( h_hmap const            map, 
                        f_contexte_cle_valeur   func, 
                        void *const             contexte)
{

    if(!map || !func || !map->table_paire)
        return EXIT_FAILURE;

    for(int i=0;i<HMAP_TAILLE;++i){

        for(    h_paire p = map->table_paire[i];
                p!=NULL;
                p=p->next
        ){
            if( p->donnee && p->cle )
                func(contexte,p->cle,p->donnee);
        }
    }

    return EXIT_SUCCESS;
}


int hmap_iterer_executer_si(    h_hmap const              map,
                                f_contexte_cle_valeur     f_exec,
                                f_si_contexte_cle_valeur  f_si,
                                void* const               contexte
){
    if(!map || !f_exec || !f_si || !map->table_paire)
        return EXIT_FAILURE;

    for(int i=0;i<HMAP_TAILLE;++i){

        for(    h_paire p = map->table_paire[i];
                p!=NULL;
                p=p->next
        ){

            if( p->donnee && p->cle ){

                if(f_si(contexte,p->cle,p->donnee)==EXIT_SUCCESS){
                    f_exec(contexte,p->cle,p->donnee);
                }
            

            }
        }
    }

    return EXIT_SUCCESS;
}


int64_t hmap_get_taille(h_hmap const map){
    return(
        map
        ?   map->taille_table
        :   -1
    );
}


void hmap_liberer(h_hmap map){
    if(!map) return;

    if(map->table_paire){

        for(int i=0;i<HMAP_TAILLE;++i){

            h_paire precedent=map->table_paire[i];

            if(precedent){

                while(precedent->next){

                    h_paire actuel=precedent->next;
                    liberer_paire(precedent);
                    precedent=actuel;
                }
            }

            liberer_paire(precedent);
            map->table_paire[i]=NULL;
        }
    }
    free(map);
    map=NULL;
}

  

h_paire hmap_get_paire(h_hmap map, const char *cle){

    int64_t hashval=hash(map,cle);

    if(hashval<0)
        return NULL;

    for(    h_paire np = map->table_paire[hashval]; 
            np != NULL;
            np = np->next
    ){
        if(!strcmp(np->cle, cle)) return np;
    }

    return NULL;
}
h_paire hmap_get_paire_precedente(h_hmap map, const char *cle){

    int64_t hashval=hash(map,cle);
    if(hashval<0)
        return NULL;

    for(    h_paire np = map->table_paire[hashval]; 
            np->next!= NULL;
            np = np->next
    ){
        if(!strcmp(np->next->cle, cle)) return np;
    }

    return NULL;
}


void liberer_paire(  h_paire paire){
    if(!paire)      
        return;

    if(paire->cle)  
        free(paire->cle);

    if(paire->liberer_data && paire->donnee)
        paire->liberer_data(paire->donnee);
    
    free(paire);


    
}