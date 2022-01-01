#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "game.h"

typedef enum transformation{ID, ROT_90, ROT_180, ROT_270, MIROIR_VERT, MIROIR_HORIZ} transformation;
typedef enum ball{PINK, RED, AMBER, GREEN, GOLD, BLACK, SILVER, LILAC, WHITE} ball;


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
    uint64_t i,j;

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
    uint8_t i;

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

uint64_t from_ball_to_base3(ball bille,int choix)
{   uint64_t nb=choix;
    for(int i=0;i<bille;i++){
        nb=nb*10;
    }
    return nb;
}

ball from_base3_to_ball(uint64_t nb)
{
    int i;
    while(nb%10==0){
        nb=nb/10;
        i++;
    }
    return i;
}
ball transform_ball(transformation tr,ball bille,int choix)
{
    uint64_t code=from_ball_to_base3(bille,choix);
    uint8_t g[3][3];
    from_base3_to_grid(g,code);
    appliquer_transformation_base(g,tr);
    return from_base3_to_ball(from_grid_to_base3(g));
    

}