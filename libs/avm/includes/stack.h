//
// Created by serbis on 14.08.17.
//

#ifndef AVMMOD_STACK_H
#define AVMMOD_STACK_H

#include <stdint.h>
#include "heap.h"
#include "thread.h"

uint16_t STACK_Get_Free_Ref();
bool STACK_PushThread(Thread *thread);
Thread* STACK_GetThread(uint16_t *tRef);
bool STACK_pushFrame(Frame *frame, uint16_t *tRef);
bool STACK_pushIntToOS(Frame *frame, uint32_t *n);

#endif //AVMMOD_STACK_H