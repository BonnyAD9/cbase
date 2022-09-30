#ifndef CB_ALIST_INCLUDED
#define CB_ALIST_INCLUDED

#include <stdbool.h>
#include <stdlib.h>

#define al_CreateCs(type, size) alCreateCs(sizeof(type), size)
#define al_PCreateCs(type, size) alPCreateCs(sizeof(type), size)
#define al_Create(type) alCreate(sizeof(type))
#define al_PCreate(type) alPCreate(sizeof(type))

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

void *alGetP(AList list, size_t index);

bool alSet(AList list, size_t index, void *in);

bool alAdd(AList *list, void *in);

bool alInsert(AList *list, size_t index, void *in);

bool alPFree(AList **al);

bool alFree(AList *al);

#endif // CB_ALIST_INCLUDED