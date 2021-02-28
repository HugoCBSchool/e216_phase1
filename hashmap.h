/*
   This is free and unencumbered software released into the public domain.
   Anyone is free to copy, modify, publish, use, compile, sell, or
   distribute this software, either in source code form or as a compiled
   binary, for any purpose, commercial or non-commercial, and by any
   means.
   In jurisdictions that recognize copyright laws, the author or authors
   of this software dedicate any and all copyright interest in the
   software to the public domain. We make this dedication for the benefit
   of the public at large and to the detriment of our heirs and
   successors. We intend this dedication to be an overt act of
   relinquishment in perpetuity of all present and future rights to this
   software under copyright law.
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
   For more information, please refer to <http://unlicense.org/>
*/
#ifndef _HASHMAP_H
#define _HASHMAP_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "debug_include.h"

//definition du type du hashmap et de son handle
typedef struct hmap     t_hmap      ,
                        *h_hmap     ;

//foncteur typé equivalent a un destructeur de structure de data
//le type de l'argument est un void-pointer car le type de l'objet a detruire doit etre
//ren
typedef void (*func_t_paire_liberer_data)(void*);
typedef void (*f_contexte_cle_valeur)(void*,const char* const,void*);
typedef int  (*f_si_contexte_cle_valeur)(void*, const char* const,void*);
/**
 * @brief  creation dun hashmap vide dont la taille initiale est taille_init*sizeof(void*)
 * @retval un pointeur sur le hashmap si tout va bien, NULL sinon
 */
h_hmap hmap_creer();


/**
 * @brief  permet d'ajouter une copie d'une paire clef-valeur au map sous la clef donnee
 * @param  map:             la map a populer
 * @param  cle:             la cle de l'element
 * @param  valeur:          laddresse de la structure abstraite aux yeux du map a copier
 *                          -   si 0, echoue
 * @param  f_liberer_valeur: un foncteur permettant de liberer la struct copiee
 *                          - si NULL, le map ne detruit pas le handle lorsquil est detrui
 * @retval EXIT_FAILURE si echec, EXIT_SUCCESS sinon
 *          - un echec arrive si la cle est deja populee dans la table
 */
int hmap_add(  h_hmap const         map     ,   
               const  char*  const  cle     , 
               void*                valeur  , 
               const  func_t_paire_liberer_data const f_liberer_valeur       );
/**
 * @brief  permet d'ajouter une copie d'une paire clef-valeur au map sous la clef donnee
 *          Si la cle existe deja, elle est detruite si un destructeur y est attribue
 *          ensuite, la reference de la nouvelle sert a effectuer le meme traitement 
 *          que pour hmap_add.
 * @param  map:             la map a populer
 * @param  cle:             la cle de l'element
 * @param  valeur:          laddresse de la structure abstraite aux yeux du map a copier
 * @param  f_liberer_valeur: un foncteur permettant de liberer la struct copiee
 *                              - si NULL, le map ne garde quune reference sur la struct
 * @retval le nombre de bytes copies, -1 pour un echec d'allocation
 */
int hmap_remplacer( h_hmap const          map     ,   
                    const  char*  const   cle     , 
                    void*                 valeur  ,   
                    const  func_t_paire_liberer_data const f_liberer_valeur             );

/**
 * @brief  permet d'obtenir une reference sur la structure stoquee.
 * @param  map: la map a observer
 * @param  cle: la cle a chercher
 * @retval un pointeur sur la structure dont le titre est inconnu de la map.
 *          NULL si echec.
 */
void *hmap_get( h_hmap const map, const char *const   cle );

/// @brief Remove an element from the hashmap.
/// @param hashmap The hashmap to remove from.
/// @param key The string key to use.
/// @param len The length of the string key.
/// @return On success 0 is returned.
/**
 * @brief  permet de retirer un element de la table sans liberer la memoire de la 
 *         struct stockee.
 * @param  map: la map a observer 
 * @param  cle: la cle a chercher
 * @retval un pointeur sur la struct retiree dont la responsabilite est remise a 
 *          l'appelant. NULL si echec.
 */
void* hmap_pop_element( h_hmap const map, const char *const cle);
/**
 * @brief  permet de retirer un element de la table et d'en liberer la memoire 
 *          si un foncteur de destruction est associe a l'element. Seulement utiliser 
 *          cette fonction si la gestion de memoire est faite a l'externe.
 * @param  map: la map a observer
 * @param  cle: la cle a chercher
 * @retval void
 */
void  hmap_supprimer_element( h_hmap const map, const char *const cle);


/**
 * @brief  permet d'iterer sur toutes les paires du map en appelant une procedure prenant 
 *          une paire cle:valeur en plus d'un contexte d'execution en argument.
 * @param  map:         la map sur laquelle iterer
 * @param  func:        l'addresse de la fonction a appeler
 * @param  contexte:    le contexte d'execution a donner en premier argument a la fonction
 * @retval 1 pour succes, 0 pour echec
 */
int hmap_iterer_paires( h_hmap const            map, 
                        f_contexte_cle_valeur   func, 
                        void *const             contexte);
int hmap_iterer_executer_si(  h_hmap const              map,
                              f_contexte_cle_valeur     f_exec,
                              f_si_contexte_cle_valeur  f_si,
                              void* const               contexte
                              );   

/**
 * @brief  retourne la taille du domaine de hashage de la map.
 * @param  map: la map a observer
 * @retval le nombre de pointeurs de paires chainees dans la table
 */
int64_t hmap_get_taille(h_hmap const map);


/**
 * @brief  permet de detruire un hmap. la memoire de chaque paire est liberee si celle-ci 
 *          contient un foncteur vers sa destructice.
 * @param  map: la map a detruire
 * @retval None
 */
void hmap_liberer(h_hmap map);

#endif