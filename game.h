#ifndef GAME
#define GAME

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>

_Bool has_empty_cases(uint8_t grille[3][3]);
_Bool is_win(uint8_t grille[3][3]);
_Bool is_valid_configuration(uint8_t grille[3][3]);
_Bool is_in_table(uint64_t code, uint64_t tab[304]);
uint64_t codage_entier( uint8_t grille[3][3]);
void codage_grille(uint8_t grille[3][3],uint64_t nb);

#endif