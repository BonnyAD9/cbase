#include "cb_alist.h"

#define AL_START_SIZE 16

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