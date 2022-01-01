// toutes les fonctions utilitaires du jeu
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#define CONTINUE 0
#define FINISHED 1


typedef enum transformation{ID, ROT_90, ROT_180, ROT_270, MIROIR_VERT, MIROIR_HORIZ} transformation;

char print_value(uint8_t value);
void appliquer_transformation_base(uint8_t grille[3][3], transformation t);
void print_grille_2d(uint8_t grille[3][3], FILE *f);
void print_grille_1d(uint8_t grille[3][3], FILE *f);
uint8_t next_configuration(uint8_t grille[3][3]);


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


int main() {
    FILE *out = fopen("sortie1.txt", "w");
    
    uint8_t g[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    uint64_t i=0,temp,tab[304];

    print_all_transformations_1d(g, out);
    tab[0]=codage_entier(g);
    
    while(i<304)
    {   
        next_configuration(g);
        temp=codage_entier (g);
        if(is_valid_configuration(g) && !(is_in_table(codage_entier(g),tab)))
        {
            appliquer_transformation_base(g,ROT_90);
            if(!(is_in_table(codage_entier(g),tab)))
            {
               
                tab[i]=temp;
                i++;
            }
          
        }
        printf("%ld\n",tab[i]);  
    }
    printf("ici");
    for(i=0;i<304;i++)
    {
        
        codage_grille(g,tab[i]);
        print_all_transformations_1d(g, out);
    }
    
}