#include <stdio.h>

#include "cb_alist.h"

int main()
{
    AList *al = al_PCreate(int);

    for (int i = 0; i < 10; i++)
        al_Add(int, al, i);

    for (int i = 0; i < al->length; i++)
        printf("%d ", al_At(int, *al, i));

    printf("\n");

    al_At(int, *al, 2) = 10;
    
    for (int i = 0; i < al->length; i++)
        printf("%d ", al_At(int, *al, i));
}
