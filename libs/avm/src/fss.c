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

    char bf[150];
    sprintf(bf, "--Can not open file %s", path);
    STDOUT_println(bf, sizeof(bf));

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



bool FSS_ReadInt32(int32_t *target, char *fdp, uint32_t off) {
    char b[4] = {0};
    FSS_ReadBytes(b, fdp, off, 4);

    int32_t t = 0;
    //t = (uint32_t) ((b[0] << 24) | (b[2] << 16) | (b[1] << 8) | (b[0]));
    *target = (int32_t) (((uint8_t) b[3] << 24) | ((uint8_t) b[2] << 16) | ((uint8_t) b[1] << 8) | (uint8_t) b[0]);

    //*target = (int32_t) ((b[0]) | ((int32_t) b[1] << 8) | ((int32_t) b[2] << 16) | ((int32_t) b[3] << 24));


    return TRUE;
}


bool FSS_ReadInt16(int16_t *target, char *fdp, uint32_t off) {
    char b[2] = {0};
    FSS_ReadBytes(b, fdp, off, 2);

    *target = (int16_t) (((uint8_t) b[1] << 8) | ((uint8_t) b[0]));

    return TRUE;
}

int8_t FSS_ReadInt8(char *fdp, uint32_t off) {
    char b[1] = {0};
    FSS_ReadBytes(b, fdp, off, 1);

    return (int8_t) b[0];

}