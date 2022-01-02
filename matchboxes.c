// les fonction manupilant les botes d'allumettes 

#include "matchboxes.h"
#include "assert.h"





tab_maillon* new_tab_maillon(uint32_t size)
{
    uint32_t i;

    //On construit le tab_maillon
    tab_maillon *t = malloc(sizeof(tab_maillon));


    //Et on construit le tableau de maillons associes au tab_maillon
    t->balls_array = malloc(size *sizeof(ball));
    assert(t->balls_array != NULL);

    //Et on lie les maillons du tableau entre eux
    for( i=0; i<size-1; i=i+1 )
    {
        t->balls_array[i].next = &(t->balls_array[i+1]);
    }
    // t->balls_array[ size-1] = NULL;

    t->taille_tab = size;
    return t;
}


void add_tete_maillon (list_tab_maillon* l,  tab_maillon *t) {

    // assert((tab_maillon!=NULL));

    t->next = l->head;
    l->head = t;
    l->size += 1;
}

 void agrandir_liste_libre(ball_arraylist *arl, uint32_t size)
 {
    tab_maillon *t;

    // assert( est_vide(arl->empty) );

    //On construit un tableau de maillons
    t = new_tab_maillon(size);

    //Et on l'ajoute a la liste contenant tous nos tableaux
    add_tete_maillon(arl->ltm, t); //La fonction d'ajout en tete d'une liste de


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


ball* rem_tete_maillon(ball_list *l)
{
    ball  *t = l->head;
    l->head = l->head->next;
    l->size -= 1;
    return t;

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
    l = rem_tete_maillon( arl->empty );

    //On y stocke la donnee
    l->ball_value = d;
    //Et on place le maillon dans la liste des occupes
    add_on_head_of_occupied(arl->occupied, l);

}




int sum_of_odd_digits(int n) {

	int r, sum = 0;

	// reading each digit of n
	while (n > 0) {

		r = n % 10;	// storing rightmost digit of n in r
		n = n / 10;	// removing rightmost digit of n

		// if r is odd, add r to sum
		if (r % 2 == 0)
			sum = sum + r;

	}

	return sum;
}
int sum_of_digits(int n) {

	int m, sum = 0;


    while(n>0)    
    {    
        m=n%10;    
        sum=sum+m;    
        n=n/10;    
    } 
	return sum;
}



uint32_t compute_hash_value(uint64_t configuration, uint32_t size) {
     return  sum_of_digits(configuration) % size; 
}


matchbox *new_matchbox(uint64_t  configuration, uint32_t g[3][3])
{
    matchbox *m = malloc(sizeof(matchbox));

    if(m==NULL)
    {
        assert(0);
    }
    m->match_box_id = sum_of_odd_digits(configuration);



    m->configurations[0] = configuration;

    uint8_t grid[3][3] =  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    uint64_t tmp = 0;

    for (uint8_t i = 1; i < 7; i++)
    {
       from_base3_to_grid(grid, configuration);
       appliquer_transformation_base(grid, i);
       tmp = from_grid_to_base3(grid);

      m->configurations[i] = tmp;

    }

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
        // printf("CONFIGURATION %d \n", &configuration);
       
        add_head((th->tab[index]) , configuration,  ball_arr);

    }
}