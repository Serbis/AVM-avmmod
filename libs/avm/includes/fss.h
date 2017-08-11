#include <stdint.h>
#include <stdio.h>
#include "../includes/defines.h"

#ifndef AVMMOD_FSS_H
#define AVMMOD_FSS_H

#endif //AVMMOD_FSS_H

typedef struct  FileDescriptor {
    char *path;
    FILE *file;
} FileDescriptor;

bool FSS_Open(char *path);
bool FSS_ReadBytes(char *bytes, char *fdp, uint32_t off, uint32_t len);
bool FSS_ReadInt(uint32_t *target, char *fdp, uint32_t off);