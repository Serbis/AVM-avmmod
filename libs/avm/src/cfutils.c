#include "../includes/cfutils.h"


int32_t CFUTILS_Get_Method_By_Sig(char *sig, char *fdp) {
    int32_t cpSize;
    int32_t mpSize;
    FSS_ReadInt32(&cpSize, fdp, CF_A_CP_SIZE);
    FSS_ReadInt32(&mpSize, fdp, CF_A_MP_SIZE);

    uint32_t ca = (uint32_t) (CF_HEADER_SIZE + cpSize);
    while (ca < cpSize + mpSize) {
        int16_t sigSize;
        int32_t *mAddr = (int32_t *) malloc(4);
        FSS_ReadShort(&sigSize, fdp, ca);
        FSS_ReadInt32(mAddr, fdp, ca + (uint32_t) sigSize + 2);
        char *sign = malloc(sizeof(char) * sigSize);
        FSS_ReadBytes(sign, fdp, ca + 2, (uint32_t) sigSize);

        Разобраться почему адрес метода main имеет в signed int -122
        if (strcmp(sig, sign) == 0) {
            int32_t ret = *mAddr;
            free(mAddr);
            free(sign);

            return ret;
        }

        free(mAddr);
        free(sign);
        ca = ca + 2 + sigSize + 4;
    }

    return (uint32_t) -1;
}
