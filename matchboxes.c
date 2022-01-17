// les fonction manupilant les botes d'allumettes 

#include "matchboxes.h"
#include <string.h>
#include "assert.h"

tab_maillon* new_tab_maillon(uint32_t size)
{
    uint32_t i;

    //On construit le tab_maillon
    tab_maillon *t = malloc(sizeof(tab_maillon));
    assert(t!=NULL);

    //Et on construit le tableau de maillons associes au tab_maillon
    t->balls_array = malloc(size *sizeof(ball));
    assert(t->balls_array != NULL);

    //Et on lie les maillons du tableau entre eux
    for( i=0; i<size-1; i=i+1 )
    {
        t->balls_array[i].next = &(t->balls_array[i+1]);
    }
     t->balls_array[ size-1] .next = NULL;

    t->taille_tab = size;
    return t;
}


void add_head_maillon (list_tab_maillon* l,  tab_maillon *t) {

    // assert((tab_maillon!=NULL));

    t->next = l->head;
    l->head = t;
    l->size += 1;
}

tab_maillon* remove_arraylist_head (list_tab_maillon* l) {

    // assert((tab_maillon!=NULL));

  tab_maillon  *t = l->head;
    l->head = l->head->next;
    l->size -= 1;
    return t;
}

 void agrandir_liste_libre(ball_arraylist *arl, uint32_t size)
 {
    tab_maillon *t;

    // assert( est_vide(arl->empty) );

    //On construit un tableau de maillons
    t = new_tab_maillon(size);

    //Et on l'ajoute a la liste contenant tous nos tableaux
    add_head_maillon(arl->ltm, t); //La fonction d'ajout en head d'une liste de


    //Enfin, on ajoute les maillons "manuellement" a la liste des maillons libres
    arl->empty->head = &( t->balls_array[0] );
    arl->empty->size = t->taille_tab;

 }

ball_list *new_liste()
 {
    ball_list *r = malloc(sizeof(ball_list));
    if(r==NULL)
    {
    assert(0);
    }
    r->size=0;
    r->head = NULL;
    
    return r;
 }

list_tab_maillon *new_liste_tab_maillons()
{
    list_tab_maillon *r = malloc(sizeof(list_tab_maillon));
    if(r==NULL)
    {
    assert(0);
    }
    r->size=0;
    r->head = NULL;
    
    return r;
 }

ball_arraylist* new_arraylist(uint32_t init_size)
 {
    ball_arraylist *arl;

    //On construit l'arraylist
    arl = malloc(sizeof(ball_arraylist));
    assert(arl != NULL);

    //On construit un tableau de maillons
    arl->empty = new_liste();
    arl->occupied = new_liste();
    arl->ltm = new_liste_tab_maillons();

    //On cree des maillons libres
    agrandir_liste_libre(arl, init_size);

    return arl;
 }

_Bool est_vide(ball_list *l ) {
    return l->head == 0;
}

 

void  add_on_head_of_occupied (ball_list* l,  ball *t) {
    t->next = l->head;
    l->head = t;
    l->size += 1;
}


ball* rem_head_maillon(ball_list *l)
{
    ball  *t = l->head;
    l->head = l->head->next;
    l->size -= 1;
    return t;

}

void  remove_matchbox(matchboxes_list *l)
{
    matchbox  *t = l->head;
    l->head = l->head->next;
    l->taille -= 1;
   free(t);

}


 void add_on_head_of_arrayList(ball_arraylist* arl, _balls d)
{
    ball *l;

    //On agrandit la liste des maillons libres si elle est vide...
    if( est_vide(arl->empty) )

    {
        agrandir_liste_libre(arl, 1.5*arl->occupied->size); //Ici, le coefficient 1.5
    }

    //On recupere un maillon libre
    l = rem_head_maillon( arl->empty );

    //On y stocke la donnee
    l->ball_value = d;
    //Et on place le maillon dans la liste des occupes
    add_on_head_of_occupied(arl->occupied, l);

}

_Bool is_empty_arraylist_ltm (list_tab_maillon * l) {
    return l->size == 0;
}  


void free_arraylist(ball_arraylist *arl)
 {
    tab_maillon *t;
    while( ! is_empty_arraylist_ltm( arl->ltm ) )
    {
        t  = remove_arraylist_head( arl->ltm );
        free(t->balls_array);
        free(t);
    }

    free(arl->empty);
    free(arl->occupied);
    free(arl->ltm);

    free(arl);


}
void rem_ball(ball_arraylist* arl,_balls ball_value){
    ball * head_of_occupied = arl->occupied->head;
    ball * tmp;
    if(head_of_occupied->ball_value == ball_value)
    {
        
        add_on_head_of_occupied(arl->empty,rem_head_maillon(arl->occupied));
    }
    else{
        
        while(head_of_occupied != NULL){
            if(head_of_occupied->ball_value == ball_value)
            {   
                
                tmp=head_of_occupied->next->next;
                head_of_occupied->next=tmp->next;
                add_on_head_of_occupied(arl->empty,tmp);
            }
            head_of_occupied = head_of_occupied->next;
        }
        
        
    }
    
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


matchbox *new_matchbox(uint64_t  configuration, uint32_t g[3][3])
{
    matchbox *m = malloc(sizeof(matchbox));

   // m->configurations = malloc(8 *sizeof(uint64_t));

    if(m==NULL)
    {
        assert(0);
    }

 
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

     appliquer_transformation_base(grid, ROT_90);
    appliquer_transformation_base(grid, MIROIR_VERT);
    m->configurations[8] =  from_grid_to_base3(grid);

  

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

opened_matchbox *new_maillon(ball_arraylist * barray,_balls ball_value)
{
    opened_matchbox *m = malloc(sizeof(opened_matchbox));
    if(m==NULL)
    {
        assert(0);
    }
    m->barray=barray;
    m->ball_value=ball_value;
    return m;
}

opened_matchboxes_stack * omb_stack_new()
{
    opened_matchboxes_stack *r = malloc(sizeof(opened_matchboxes_stack));
    if(r==NULL)
    {
    assert(0); 
    }
    r->head = NULL;
    return r;
}
void omb_stack_push(opened_matchboxes_stack *p,ball_arraylist * barray,_balls ball_value){
    opened_matchbox *m = new_maillon(barray,ball_value);
    m->next = p->head;
    p->head = m;  
}

void omb_stack_pop(opened_matchboxes_stack *p){
    opened_matchbox *t = p->head;
    p->head = p->head->next;
    free(t);

}

void omb_stack_free(opened_matchboxes_stack *p){
    while( p->head != NULL )
    {
        omb_stack_pop(p);
    }

    free(p);
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
        // printf("CONFIGURATION %d \n", &configuration);
       
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
    //printf("%d", b->ball_value);
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
                
                printf("ici\n");
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

void gamer_vs_menace(hash_table *th)
{
    opened_matchboxes_stack * ombs = omb_stack_new();
    uint8_t board_state[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    
    uint32_t move,choice;
    int i,res;
    for(i =0 ;i<4;i++){
        
        
        move = get_menace_move(th, from_grid_to_base3(board_state),ombs);
       
        board_state[move / 3][move % 3]=1;
        make_board(board_state);

        if(is_win(board_state))
        {
            printf("MENACE WON !\n");
            res=1;
            break;
        }

        printf("choisissez une position entre 0 et 8\n");
        scanf("%d",&choice);
        board_state[choice / 3][choice % 3]=2;
        make_board(board_state);

        if(is_win(board_state))
        {
            printf("CONGRATULATIONS YOU WON !\n");
            res=0;
            break;
        }

    
    }
    
    if(!is_win(board_state)){
        for  (i = 0; i < 3; i++)
        {
            for(int j =0;j< 3 ;j++)
            {
                if(board_state[i][j]==0)
                    board_state[i][j]=1;
            } 
        }   

        if(is_win(board_state))
        {
            printf("MENACE WON !\n");
            res=1;
        }
        else
        {
            printf("DRAW !\n");
            res=2;
        }
    }
    update_menace_state(res,ombs);
    
}

void menace_vs_menace(hash_table *th,int N)
{
    for(int k=0;k<N;k++)
    {
        init_matchbox_hash_table("matchbox1.txt", th, HASH_TABLE_SIZE);
        opened_matchboxes_stack * ombs1 = omb_stack_new();
        opened_matchboxes_stack * ombs2 = omb_stack_new();
        uint8_t board_state[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
        
        uint32_t move,choice;
        int i,res;
        for(i =0 ;i<4;i++){
        
        
            move = get_menace_move(th, from_grid_to_base3(board_state),ombs1);
       
            board_state[move / 3][move % 3]=1;
            make_board(board_state);
            printf("ici\n");
            if(is_win(board_state))
            {
                res=1;
                break;
            }

        
            move = get_menace_move(th, from_grid_to_base3(board_state),ombs2);
       
            board_state[move / 3][move % 3]=1;
            make_board(board_state);

            if(is_win(board_state))
            {
                res=0;
                break;
            }

    
        }
    
        if(!is_win(board_state)){
            for  (i = 0; i < 3; i++)
            {
                for(int j =0;j< 3 ;j++)
                {
                    if(board_state[i][j]==0)
                        board_state[i][j]=1;
                } 
            }   

            if(is_win(board_state))
            {
                printf("MENACE WON !\n");
                res=1;
            }
            else
            {
                printf("DRAW !\n");
                res=2;
            }
        }
        
    update_menace_state(res,ombs1);
    save_menace_state("matchbox1.txt", th, HASH_TABLE_SIZE);
    free_menace(th);
    }
}