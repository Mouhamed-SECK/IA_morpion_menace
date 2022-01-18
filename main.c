#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "matchboxes.h"

#define HASH_TABLE_SIZE 8

void display_menu() {

        system("cls");
    	printf("\t\t\t\t  ***********************  \n");
		printf("\t\t\t\t||     WELCOME TO THE    ||\n");
		printf("\t\t\t\t||       MENACE IA       ||\n");
		printf("\t\t\t\t  ***********************  \n");
        printf("\n");
        printf("\n");
		printf("\t\t\t\t=======TIC TAC TOE========\n");
		printf("\t\t\t\t===========================\n");

        printf("\n");
		printf("\t\t\t\t\tMAIN MENU: \n\n");
		printf("\t\t\t\t1--> MENACE VS GAMER\n\n");
		printf("\t\t\t\t2--> MENACE VS RANDOM\n\n");
		printf("\t\t\t\t3--> RESET MENACE SYSTEM\n\n");
		printf("\t\t\t\t4--> Quit\n[");

        printf("\t\t\t\tMake your choice  : _\n");
	

}


int main() {    
    int choice = 0;
    game_result result = 0;

    hash_table *menace = new_hash_table(HASH_TABLE_SIZE);
    opened_matchboxes_stack * opened_matchboxes = omb_stack_new();

    uint8_t board_state[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    
   
    srand(time(NULL));
    init_matchbox_hash_table("matchbox.txt", menace, HASH_TABLE_SIZE);

    display_menu();
    scanf("%d",&choice);
   
    if(choice==1){
        gamer_vs_menace(menace, board_state, opened_matchboxes, &result);  
    }

    update_menace_state(result,opened_matchboxes);


    save_menace_state("matchbox.txt", menace, HASH_TABLE_SIZE);
    free_menace(menace);
    
}