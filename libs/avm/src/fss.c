#include "../includes/fss.h"


Node *fdPool = NULL;

bool FSS_Open(char *path) {
    FILE *fp = (FILE*) malloc(sizeof(FILE));
    fp = fopen(path, "rw");
    if (fp != NULL) {
        FileDescriptor *fd = malloc(sizeof(FileDescriptor));
        fd->file = fp;
        fd->path = path;

        LIST_Shift(&fdPool, (int) fd);

        Node * x = fdPool;
        FileDescriptor *fdx = (FileDescriptor *) LIST_Get(fdPool, 0);
        char *ps = ((FileDescriptor *) LIST_Get(fdPool, 0))->path;

        return TRUE;
    }

    return FALSE;
}

bool FSS_ReadBytes(char *bytes, char *fdp, long off, uint32_t len) {
    FILE *fp = NULL;
    for (int i = 0; i < LIST_Length(fdPool); i++) {
        if (strcmp(((FileDescriptor*) LIST_Get(fdPool, i))->path, fdp) == 0 ) {
            fp = ((FileDescriptor*) LIST_Get(fdPool, i))->file;
        }
    }

    if (fp == NULL) {
        printf("Не найден файловый дескритор");
        return FALSE;
    }

    fseek(fp, off, SEEK_SET);
    fread(bytes, len, 1, fp);

    return TRUE;
}

bool FSS_ReadInt32(int *target, char *fdp, uint32_t off) {
    char b[4] = {0};
    FSS_ReadBytes(b, fdp, off, 4);

    *target = (int) ((b[0] << 24) | (b[1] << 16) | (b[2] << 8) | (b[3]));

    return TRUE;
}

bool FSS_ReadUInt32(uint32_t *target, char *fdp, uint32_t off) {
    char b[4] = {0};
    FSS_ReadBytes(b, fdp, off, 4);

    *target = (uint32_t) ((b[0] << 24) | (b[1] << 16) | (b[2] << 8) | (b[3]));

    return TRUE;
}

bool FSS_ReadShort(int16_t *target, char *fdp, uint32_t off) {
    char b[2] = {0};
    FSS_ReadBytes(b, fdp, off, 2);

    *target = (int16_t) ((b[0] << 8) | (b[1]));

    return TRUE;
}