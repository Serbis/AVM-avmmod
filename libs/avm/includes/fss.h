#ifndef AVMMOD_FSS_H
#define AVMMOD_FSS_H

#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "defines.h"
#include "linklist.h"

typedef struct  FileDescriptor {
    char *path;
    FILE *file;
} FileDescriptor;

bool FSS_Open(char *path);
bool FSS_ReadBytes(char *bytes, char *fdp, long off, uint32_t len);
bool FSS_ReadInt(int *target, char *fdp, uint32_t off);
bool FSS_ReadShort(int16_t *target, char *fdp, uint32_t off);

#endif //AVMMOD_FSS_H
