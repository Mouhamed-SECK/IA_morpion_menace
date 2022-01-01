#include "game.h"

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
uint64_t codage_entier( uint8_t grille[3][3])
{
    
    uint64_t nb=0,p=6561;
    int i,j;
    for(i=0;i<3 ;i++){
        for(j=0;j<3;j++){
            nb=nb+grille[i][j]*p;
            p=p/3;
        }
    }
    return nb;
}
void codage_grille(uint8_t grille[3][3],uint64_t nb)
{
    int i,j;
    for(i=2;i>=0;i--)
    {
        for(j=2;j>=0;j--)
        {
            grille[i][j]=nb%3;
            nb=nb/3;
            
        }
    }

}