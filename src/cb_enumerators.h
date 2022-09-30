#ifndef CB_ENUMERATORS_INCLUDED
#define CB_ENUMERATORS_INCLUDED

#include <stdlib.h>
#include <stdbool.h>

#define en_At(type, en, index) (*((type) *)enAt(en, index))
#define en_AtP(type, en, index) (((type) *)enAt(en, index))
#define en_Cur(type, en) (*((type) *)enCur(en))
#define en_CurP(type, en) (((type) *)enCur(en))

typedef enum
{
    EN_NEXT  = 0x01,
    EN_PREV  = 0x02,
    EN_AT    = 0x04,
    EN_LEN   = 0x08,
    EN_FREE  = 0x10,
    EN_RESET = 0x20,
} EnFlags;

typedef struct Enumerator
{
    void    *data;
    EnFlags  flags;
    bool   (*next    )(void *data);
    bool   (*prev    )(void *data);
    void  *(*at      )(void *data, size_t index);
    void  *(*cur     )(void *data);
    size_t (*curSize )(void *data);
    size_t (*len     )(void *data);
    void   (*freeData)(void *data);
    bool   (*reset   )(void *data);
} Enumerator;

bool enNext(Enumerator en);

bool enPrev(Enumerator en);

void *enAt(Enumerator en, size_t index);

void *enCur(Enumerator en);

size_t enCurSize(Enumerator en);

size_t enLen(Enumerator en);

void enFree(Enumerator en);

bool enReset(Enumerator en);

#endif // CB_ENUMERATORS_INCLUDED