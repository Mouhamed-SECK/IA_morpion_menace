#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "matchboxes.h"

#define HASH_TABLE_SIZE 8



void board(char* square)
{
    system("cls");
    printf("\n\n\tTic Tac Toe\n\n");

    printf("Player 1 (X)  -  Player 2 (O)\n\n\n");


    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", square[1], square[2], square[3]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", square[4], square[5], square[6]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", square[7], square[8], square[9]);

    printf("     |     |     \n\n");
}


int main() {


    
    // uint8_t board_state[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    hash_table *th = new_hash_table(HASH_TABLE_SIZE);

    init_matchbox_hash_table("matchbox.txt", th, HASH_TABLE_SIZE);


    // uint32_t in = compute_hash_value(202000121      , HASH_TABLE_SIZE);

    //  printf("M %d \n",in);

  char square[10] = { 'o', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
   

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