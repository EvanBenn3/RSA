#ifndef BIGINT_H
#define BIGINT_H

#include "shortint.h"

typedef struct {
    u8* bytes;
    u16 size;
} Bigint;

void initBigint(Bigint* n);
void resizeBigint(Bigint* n, u16 newSize);
void destroyBigint(Bigint* n);



#endif