#ifndef AVMMOD_THREAD_H
#define AVMMOD_THREAD_H

#include <stdint.h>
#include "linklist.h"
#include "defines.h"
#include "frame.h"

typedef struct thread {
    int16_t ref;
    Node *framesStack;
} Thread;

#endif //AVMMOD_THREAD_H
