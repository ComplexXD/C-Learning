#include <stdlib.h>

typedef struct _listelem
{
    int number;
    struct _listelem *next_number;
    struct _listelem *previous_number;
} listelem;


listelem* dll_create();

{
    listelem *a = malloc(sizeof(listelem));
    a->number = 0;
    a->next_number = NULL;
    a->previous_number = NULL;

return a;
}


listelem* dll_add(listelem *a, int value)
{
    listelem *new = malloc(sizeof(listelem));
    new-> number = value;

    listelem *b = a->next_number;

    a->next_number = new;

    new-> previous_number = a;
    new->next_number = b;
    
    if (b)
        b->previous_number = new;
    return new;
}


listelem* dll_previous(listelem *a)
{
    if (a->previous_number)
    {
        if (a->previous_number->previous_number == NULL)
            return NULL;
    }

    return a->previous_number;
}


listelem* dll_remove(listelem *a)
{
    if(a->previous_number == NULL)
        return NULL;

    listelem *b = a->previous_number;
    listelem *c = a->next_number;
    b->next_number = c;
    if (c)
        c->previous_number = b;
    free(a);


    return b;
}

listelem *dll_first(listelem *a)
{
    while(dll_previous(a) != NULL)
       a = dll_previous(a); 
    return a->next_number;
}


listelem* dll_next(listelem *a)
{
    return a->next_number;
}

int dll_get_value(listelem *a)
{
    return a->number;
}

int dll_delete_list(listelem *a)
{   
    listelem *pos;
    while(dll_first(a) != NULL)
    {
        pos = dll_first(a);
        dll_remove(pos);
    }
    free(a);
    return 0;
}

int dll_count(listelem *a) 
{
   int i = 0;
    listelem *pos = dll_first(a);
    while(pos)
    {
        i++;
        pos = dll_next(pos);
    }
    return i;
}


listelem* dll_last(listelem *a)
{
    while(dll_next(a))
        a = dll_next(a);
    return a;
}


listelem* dll_find(listelem *a, int value) //assume head is given
{
    while (dll_next(a) != NULL)
    {
        a = dll_next(a);
        if(a->next_number == value)
            return a;
    }
    
    return NULL;

}
