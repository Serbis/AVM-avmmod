#ifndef AVMMOD_CLASSLOADER_H
#define AVMMOD_CLASSLOADER_H

#include <stdint.h>
#include "thread.h"
#include "stack.h"
#include "object.h"
#include "heap.h"
#include "fss.h"
#include "interpretator.h"
#include "defines.h"

bool CLASSLOADER_Load(char *classFilePath, uint16_t tid, uint16_t *cRefBuf);

#endif //AVMMOD_CLASSLOADER_H
