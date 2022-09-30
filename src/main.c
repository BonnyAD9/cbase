#include <stdio.h>

#include "cb_alist.h"

int main()
{
    AList *al = al_PCreate(int);

    for (int i = 0; i < 10; i++)
        al_Add(int, al, 100 + i);

    Enumerator en = alEnumarate(al);

    do printf("%d ", en_Cur(int, en));
    while (enNext(en));

    enFree(en);
    alFree(al);
}
