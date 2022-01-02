#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "game.h"


#define CONTINUE 0
#define FINISHED 1
#define ROND 1
#define CROIX 2

void appliquer_transformation_base(uint8_t grille[3][3], transformation tr)
{
    uint8_t t;
    switch(tr)
    {
        case(ID):
            break;

        case(ROT_90):
            t = grille[0][0];
            grille[0][0] = grille[2][0];
            grille[2][0]=grille[2][2];
            grille[2][2]=grille[0][2];
            grille[0][2]=t;

            t = grille[0][1];
            grille[0][1] = grille[1][0];
            grille[1][0]=grille[2][1];
            grille[2][1]=grille[1][2];
            grille[1][2]=t;
            break;

        case(ROT_180):
            appliquer_transformation_base(grille, ROT_90);
            appliquer_transformation_base(grille, ROT_90);
            break;

        case(ROT_270):
            appliquer_transformation_base(grille, ROT_90);
            appliquer_transformation_base(grille, ROT_90);
            appliquer_transformation_base(grille, ROT_90);
            break;

        case(MIROIR_VERT):
            t = grille[0][0];
            grille[0][0] = grille[0][2];
            grille[0][2] = t;

            t = grille[1][0];
            grille[1][0] = grille[1][2];
            grille[1][2] = t;

            t = grille[2][0];
            grille[2][0] = grille[2][2];
            grille[2][2] = t;
            break;

        case(MIROIR_HORIZ):
            appliquer_transformation_base(grille, ROT_90);
            appliquer_transformation_base(grille, MIROIR_VERT);
            appliquer_transformation_base(grille, ROT_270);
    }
}
// les fonctons relative à une partie en cours 
_Bool has_empty_cases(uint8_t grille[3][3])
{
    uint32_t i,j;

     for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            if(grille[i][j]==0)
                return 1;
        }
    }
    return 0;
}

_Bool is_win(uint8_t grille[3][3])
{
    uint32_t i;

    for(i=0; i<3; i++)
    {
        if(grille[i][0]==grille[i][1] && grille[i][0]==grille[i][2] && grille[i][0]!=0 )
            return 1;
        else if(grille[0][i]==grille[1][i] && grille[0][i]==grille[2][i] && grille[0][i]!=0)
            return 1;
        else if(grille[0][0]==grille[1][1] && grille[0][0]==grille[2][2] && grille[0][0]!=0)
            return 1;
        else if(grille[0][2]==grille[1][1] && grille[0][2]==grille[2][0] && grille[0][2]!=0)
            return 1;
    }

    return 0;
}

_Bool is_valid_configuration(uint8_t grille[3][3])
{
    uint64_t i,j,sumx=0,sumo=0;

     for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            if(grille[i][j]==1)
            {
                sumo++;
            }
            else if(grille[i][j]==2)
            {
                sumx++;
            }
        }
    }
    return (abs(sumx-sumo)==1 && has_empty_cases(grille) && !(is_win(grille)));

}


_Bool is_in_table(uint64_t code, uint64_t tab[304])
{
    for(int i=0;i<304;i++)
    {
        if ( code == tab[i])
            return 1;
    }
    return 0;
}
uint64_t from_grid_to_base3( uint8_t grille[3][3])
{
    
    uint64_t nb=0,p=1;
    int i,j;
    for(i=2;i>=0 ;i--){
        for(j=2;j>=0;j--){
            nb=nb+grille[i][j]*p;
            p=p*10;
        }
    }
    return nb;
}
void from_base3_to_grid(uint8_t grille[3][3],uint64_t nb)
{
    int i,j;
    
    for(i=2;i>=0;i--)
    {
        for(j=2;j>=0;j--)
        {
            grille[i][j]=nb%10;
            nb=nb/10;
            
        }
    }

}

uint64_t from_ball_to_base3(_balls bille,int choix)
{   uint64_t nb=choix;
    for(uint32_t i=0;i<bille;i++){
        nb=nb*10;
    }
    return nb;
}

_balls from_base3_to_ball(uint64_t nb)
{
    uint32_t i;
    while(nb%10==0){
        nb=nb/10;
        i++;
    }
    return i;
}
_balls transform_balls(transformation tr,_balls bille,int choix)
{
    uint64_t code=from_ball_to_base3(bille,choix);
    uint8_t g[3][3];
    from_base3_to_grid(g,code);
    appliquer_transformation_base(g,tr);
    return from_base3_to_ball(from_grid_to_base3(g));
    

}


char print_value(uint8_t value)
{
    switch(value)
    {
        case (0):
            return ' ';
        case (1):
            return 'x';
        case (2):
            return 'o';
        default:
            assert(0);
    }
}


void print_grille_2d(uint8_t grille[3][3], FILE *f)
{
    fprintf(f, "|%c|%c|%c|\n", print_value(grille[0][0]), print_value(grille[0][1]), print_value(grille[0][2]));
    fprintf(f, "|%c|%c|%c|\n", print_value(grille[1][0]), print_value(grille[1][1]), print_value(grille[1][2]));
    fprintf(f, "|%c|%c|%c|\n", print_value(grille[2][0]), print_value(grille[2][1]), print_value(grille[2][2]));
}

void print_grille_1d(uint8_t grille[3][3], FILE *f)
{
    fprintf(f, "%c%c%c%c%c%c%c%c%c", print_value(grille[0][0]), print_value(grille[0][1]), print_value(grille[0][2]), print_value(grille[1][0]), print_value(grille[1][1]), print_value(grille[1][2]), print_value(grille[2][0]), print_value(grille[2][1]), print_value(grille[2][2]));
}

void print_all_transformations_1d(uint8_t g[3][3], FILE *f)
{
    print_grille_1d(g,f);
    fprintf(f, "|");
    /*

    appliquer_transformation_base(g, ROT_90);
    print_grille_1d(g,f);
    fprintf(f, "|");

    appliquer_transformation_base(g, ROT_90);
    print_grille_1d(g,f);
    fprintf(f, "|");

    appliquer_transformation_base(g, ROT_90);
    print_grille_1d(g,f);
    fprintf(f, "|");

    appliquer_transformation_base(g, ROT_90);
    appliquer_transformation_base(g, MIROIR_VERT);
    print_grille_1d(g,f);
    fprintf(f, "|");

    appliquer_transformation_base(g, ROT_90);
    print_grille_1d(g,f);
    fprintf(f, "|");

    appliquer_transformation_base(g, ROT_90);
    print_grille_1d(g,f);
    fprintf(f, "|");

    appliquer_transformation_base(g, ROT_90);
    print_grille_1d(g,f);

    //On fait une derniere transformation pour remettre la grille dans son Ã©tat initial
    appliquer_transformation_base(g, ROT_90);
    appliquer_transformation_base(g, MIROIR_VERT);
    */
    fprintf(f, "\n");
    
}

uint8_t next_configuration(uint8_t grille[3][3])
{
    uint8_t i, j;

    grille[0][0]++;
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            if(grille[i][j]==3)
            {
                grille[i][j]=0;
                if(j<2) grille[i][j+1]++;
                else if(i<2) grille[i+1][0]++;
                else return FINISHED;
            }
        }
    }

    return CONTINUE;
}

