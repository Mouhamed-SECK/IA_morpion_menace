#ifndef GAME
#define GAME

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>

typedef enum _balls{PINK, RED, AMBER, GREEN, GOLD, BLACK, SILVER, LILAC, WHITE} _balls;
typedef enum transformation{ID, ROT_90, ROT_180, ROT_270, MIROIR_VERT, MIROIR_HORIZ} transformation;




_Bool has_empty_cases(uint8_t grille[3][3]);
_Bool is_win(uint8_t grille[3][3]);
_Bool is_valid_configuration(uint8_t grille[3][3]);
_Bool is_in_table(uint64_t code, uint64_t tab[304]);
uint64_t from_grid_to_base3( uint8_t grille[3][3]);
void from_base3_to_grid(uint8_t grille[3][3],uint64_t nb);
uint64_t from_grid_to_base3( uint8_t grille[3][3]);
void from_base3_to_grid(uint8_t grille[3][3],uint64_t nb);
uint64_t from_ball_to_base3(_balls bille,int choix);
_balls from_base3_to_ball(uint64_t nb);
_balls transform_balls(transformation tr,_balls bille,int choix);
char print_value(uint8_t value);
void appliquer_transformation_base(uint8_t grille[3][3], transformation t);
void print_grille_2d(uint8_t grille[3][3], FILE *f);
void print_grille_1d(uint8_t grille[3][3], FILE *f);
uint8_t next_configuration(uint8_t grille[3][3]);

#endif