
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/timeb.h>

#define DLL_BEFORE 0
#define DLL_AFTER  1


typedef struct _listelem
{
    int number;
    struct _listelem *next_number;
    struct _listelem *previous_number;
} listelem;


listelem* dll_create()
{
    listelem *a = malloc(sizeof(listelem));
    a->number = 0;
    a->next_number = NULL;
    a->previous_number = NULL;

return a;
}


listelem* dll_add(listelem *list, listelem *a, int value, int where)
{   
    listelem *new = malloc(sizeof(listelem));
    new-> number = value;

    if(a == NULL)
    {
        a = list;
    }


    if (where == DLL_BEFORE && a->previous_number)
    {
        a = a->previous_number;
    }
   
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
    // free(a);
    return b;
}

listelem *dll_get_first_pos(listelem *a)
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


int dll_count(listelem *a) 
{
   int i = 0;
    listelem *pos = dll_get_first_pos(a);
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

// Is this the last element of the  list
int dll_is_last(listelem *a)
{
    if (a == NULL)
        return 1;
    if((a->next_number) == NULL)
        return 1;
    else;
        return 0;
}

listelem* dll_find(listelem *a, int value) //assume head is given
{
    while (dll_next(a) != NULL)
    {
        a = dll_next(a);
        if((a->number) == value)
            return a;
    }
    
    return NULL;

}

int dll_is_empty(listelem *a_list)
{
    if(a_list->next_number == NULL)
        return 1;
    else
        return 0;
}

int dll_delete_list(listelem *a_list)
{   
    listelem *pos;
    while(!dll_is_empty(a_list))
    {
        pos = dll_get_first_pos(a_list);
        dll_remove(pos);
    }
    free(a_list);
    return 0;
}


void dll_out_list(listelem *a)
{
    if(dll_is_empty(a))
    {
        printf("[]");
        return;
    }
    int place = 1;
    a = dll_get_first_pos(a);
    printf("[");
    while(a) 
    {
        printf("%d ",dll_get_value(a));
        a = dll_next(a);
        place++;
    }
    printf("] ");
    return;
}


listelem *dll_split(listelem *a_list)
{
    int half = (dll_count(a_list) -1) / 2;
    int i;

    listelem *pos = dll_get_first_pos(a_list);
    for(i = 0; i <= half; i++) 
    {
        pos = dll_next(pos);
    }   
    listelem *newhead = dll_create();
    newhead->next_number = pos;
    if (pos) {
        dll_previous(pos)->next_number = NULL;
        pos->previous_number = newhead;
    }
    return newhead;
}


void dll_merge(listelem *a_list, listelem *b_list) //merge list b into a. // a and b must be sorted
{
    listelem *a = dll_get_first_pos(a_list); //position a on first number
    listelem *b = dll_get_first_pos(b_list); // position b on header

   
    if(dll_is_empty(b_list))                     // if b is empty, dont do shit
        return;
  
    if (dll_is_empty(a_list)) {
        a = dll_add(a_list, a, dll_get_value(b), DLL_AFTER);
        if (dll_is_last(b)) {
            return;
        }
        b = dll_next(b);
    }

    while(1)
    {
        while((dll_get_value(a) < dll_get_value(b)))
            {
                if(dll_is_last(a))
                    break;
                else;
                a = dll_next(a);
            }
        if(dll_is_last(a) && (dll_get_value(a) < dll_get_value(b)))
                dll_add(a_list, a, dll_get_value(b), DLL_AFTER);
        else
            dll_add(a_list, a, dll_get_value(b), DLL_BEFORE);
        
        if (dll_is_last(b))
            break;
    
        b = dll_next(b);

    }
    return;
}

void dll_print_list(listelem *a, char* listname)
{
    if(dll_is_empty(a))
    {
        printf("%s is empty", listname);
        return;
    }
    int place = 1;
    a = dll_get_first_pos(a);
    printf("\n");
    while(a) 
    {
        printf("%s Value %d is: %d\n",listname, place, dll_get_value(a));
        a = dll_next(a);
        place++;
    }
    printf("\n");
    return;
}



listelem* dll_get_head(listelem *a)
{
    a = dll_get_first_pos(a);
    a = dll_previous(a);   
    return a;
}

listelem * dll_sort(listelem *a_list)
{
    listelem *b_list;

    if(dll_is_empty(a_list))
        return a_list;
    if(dll_count(a_list) == 1)
        return a_list;
    
    b_list = dll_split(a_list);

    dll_sort(a_list);
    dll_sort(b_list);

    dll_merge(a_list, b_list);

    dll_delete_list(b_list);

    return a_list;


}
