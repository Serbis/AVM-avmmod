#ifndef AVMMOD_HARDM_H
#define AVMMOD_HARDM_H

#include <stdint.h>
#include "linklist.h"
#include "interpretator.h"


#define HARDM_PARMAS_M0 2
#define HARDM_PARMAS_M1 1
#define HARDM_PARMAS_M2 0

void HARDM_M0(Node *params);
void HARDM_M1(Node *params);
void HARDM_M2(Node *params);

#endif //AVMMOD_HARDM_H
