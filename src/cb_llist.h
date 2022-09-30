#ifndef CB_LLIST_INCLUDED
#define CB_LLIST_INCLUDED

#include <stdbool.h>

#define ll_Append(type, pll, value) ({\
    type v = value;\
    llAppend((pll), &v, sizeof(type));\
})

#define ll_Push(type, pll, value) ({\
    type v = value;\
    llPush((pll), &v, sizeof(type));\
})

#define ll_Insert(type, pll, index, value) ({\
    type v = value;\
    llInsert((pll), index, &v, sizeof(type));\
})

#define ll_AtP(type, ll, index) ((type *)llAt(ll, index)->value)
#define ll_At(type, ll, index) (*(type *)llAt(ll, index)->value)
#define ln_Create(type, value, next) lnCreate((next), (value), sizeof(type))

typedef struct LNode LNode;

struct LNode
{
    LNode *next;
    void *value;
    size_t size;
};

LNode *llCreate();

LNode **llPCreate();

void llAppend(LNode **ll, void *value, size_t size);

void llPush(LNode **ll, void *value, size_t size);

void llInsert(LNode *ll, size_t index, void *value, size_t size);

void llPop(LNode **ll, void *outVal, size_t *outSize);

LNode *llAt(LNode *ll, size_t index);

size_t llCount(LNode *ll);

LNode *llLast(LNode *ll);

LNode *lnCreate(LNode *next, void *value, size_t size);

bool llFree(LNode **ll);

bool llPFree(LNode ***ll);

#endif // CB_LLIST_INCLUDED