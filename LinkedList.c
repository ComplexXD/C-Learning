#include <stdio.h>
#include <stdlib.h>

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
    free(a);


    return b;
}

listelem *dll_first_number(listelem *a)
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
    if (!a)
        return 0;

    listelem *pos;
    pos = dll_first_number(a);
    while(pos != NULL)
    {
        dll_remove(pos);
        pos = dll_first_number(a);
    }
    free(a->previous_number);
    return 0;
}

int dll_count(listelem *a) 
{
   int i = 0;
    listelem *pos = dll_first_number(a);
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



void dll_merge(listelem *a_list, listelem *b_list) //merge list b into a. // a and b must be sorted
{
    listelem *a = dll_first_number(a_list); //position a on first number
    listelem *b = dll_first_number(b_list); // position b on header

    if(dll_is_empty(b_list))                     // if b is empty, dont do shit
        return;

    printf("Checking list for emptyness\n");    
    if (dll_is_empty(a_list)) {
        printf("List is empty");
        dll_add(a_list, a, dll_get_value(b), DLL_AFTER);
        if (dll_is_last(b))
            return;
        b = dll_next(b);
    }
    printf("List is not empy\n");


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
    a = dll_first_number(a);
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
    a = dll_first_number(a);
    a = dll_previous(a);   
    return a;
}



int main(void)
{
    printf("Starting...\n");
    
    listelem *list_a = dll_create();
    listelem *list_b = dll_create();
    listelem *a = NULL; 
    listelem *b = NULL;


    // a = dll_add(list_a, a, 2, DLL_AFTER);
    // a = dll_add(list_a, a, 4, DLL_AFTER);
    // a = dll_add(list_a, a, 6, DLL_AFTER);

    b = dll_add(list_b, b, 0, DLL_AFTER);
    b = dll_add(list_b, b, 1, DLL_AFTER);
    b = dll_add(list_b, b, 3, DLL_AFTER);
    b = dll_add(list_b, b, 5, DLL_AFTER);
    b = dll_add(list_b, b, 10, DLL_AFTER);

//     dll_print_list(list_a, "List A");

    dll_print_list(list_b, "List B");

    dll_merge(list_a, list_b);

    dll_print_list(list_a, "Combined");
    
    


    return 0;
}
