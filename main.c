#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "matchboxes.h"

#define HASH_TABLE_SIZE 8



int main() {    

    
    int x,i=0;
    int res;
    hash_table *th = new_hash_table(HASH_TABLE_SIZE);
    
    srand(time(NULL));
    init_matchbox_hash_table("matchbox.txt", th, HASH_TABLE_SIZE);

   
    printf("CHOISISSEZ :\n 1-MENACE JOUE SEULE   2-JOUER CONTRE MENACE   0-QUITTER \n ");
    scanf("%d",&x);
    
    
    if(x==2){
        gamer_vs_menace(th);
        save_menace_state("matchbox1.txt", th, HASH_TABLE_SIZE);
    

        free_menace(th);
    }else if(x==1)
    {
        menace_vs_menace(th,4);
    }
    
    
 
}