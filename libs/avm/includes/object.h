//
// Created by serbis on 14.08.17.
//

#ifndef AVMMOD_OBJECT_H
#define AVMMOD_OBJECT_H

typedef struct object {
    uint16_t *ref;
    uint16_t *cRef;
} Object;

#endif //AVMMOD_OBJECT_H