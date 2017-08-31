//
// Created by serbis on 14.08.17.
//

#ifndef AVMMOD_STACK_H
#define AVMMOD_STACK_H

#include <stdint.h>
#include "heap.h"
#include "thread.h"
#include "stdout.h"


uint16_t STACK_Get_Free_Ref();
bool STACK_PushThread(Thread *thread);
Thread* STACK_GetThread(uint16_t *tRef);
bool STACK_pushFrame(Frame *frame, uint16_t *tRef);
bool STACK_pushIntToOS(Frame *frame, int32_t *n);
int32_t STACK_popIntFromOS(Frame *frame);
void STACK_freeFrame(Frame *frame);

#endif //AVMMOD_STACK_H
