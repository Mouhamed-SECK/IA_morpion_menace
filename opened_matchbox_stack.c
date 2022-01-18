#include "opened_matchbox_stack.h"
#include "assert.h"



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
