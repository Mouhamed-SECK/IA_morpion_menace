#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "matchboxes.h"

#define HASH_TABLE_SIZE 6





int main() {


    
    // uint8_t board_state[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    hash_table *th = new_hash_table(HASH_TABLE_SIZE);

    init_matchbox_hash_table("matchbox.txt", th, HASH_TABLE_SIZE);


    // uint32_t in = compute_hash_value(122001100, HASH_TABLE_SIZE);

   

    // for (uint32_t i = 0; i < HASH_TABLE_SIZE; i++)
    // {
    //       printf("M %d \n",th->tab[i]->taille);

    // }    


    matchbox  *m = th->tab[0]->head;
    while ( m != NULL)
    {

     
        for (int i = 0; i < 7; i++)
        {
               printf("%d \t ", m->configurations[i] );
        }
        printf("%d", m->match_box_id);
        printf("\n");
        
        m = m->next;
    }
    
}