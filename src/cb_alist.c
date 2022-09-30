#include "cb_alist.h"

#include <string.h>

#define AL_START_SIZE 16

typedef struct ALEnumerator
{
    AList *list;
    size_t pos;
} ALEnumerator;

void *_alAt(AList list, size_t index);
void _alSet(AList list, size_t index, void *in);
bool _alAdd(AList *list, void *in);

ALEnumerator *_createALEnumerator(AList *al, size_t pos);
bool _aleNext(ALEnumerator *ale);
bool _alePrev(ALEnumerator *ale);
void *_aleAt(ALEnumerator *ale, size_t index);
void *_aleCur(ALEnumerator *ale);
size_t _aleSize(ALEnumerator *ale);
size_t _aleLen(ALEnumerator *ale);
void _aleFree(ALEnumerator *ale);
bool _aleReset(ALEnumerator *ale);

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

    memcpy(out, _alAt(list, index), list.elemSize);
    return true;
}

void *alAt(AList list, size_t index)
{
    if (index >= list.length)
        return NULL;

    return list.data + index * list.elemSize;
}

void *_alAt(AList list, size_t index)
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
    if (!list || !in)
        return false;

    return _alAdd(list, in);
}

bool _alAdd(AList *list, void *in)
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
    if (!list || !in)
        return false;

    if (index == list->length)
        return _alAdd(list, in);

    if (!_alAdd(list, _alAt(*list, list->length - 1)))
        return false;

    memmove(
        _alAt(*list, index + 1),
        _alAt(*list, index),
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

bool alClear(AList *al)
{
    if (!al)
        return false;

    al->length = 0;
    return true;
}

Enumerator alEnumarate(AList *al)
{
    Enumerator en = { .flags = EN_NONE };
    if (!al)
        return en;

    en.data = _createALEnumerator(al, 0);
    if (!en.data)
        return en;

    en.flags    = EN_ALL;
    en.next     = (bool   (*)(void *))_aleNext;
    en.prev     = (bool   (*)(void *))_alePrev;
    en.at       = (void  *(*)(void *, size_t))_aleAt;
    en.cur      = (void  *(*)(void *))_aleCur;
    en.curSize  = (size_t (*)(void *))_aleSize;
    en.len      = (size_t (*)(void *))_aleLen;
    en.freeData = (void   (*)(void *))_aleFree;
    en.reset    = (bool   (*)(void *))_aleReset;

    return en;
}

ALEnumerator *_createALEnumerator(AList *al, size_t pos)
{
    ALEnumerator *ale = malloc(sizeof(ALEnumerator));
    if (!ale)
        return NULL;

    ale->list = al;
    ale->pos = pos;
    return ale;
}

bool _aleNext(ALEnumerator *ale)
{
    if (ale->pos + 1 >= ale->list->length)
        return false;

    ++ale->pos;
    return true;
}

bool _alePrev(ALEnumerator *ale)
{
    if (ale->pos == 0)
        return false;

    --ale->pos;
    return true;
}

void *_aleAt(ALEnumerator *ale, size_t index)
{
    return alAt(*ale->list, index);
}

void *_aleCur(ALEnumerator *ale)
{
    return alAt(*ale->list, ale->pos);
}

size_t _aleSize(ALEnumerator *ale)
{
    return ale->list->elemSize;
}

size_t _aleLen(ALEnumerator *ale)
{
    return ale->list->length;
}


void _aleFree(ALEnumerator *ale)
{
    free(ale);
}

bool _aleReset(ALEnumerator *ale)
{
    ale->pos = 0;
    return true;
}