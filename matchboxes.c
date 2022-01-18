/*
*Ce fichier permet de gerer une boite d'allumete et la table de hachage de toutes les boites d'allumetes
*elle contient toutes les fonctiond de mmanupulation d'une arraylist 
*Ajout suppression Mise à jour et libération
*/

#include "matchboxes.h"
#include <string.h>
#include <time.h>
#include "assert.h"




void  remove_matchbox(matchboxes_list *l)
{
    matchbox  *t = l->head;
    l->head = l->head->next;
    l->taille -= 1;
   free(t);

}

_Bool is_empty_matchboxes_list(matchboxes_list * l){
    return l->taille == 0;

} 

void free_menace(hash_table* menace ){
   
  for (int i = 0; i <= 7; i++)
    {
        matchbox  *m = menace->tab[i]->head;
        matchboxes_list *l = menace->tab[i];
        
        while ( m != NULL)
        { 
            matchbox *tmp = m;
            tmp = m;
            free_arraylist(m->arl);
            
            m = m->next;

            free(tmp->configurations);
        }

        while (is_empty_matchboxes_list(l))
        { 
          remove_matchbox(l);
          
        }
        free(l);
    }
    
    free(menace->tab);
    free(menace);
         
}
   
int sum_of_digits(int nombre ) {

    uint8_t g[3][3];
    int i;
    from_base3_to_grid(g,nombre); 
    uint64_t sommex=0,sommey=0;
    for(i=0;i<3;i++)
    {
        sommex=sommex+g[i][i]+g[i][2-i];
        sommey=sommey+g[1][i]+g[i][1];
    }
       return sommex*100+sommey;

}

uint32_t compute_hash_value(uint64_t configuration, uint32_t size) {
     return  sum_of_digits(configuration) % size; 
}

void init_configuration(uint64_t  configuration,matchbox *m)
{
    m->configurations[0] = configuration;

    uint8_t grid[3][3];
    from_base3_to_grid(grid, configuration);

    appliquer_transformation_base(grid,ROT_90);
    m->configurations[1] =  from_grid_to_base3(grid);

    appliquer_transformation_base(grid,ROT_90);
    m->configurations[2] =  from_grid_to_base3(grid);

    appliquer_transformation_base(grid,ROT_90);
    m->configurations[3] =  from_grid_to_base3(grid);

    appliquer_transformation_base(grid,ROT_90);
    appliquer_transformation_base(grid,MIROIR_VERT);
   m->configurations[4] =  from_grid_to_base3(grid);

    appliquer_transformation_base(grid,ROT_90);
   m->configurations[5] =  from_grid_to_base3(grid);

    appliquer_transformation_base(grid,ROT_90);
   m->configurations[6] =  from_grid_to_base3(grid);

    appliquer_transformation_base(grid,ROT_90);
   m->configurations[7] =  from_grid_to_base3(grid);

}

matchbox *new_matchbox(uint64_t  configuration, uint32_t g[3][3])
{
    matchbox *m = malloc(sizeof(matchbox));

    if(m==NULL)
    {
        assert(0);
    }

    
    init_configuration(configuration,m);
  

    m->arl   = new_arraylist(9);
    _balls ball = 0;
    for (uint32_t i = 0; i < 3; i++)
    {
    
       for ( uint32_t j = 0; j < 3; j++)
       {

          if (g[i][j] !=0) {
            uint32_t tmp = g[i][j];
            for (uint32_t k  = 0; k < tmp; k++)
            {
                add_on_head_of_arrayList(m->arl, ball);
            }
            
          }
          ball++;
       }
       
    }
    

    m->next = NULL;

    return m;
}

matchboxes_list *new_list()
{
    matchboxes_list *list = malloc(sizeof(matchboxes_list));

    if(list==NULL)
    {
        assert(0);
    }
    list->taille=0;
    list->head = NULL;

    return list;
}


hash_table* new_hash_table(uint32_t size)
{
    uint32_t i;

    hash_table *matchbox_hash_table = malloc( sizeof(hash_table) );
    assert(matchbox_hash_table != NULL);

    matchbox_hash_table->tab = malloc(size*sizeof(matchboxes_list*));    
    assert(matchbox_hash_table->tab != NULL);
    matchbox_hash_table->taille =size;
    for( i=0; i<size; i=i+1 )
    {

       matchbox_hash_table->tab[i] = new_list();
    }

    return matchbox_hash_table;

  
}

void add_head(matchboxes_list *l , uint32_t configuration, uint32_t g[3][3])
{
    matchbox *m = new_matchbox(configuration, g);
    m->next = l->head;
    l->head = m;
    l->taille += 1;
}


void init_matchbox_hash_table(char * matchbox, hash_table *th, uint32_t size) {

    FILE *f = fopen(matchbox, "rb");
    

    if (f== NULL) {
        fprintf(stderr, "ERREUR : fichier introuvable");
        assert(0);
    }

    uint32_t ball_arr[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    uint32_t configuration = 0;

    
    while (fscanf(f, "%d %d %d %d %d %d %d %d %d %d\n", &configuration, &ball_arr[0][0], &ball_arr[0][1], &ball_arr[0][2], &ball_arr[1][0], &ball_arr[1][1], &ball_arr[1][2], &ball_arr[2][0], &ball_arr[2][1] , &ball_arr[2][2]) == 10)
    {
     
        uint32_t index = compute_hash_value(configuration, size);
        add_head((th->tab[index]) , configuration,  ball_arr);
    }

  fclose(f);
}

void count_ball(matchbox *m, uint32_t ball_arr[3][3]) {
    ball *b =m->arl->occupied->head;

    while (b != NULL)
    {
        uint32_t i = b->ball_value/3;
        uint32_t j = b->ball_value%3;

        ball_arr[i][j]++;
        b =b->next;
    }
}

void save_menace_state(char * menace_state_file, hash_table *menace, uint32_t size) {

    FILE *f = fopen(menace_state_file, "w");
    

    if (f== NULL) {
        fprintf(stderr, "ERREUR : fichier introuvable");
        assert(0);
    }

    uint32_t ball_arr[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    uint32_t configuration = 0;

    
    for (uint32_t i = 0; i < size; i++)
    {
       matchbox *m = menace->tab[i]->head;

        while (m !=NULL)
        {
           count_ball(m, ball_arr);
            configuration = m->configurations[0];
           fprintf(f, "%09d %d %d %d %d %d %d %d %d %d\n", configuration, ball_arr[0][0], ball_arr[0][1], ball_arr[0][2], ball_arr[1][0], ball_arr[1][1], ball_arr[1][2], ball_arr[2][0], ball_arr[2][1] , ball_arr[2][2]);
        
            // on remet le tableau a zero
            memset(ball_arr, 0, sizeof(ball_arr)); 
            m = m->next;
        }
        
    }
    
    fclose(f);
}


_Bool is_configuration_in_array(uint64_t* configurations , uint64_t c, transformation *tr){

 for (uint32_t j = 0; j < 8; j++)
        {
         
          if (configurations[j] == c) {
              *(tr) = j;
              return 1;
          }
        }
    return 0;
} 

_balls get_menace_move(hash_table* menace, uint64_t configuration,opened_matchboxes_stack * ombs) {

    uint32_t index = compute_hash_value(configuration, 8);
    matchbox *m = menace->tab[index]->head;
    uint32_t list_size = menace->tab[index]->taille;
    transformation tr = 0;

    // on cherche la boite d'allumette 
    for (uint32_t i = 0; i < list_size; i++)
    {
        if (is_configuration_in_array(m->configurations, configuration, &tr)){
            break;
        } 
        m = m->next;
    }

    //on tire une bille au hazard
    uint32_t ball_number = m->arl->occupied->size;
    printf("%d\n",ball_number);
    uint32_t menace_move = rand() % ball_number;
    ball* b =  m->arl->occupied->head;
    for (uint32_t i = 0; i < menace_move; i++)
    {
        b = b->next;
    }
    omb_stack_push(ombs,m->arl,b->ball_value);
    return transform_balls(tr, b->ball_value, 1); 
}

void update_menace_state(game_result gr , opened_matchboxes_stack * ombs){
    
        opened_matchbox * tmp =ombs->head;
        while( tmp != NULL )
        {
            switch (gr)
            {
            case 0:
                rem_ball(tmp->barray,tmp->ball_value);
                break;
            case 1:
                add_on_head_of_arrayList(tmp->barray,tmp->ball_value);
                add_on_head_of_arrayList(tmp->barray,tmp->ball_value);
                add_on_head_of_arrayList(tmp->barray,tmp->ball_value);
                break;
            case 2:
                add_on_head_of_arrayList(tmp->barray,tmp->ball_value);
                break;
            default:
                break;
            }
            tmp=tmp->next;
        }

    
    
}

void make_last_move(uint8_t board_state[3][3]) {
      for  (uint32_t i = 0; i < 3; i++)
        {
            for(int j =0;j< 3 ;j++)
            {
                if(board_state[i][j]==0)
                    board_state[i][j]=2;
            } 
        }   
}



game_result gamer_vs_menace(hash_table *th, uint8_t board_state[3][3] , opened_matchboxes_stack * opened_matchbox)
{
    uint32_t box, move = 0 ,choice =0;

    for(uint32_t i =0 ;i<4;i++){
        move = get_menace_move(th, from_grid_to_base3(board_state),opened_matchbox);
        clock_t end_prog = clock();
        board_state[move / 3][move % 3]=2;
        make_board(board_state);

        if(is_win(board_state))
        {
            printf("MENACE WON !\n");
            return 1;
        }
        
        do{
            printf("CHOOSE A VALABLE CASE \n");
            scanf("%d",&choice);

        }while((choice>9) || (choice<1) || (board_state[(choice-1) / 3][(choice-1) % 3]!=0) );
            
        board_state[(choice-1) / 3][(choice-1) % 3]=1;
        make_board(board_state);

        if(is_win(board_state))
        {
            printf("CONGRATULATIONS YOU WON !\n");
            return 0;
        }
          
    
    }
    
    if(!is_win(board_state)){
        make_last_move(board_state);

        if(is_win(board_state))
        {
            printf("MENACE WON !\n");
            return 1;
        }
        else
        {
            printf("DRAW !\n");
            return 2;
        }
    }
   
}
game_result menace_vs_random(hash_table *th, uint8_t board_state[3][3] , opened_matchboxes_stack * opened_matchbox)
{
    uint32_t box, move = 0 ,choice =0;

    for(uint32_t i =0 ;i<4;i++){
        move = get_menace_move(th, from_grid_to_base3(board_state),opened_matchbox);
        clock_t end_prog = clock();
        board_state[move / 3][move % 3]=2;
        make_board(board_state);

        if(is_win(board_state))
        {
            printf("MENACE WON !\n");
            return 1;
        }
        
        
        do
        {
            box=rand()%8;

        }while(board_state[box /3][box % 3]!=0);
        board_state[box /3][box % 3]=1;
        if(is_win(board_state))
        {
            printf("RANDOM WON !\n");
            return 0;
        }

    }  
    
    if(!is_win(board_state)){
        make_last_move(board_state);

        if(is_win(board_state))
        {
            printf("MENACE WON !\n");
            return 1;
        }
        else
        {
            printf("DRAW !\n");
            return 2;
        }
    }
}