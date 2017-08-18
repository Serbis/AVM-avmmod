#ifndef AVMMOD_HEAP_H
#define AVMMOD_HEAP_H

#include <stddef.h>
#include <stdio.h>
#include "linklist.h"
#include "defines.h"
#include "rlogger.h"
#include "object.h"
#include "class.h"

uint16_t* HEAP_Get_Free_aRef();
uint16_t* HEAP_Get_Free_cRef();
bool HEAP_PushObject(Object *object);
bool HEAP_PushClass(Class *class);
Class* HEAP_GetClass(uint16_t *cRef);

#endif //AVMMOD_HEAP_H