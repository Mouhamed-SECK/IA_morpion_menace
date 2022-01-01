
#ifndef HELPER
#define HELPER

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>




typedef enum transformation{ID, ROT_90, ROT_180, ROT_270, MIROIR_VERT, MIROIR_HORIZ} transformation;


char print_value(uint8_t value);
void appliquer_transformation_base(uint8_t grille[3][3], transformation t);
void print_grille_2d(uint8_t grille[3][3], FILE *f);
void print_grille_1d(uint8_t grille[3][3], FILE *f);
uint8_t next_configuration(uint8_t grille[3][3]);


#endif