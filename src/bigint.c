#include "bigint.h"
#include <stdlib.h>

void initBigint(Bigint* n) {
    n->bytes = NULL;
    n->size = 0;
}

void resizeBigint(Bigint* n, u16 newSize) {
    n->bytes = realloc(n->bytes, newSize);
    n->size = newSize;
}

void destroyBigint(Bigint* n) {
    free(n->bytes);
    n->bytes = NULL;
    n->size = 0;
}

Bigint addBigint(Bigint a, Bigint b) {
    Bigint result;
    initBigint(&result);

    u16 maxSize = (a.size > b.size) ? a.size : b.size;
    maxSize++;
    resizeBigint(&result, maxSize);

    u8 carryover = 0;
    for (int i = 0; i < maxSize; i++) {
        result.bytes[i] = a.bytes[i] + b.bytes[i] + carryover;
        carryover = (result.bytes[i] < a.bytes[i]) ? 1 : 0;
    }
    if (result.bytes[maxSize-1] == 0) {
        resizeBigint(&result, maxSize-1);
    }

    return result;
}

Bigint mulByte(Bigint a, u8 b) {
    Bigint result;
    initBigint(&result);

    u16 maxSize = a.size + 1;
    resizeBigint(&result, maxSize);

    u16 carryover = 0;
    u16 partial;
    for (int i = 0; i < a.size; i++) {
        partial = (u16)a.bytes[i] * (u16)b + carryover;
        carryover = partial >> 8;
        result.bytes[i] = partial & 0xff;
    }
    if (result.bytes[maxSize-1] == 0) {
        resizeBigint(&result, maxSize-1);
    }

    return result;
}