#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "matchboxes.h"

#define HASH_TABLE_SIZE 8






int main() {


    
    // uint8_t board_state[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    hash_table *th = new_hash_table(HASH_TABLE_SIZE);

    init_matchbox_hash_table("matchbox.txt", th, HASH_TABLE_SIZE);


    // uint32_t in = compute_hash_value(202000121      , HASH_TABLE_SIZE);

    //  printf("M %d \n",in);

//   char square[10] = { 'o', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
   

    // for (uint32_t i = 0; i < HASH_TABLE_SIZE; i++)
    // {
    //       printf("M %d \n",th->tab[i]->head->arl->occupied->head->ball_value);

    // }    

        
    printf("M %d \n",th->tab[0]->head->configurations[0]);

        ball  *m = th->tab[0]->head->arl->occupied->head;

        while ( m != NULL)
        {
                    printf("M %d \n",m->ball_value);      
                    m = m->next;

        }


     


    // matchbox  *m = th->tab[0]->head;
    // while ( m != NULL)
    // {

     
    //     for (int i = 0; i < 7; i++)
    //     {
    //            printf("%d \t ", m->configurations[i] );
    //     }
    //     printf("%d", m->match_box_id);
    //     printf("\n");
        
    //     m = m->next;
    // }
}