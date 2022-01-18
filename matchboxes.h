#ifndef MATCHBOX
#define MATCHBOX

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include "game.h"
#include "ball_arraylist.h"
#include "opened_matchbox_stack.h"

#define HASH_TABLE_SIZE 8


typedef struct _matchbox  {

    uint64_t configurations[8] ;  
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






uint32_t compute_hash_value(uint64_t configuration,  uint32_t size);
int sum_of_digits(int n);
matchboxes_list *new_list();
hash_table* new_hash_table(uint32_t size);
void add_head(matchboxes_list *l , uint32_t configuration, uint32_t g[3][3]);
void init_matchbox_hash_table(char * matchbox, hash_table *th, uint32_t size);



void free_menace(hash_table *menace);
_balls get_menace_move(hash_table* menace, uint64_t configuration,opened_matchboxes_stack * ombs);
void save_menace_state(char * menace_state_file, hash_table *menace, uint32_t size);
void count_ball(matchbox *m, uint32_t ball_arr[3][3]);
void update_menace_state(game_result gr , opened_matchboxes_stack * ombs);
void gamer_vs_menace( hash_table *th, uint8_t board_state[3][3] , opened_matchboxes_stack * ombs, game_result  *result);
#endif