#ifndef CB_ALIST_INCLUDED
#define CB_ALIST_INCLUDED

#include <stdbool.h>
#include <stdlib.h>

#include "cb_enumerators.h"

#define al_CreateCs(type, size) alCreateCs(sizeof(type), size)
#define al_PCreateCs(type, size) alPCreateCs(sizeof(type), size)
#define al_Create(type) alCreate(sizeof(type))
#define al_PCreate(type) alPCreate(sizeof(type))
#define al_At(type, list, index) (*(type *)alAt(list, index))
#define al_AtP(type, list, index) ((type *)alAt(list, index))

#define al_Add(type, pList, value) ({\
    type v = (value);\
    alAdd((pList), &v);\
})

typedef struct AList
{
    char *data;
    size_t elemSize;
    size_t allocated;
    size_t length;
} AList;

AList alCreateCs(size_t elemSize, size_t size);

AList *alPCreateCs(size_t elemSize, size_t size);

AList alCreate(size_t elemSize);

AList *alPCreate(size_t elemSize);

bool alGet(AList list, size_t index, void *out);

void *alAt(AList list, size_t index);

bool alSet(AList list, size_t index, void *in);

bool alAdd(AList *list, void *in);

bool alInsert(AList *list, size_t index, void *in);

bool alPFree(AList **al);

bool alFree(AList *al);

bool alClear(AList *al);

Enumerator alEnumarate(AList *al);

#endif // CB_ALIST_INCLUDED