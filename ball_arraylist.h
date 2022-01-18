/*
*Ce fichier permet de gerer l'arraylist de bille pour une configuration donnée
*elle contient toutes les fonctiond de mmanupulation d'une arraylist 
*Ajout suppression Mise à jour et libération
*/


#ifndef ARRAYLIST_OF_MATCHBOX_BALL
#define ARRAYLIST_OF_MATCHBOX_BALL

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include "game.h"



typedef struct _ball
{
    struct _ball *next;
    uint32_t ball_value;
} ball;

typedef  struct {
    uint32_t size;
    ball *head;
} ball_list;

//dpdppdpd

typedef struct _tab_maillon
 {
    ball *balls_array; //Un tableau de maillons
    uint32_t taille_tab; //La taille du tableau de maillons
    struct _tab_maillon *next;
} tab_maillon;

 typedef struct
{
    uint32_t size;
    tab_maillon *head; 
} list_tab_maillon;

typedef struct {  

    ball_list *occupied;
    ball_list *empty;

    list_tab_maillon *ltm;
} ball_arraylist;


tab_maillon* new_tab_maillon(uint32_t size);
void add_tete_maillon (list_tab_maillon* l,  tab_maillon *t);
void agrandir_liste_libre(ball_arraylist *arl, uint32_t size);


ball_list *new_liste();
list_tab_maillon *new_liste_tab_maillons();

ball_arraylist* new_arraylist(uint32_t init_size);
_Bool est_vide(ball_list *l );
void  add_on_head_of_occupied (ball_list* l,  ball *t);
ball* rem_head_maillon(ball_list *l);
void add_on_head_of_arrayList(ball_arraylist* arl, _balls d);


ball  *find_ball_predecessor( ball_list * l, uint32_t size, _balls ball_value);
void rem_ball(ball_arraylist* arl,_balls ball_value);

#endif