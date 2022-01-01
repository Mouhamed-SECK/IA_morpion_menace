// les fonction manupilant les botes d'allumettes 


#include "matchboxes.h"


typedef struct _matchbox  {

    uint32_t match_box_id; // sum nombre pair
    uint32_t configurations[7];  

    //  tableau arrayList
    struct _matchbox *next;

} matchbox;


typedef  struct {
    uint32_t taille;
    matchbox *head;
} matchboxes_list;


typedef struct {

    matchboxes_list **tab;
    uint32_t taille;
    
} tab_hachage_matchboxes;


matchbox *new_matchbox(uint32_t machbox_id, uint32_t  configurations[7])
{
    matchbox *m = malloc(sizeof(matchbox));

    if(m==NULL)
    {
        assert(0);
    }

    m->configurations = configurations;
    m->match_box_id = machbox_id;

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