#include "dij.h"
#include <stdio.h>

void dijstra_to_stdout(int *path, int result, int size )
{
    int i;
    printf("Wartość najkrótszej drogi w grafie: %d",result);
    printf("Kolejne wierzchoki wchodzące w skład najkrótszej drogi:\n");
    for(i = 0; i < size; i++)
    {
        printf("%d ",path[i]);
        if(path[i] < size-1)
            printf("-> ");
    }

}


