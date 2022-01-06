#ifndef MATCHBOX
#define MATCHBOX

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

typedef struct _matchbox  {

    uint64_t configurations[8];  
    //  tableau arrayList
    ball_arraylist  *arl;

    struct _matchbox *next;

} matchbox;

typedef  struct {
    uint32_t taille;
    matchbox *head;
} matchboxes_list;


typedef struct {

    matchboxes_list **tab;
    uint32_t taille;
    
} hash_table;




tab_maillon* new_tab_maillon(uint32_t size);
void add_tete_maillon (list_tab_maillon* l,  tab_maillon *t);
void agrandir_liste_libre(ball_arraylist *arl, uint32_t size);

ball_list *new_liste();
list_tab_maillon *new_liste_tab_maillons();

ball_arraylist* new_arraylist(uint32_t init_size);
_Bool est_vide(ball_list *l );
ball* rem_tete_maillon(ball_list *l);
void  add_on_head_of_occupied (ball_list* l,  ball *t);

ball* rem_tete_maillon(ball_list *l);
 void add_on_head_of_arrayList(ball_arraylist* arl, _balls d);
 uint32_t compute_hash_value(uint64_t configuration,  uint32_t size);
 int sum_of_digits(int n);
 matchboxes_list *new_list();
 hash_table* new_hash_table(uint32_t size);
 void add_head(matchboxes_list *l , uint32_t configuration, uint32_t g[3][3]);
void init_matchbox_hash_table(char * matchbox, hash_table *th, uint32_t size);

#endif