#include "ball_arraylist.h"
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

ball  *find_ball_predecessor( ball_list * l, uint32_t size, _balls ball_value)
{
    ball *r = l->head;
    ball *p = NULL;
  
  
    for (uint32_t i=0; i<size; i++)
    {
        if (r->ball_value == ball_value) {
            break;
        }
        p = r;
        r = r->next; 
    }
    return p;
 }

void rem_ball(ball_arraylist* arl,_balls ball_value){
    ball * m = arl->occupied->head;
    ball * r = NULL;
    if(m->ball_value == ball_value)
    {
        
        add_on_head_of_occupied(arl->empty,rem_head_maillon(arl->occupied));
    }
    else{
        

        r = find_ball_predecessor(arl->occupied, arl->occupied->size, ball_value);
        m = r->next;
        r->next = m->next;
        arl->occupied->size -=1;
        add_on_head_of_occupied(arl->empty,m);
        return; 
    }
    
}