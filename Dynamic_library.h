#include <stdlib.h>
#include <stdio.h>

typedef struct _da
{
    int size_of_array;
    char * the_array;
    int length;
} dynamic_array;


dynamic_array* create_array(int size)

{
    dynamic_array *d;
    d = malloc(sizeof(dynamic_array)*1);
    d->length = 0;
    d->size_of_array = size;
    d->the_array = malloc(sizeof(char)*size);
    return d;
}

void free_dynamic_array(dynamic_array *d)
{
    free(d->the_array);
    free(d);
}

int add_char_to_dynamic_array(dynamic_array* d, char input)
{   
    int i;
    char* new_array;
    if (d->length >= d->size_of_array -1)
    {
        new_array = malloc(sizeof(char)*2*d->size_of_array);
        for(i = 0; i <= d->size_of_array; i++)
        {
            new_array[i] = d->the_array[i];
        }
        free(d->the_array);
        d->the_array = new_array;
        d->size_of_array = d->size_of_array * 2;
    } 
    d->the_array[d->length] = input;
    d->length++;
    d->the_array[d->length] = '\0';
    return 1;
}

char* get_string(dynamic_array* d)
{
    return d->the_array;
}

void add_str_to_array(dynamic_array *d, char* b)
{   
    int i;
    for (i = 0; b[i] != '\0'; i++)
    {
        add_char_to_dynamic_array(d,b[i]);
    }

}