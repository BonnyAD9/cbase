#include "cb_alist.h"

#include <string.h>

#define AL_START_SIZE 16

void *_alAtP(AList list, size_t index);
void _alSet(AList list, size_t index, void *in);

AList alCreateCs(size_t elemSize, size_t size)
{
    AList al = 
    {
        .data = malloc(elemSize * size),
        .elemSize = elemSize,
        .allocated = size,
        .length = 0,
    };

    if (al.data)
        return al;

    al.allocated = 0;
    return al;
}

AList *alPCreateCs(size_t elemSize, size_t size)
{
    AList *al = malloc(sizeof(AList));
    if (!al)
        return NULL;

    *al = alCreateCs(elemSize, size);
    return al;
}

AList alCreate(size_t elemSize)
{
    return alCreateCs(elemSize, AL_START_SIZE);
}

AList *alPCreate(size_t elemSize)
{
    return alPCreateCs(elemSize, AL_START_SIZE);
}

bool alGet(AList list, size_t index, void *out)
{
    if (index >= list.length || !out)
        return false;

    memcpy(out, _alAtP(list, index), list.elemSize);
    return true;
}

void *alAt(AList list, size_t index)
{
    if (index >= list.length)
        return NULL;

    return list.data + index * list.elemSize;
}

void *_alAtP(AList list, size_t index)
{
    return list.data + index * list.elemSize;
}

bool alSet(AList list, size_t index, void *in)
{
    if (index >= list.length || !in)
        return false;

    _alSet(list, index, in);
    return true;
}

void _alSet(AList list, size_t index, void *in)
{
    memcpy(list.data + index * list.elemSize, in, list.elemSize);
}

bool alAdd(AList *list, void *in)
{
    if (list->length >= list->allocated)
    {
        size_t newSize = list->allocated < 2 ? 2 : list->allocated + list->allocated / 2;
        char *newData = realloc(list->data, newSize * list->elemSize);
        if (!newData)
            return false;
        list->allocated = newSize;
        list->data = newData;
    }

    _alSet(*list, list->length++, in);
    return true;
}

bool alInsert(AList *list, size_t index, void *in)
{
    if (index == list->length)
        return alAdd(list, in);

    if (!alAdd(list, _alAtP(*list, list->length - 1)))
        return false;

    memmove(
        _alAtP(*list, index + 1),
        _alAtP(*list, index),
        (list->length - 1 - index) * list->elemSize
    );

    _alSet(*list, index, in);
    return true;
}

bool alPFree(AList **al)
{
    if (!*al || !alFree(*al))
        return false;

    free(*al);
    return true;
}

bool alFree(AList *al)
{
    if (!al->data || !al->allocated)
        return false;

    free(al->data);
    al->allocated = 0;
    al->data = NULL;
    return true;
}