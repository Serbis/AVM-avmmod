#ifndef AVMMOD_FRAME_H
#define AVMMOD_FRAME_H

#include "linklist.h"

typedef struct Frame {
    uint16_t *aRef;
    uint16_t *cRef;
    Node *os;
} Frame;

#endif //AVMMOD_FRAME_H
