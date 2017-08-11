#include <malloc.h>
#include <stdio.h>
#include "../includes/fss.h"
#include "../includes/linklist.h"

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

bool FSS_ReadBytes(char *bytes, char *fdp, uint32_t off, uint32_t len) {

}

bool FSS_ReadInt(uint32_t *target, char *fdp, uint32_t off) {

}