#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "matchboxes.h"

#define HASH_TABLE_SIZE 8






int main() {    
    // uint8_t board_state[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    hash_table *th = new_hash_table(HASH_TABLE_SIZE);

    srand(time(NULL));

    init_matchbox_hash_table("matchbox.txt", th, HASH_TABLE_SIZE);

    uint32_t move = get_menace_move(th, 000000000);


    switch (move)
    {
    case 0:
        printf("PINK \n");
        break;
    case 2:
        printf("RED \n");
        break;
    case 3:
        printf("AMBER \n");
        break;
    case 4:
        printf("GREEN \n");
        break;
    case 5:
        printf("GOLD \n");
        break;
    case 6:
        printf("BLACK \n");
        break;
    case 7:
        printf("SILVER \n");
        break;
    case 8:
        printf("LILAC \n");
        break;

    case 9:
        printf("WHITE \n");
        break;
    default:
        break;
    }

    save_menace_state("matchbox1.txt", th, HASH_TABLE_SIZE);

   free_menace(th);
 
}