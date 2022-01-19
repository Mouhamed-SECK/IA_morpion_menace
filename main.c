#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "matchboxes.h"

#define HASH_TABLE_SIZE 8

void display_menu() {

        //system("clear");
    	printf("\t\t\t  ***********************  \n");
		printf("\t\t\t||     WELCOME TO THE    ||\n");
		printf("\t\t\t||       MENACE IA       ||\n");
		printf("\t\t\t  ***********************  \n");
        printf("\n");
        printf("\n");
		printf("\t\t\t=======TIC TAC TOE========\n");
		printf("\t\t\t===========================\n");

        printf("\n");
		printf("\t\t\t\tMAIN MENU: \n\n");
		printf("\t\t\t1--> MENACE VS GAMER\n\n");
		printf("\t\t\t2--> MENACE VS RANDOM\n\n");
		printf("\t\t\t3--> RESET MENACE SYSTEM\n\n");
		printf("\t\t\t4--> Quit\n[");

        printf("\t\t\tMake your choice  : _\n");
	

}


int main() {    
    uint32_t N,choice = 0;

    hash_table *menace = new_hash_table(HASH_TABLE_SIZE);
    
    
    srand(time(NULL));
    
    init_matchbox_hash_table("matchbox.txt", menace, HASH_TABLE_SIZE);
    display_menu();
    scanf("%d",&choice);

    while(choice !=4)
    {   
        
        uint8_t board_state[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
        switch (choice)
        {
        case 1:
            
            gamer_vs_menace(menace, board_state);  
            
            break;
        case 2:
            printf("CHOOSE A NUMBER\n");
            scanf("%d",&N);
            for(uint32_t i=0;i<N;i++)
            {   
                uint8_t board_state[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
                menace_vs_random(menace, board_state);
                
                
            }
            break;
        case 3:
            reset_menace();
            free_menace(menace);
            menace = new_hash_table(HASH_TABLE_SIZE);
            init_matchbox_hash_table("matchbox.txt", menace, HASH_TABLE_SIZE);
            break;
        default:
            break;
        }

        display_menu();
        scanf("%d",&choice);

    }

    save_menace_state("matchbox.txt", menace, HASH_TABLE_SIZE);
    free_menace(menace);
    
}