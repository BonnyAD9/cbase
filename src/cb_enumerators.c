#include "cb_enumerators.h"

bool enNext(Enumerator e)
{
    return e.flags & EN_NEXT ? e.next(e.data) : false;
}

bool enPrev(Enumerator e)
{
    return e.flags & EN_PREV ? e.prev(e.data) : false;
}

void *enAt(Enumerator e, size_t index)
{
    return e.flags & EN_AT ? e.at(e.data, index) : NULL;
}

void *enCur(Enumerator e)
{
    return e.cur(e.data);
}

size_t enCurSize(Enumerator e)
{
    return e.curSize(e.data);
}

size_t enLen(Enumerator e)
{
    return e.flags & EN_LEN ? e.len(e.data) : 0;
}

void enFree(Enumerator e)
{
    if (e.flags & EN_FREE)
        e.freeData(e.data);
}

bool enReset(Enumerator e)
{
    return e.flags & EN_RESET ? e.reset(e.data) : 0;
}
