#ifndef OPENED_MATCHBOX_STACK
#define OPENED_MATCHBOX_STACK

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include "ball_arraylist.h"

/*
*Ce fichier contien la pile permetant de garder la trace des boites d'allumettes ouverte lors d'une partie
*Elle contient toutes les fonctions de mmanupulation d'une pile 
*Ajout suppression Mise à jour et libération de la pile
*/

typedef struct _opened_matchbox {

    ball_arraylist * barray;
    _balls ball_value;
    struct _opened_matchbox * next;

}opened_matchbox;

typedef struct {
    opened_matchbox * head;

}opened_matchboxes_stack;


opened_matchbox *new_maillon(ball_arraylist * barray,_balls ball_value);
opened_matchboxes_stack * omb_stack_new();


void omb_stack_push(opened_matchboxes_stack *p,ball_arraylist * barray, _balls ball_value);
void omb_stack_pop(opened_matchboxes_stack *p);
void omb_stack_free(opened_matchboxes_stack *p);









#endif