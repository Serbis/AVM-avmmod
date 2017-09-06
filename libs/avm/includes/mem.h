#ifndef AVMMOD_MEM_H
#define AVMMOD_MEM_H

#include <stddef.h>
#include "defines.h"
#include <stdint.h>
#include <stdio.h>
#include "../includes/linklist.h"


void *xmalloc (uint32_t __size);
void xfree (void *__ptr);
void xmem_init();
void xdump();
void xmap();
void xbmap();
int32_t xfreeMem();
int32_t xtableSize();
int32_t xmetaSize();

#endif //AVMMOD_MEM_H
