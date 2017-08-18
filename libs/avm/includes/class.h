#include <stdint.h>

#ifndef AVMMOD_CLASS_H
#define AVMMOD_CLASS_H

typedef struct Class {
    uint16_t *ref;
    char *fdp;
} Class;

#endif //AVMMOD_CLASS_H
