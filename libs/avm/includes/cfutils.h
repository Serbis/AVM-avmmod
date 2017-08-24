#ifndef AVMMOD_CFUTILS_H
#define AVMMOD_CFUTILS_H

#include <stdint.h>
#include "defines.h"
#include "../includes/fss.h"

int32_t CFUTILS_Get_Method_Ad_By_Sig(char *sig, char *fdp);
int32_t CFUTILS_Get_Method_Cpe_By_Sig(char *sig, char *fdp);

#endif //AVMMOD_CFUTILS_H
