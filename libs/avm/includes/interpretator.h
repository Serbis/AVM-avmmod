#ifndef AVMMOD_INTERPRETATOR_H
#define AVMMOD_INTERPRETATOR_H

#include <stdint.h>
#include "frame.h"
#include "fss.h"
#include "../includes/heap.h"

void INTERPRETATOR_Preprocess();
void INTERPRETATOR_Process();

void INTERPRETATOR_Exec_New(uint32_t *cpPointer);
void INTERPRETATOR_Exec_Invokespetial(uint32_t adr);

void INTERPRETATOR_Set_Current_Tid(uint8_t tif);
uint8_t INTERPRETATOR_Get_Current_Tid();
void INTERPRETATOR_Set_Current_ARef(uint16_t aRef);
uint16_t INTERPRETATOR_Get_Current_ARef();
void INTERPRETATOR_Set_Current_Frame(Frame *frame);
Frame* INTERPRETATOR_Get_Current_Frame();
void INTERPRETATOR_Set_Current_CRef(uint16_t cRef);
uint16_t INTERPRETATOR_Get_Current_CRef();


#endif //AVMMOD_INTERPRETATOR_H
