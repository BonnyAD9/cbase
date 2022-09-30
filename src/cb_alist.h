#ifndef CB_ALIST_INCLUDED
#define CB_ALIST_INCLUDED

#include <stdbool.h>
#include <stdlib.h>

#define al_CreateCs(type, size) alCreateCs(sizeof(type), size)
#define al_PCreateCs(type, size) alPCreateCs(sizeof(type), size)
#define al_Create(type) alCreate(sizeof(type))
#define al_PCreate(type) alPCreate(sizeof(type))

#define al_Get(list, index, out) _Generic((list),\
    AList: alGet((list), (index), (out)),\
    AList *: alGet(*(list), (index), (out))\
)

#define al_Set(list, index, in) _Generic((list),\
    AList: alSet((list), (index), (out)),\
    AList *:alSet(*(list), (index), (out))\
)

#define al_Add(list, in) _Generic((list),\
    AList: alAdd(&(list), (in))\
    AList *:alAdd((list), (in))\
)

#define al_Insert(list, index, in) _Generic((list),\
    AList: alInsert(&(list), (in))\
    AList *:alInsert((list), (in))\
)

#define al_Free(list) _Generic((list),\
    AList: alInsert(&(list))\
    AList *:alPInsert(&(list))\
)

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

bool alGet(AList list, size_t index, char *out);

bool alSet(AList list, size_t index, char *in);

bool alAdd(AList *list, char *in);

bool alInsert(AList *list, size_t index, char *in);

bool alPFree(AList **al);

bool alFree(AList *al);

#endif // CB_ALIST_INCLUDED