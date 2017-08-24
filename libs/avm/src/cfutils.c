#include "../includes/cfutils.h"


/**
 * Возаращет адрес первой инструкции метода по его сингатуре. Функция ищет
 * в пуле методов заданную в параметре сигатуру и найдя ее, возвращает адрес
 * куда указывает запись. Если метод не числится в пуле методов, возвращает
 * -1
 *
 * @param sig сигнаатура метода
 * @param fdp дескриптор cf
 * @return адрес первой инструкции метода или -1
 */
int32_t CFUTILS_Get_Method_Ad_By_Sig(char *sig, char *fdp) {
    int32_t cpSize;
    int32_t mpSize;
    FSS_ReadInt32(&cpSize, fdp, CF_A_CP_SIZE);
    FSS_ReadInt32(&mpSize, fdp, CF_A_MP_SIZE);

    uint32_t ca = (uint32_t) (CF_HEADER_SIZE + cpSize);
    while (ca < cpSize + mpSize) {
        int16_t sigSize;
        int32_t *mAddr = (int32_t *) malloc(4);
        FSS_ReadInt16(&sigSize, fdp, ca);
        FSS_ReadInt32(mAddr, fdp, ca + (uint32_t) sigSize + 2);
        char *sign = malloc(sizeof(char) * sigSize);
        FSS_ReadBytes(sign, fdp, ca + 2, (uint32_t) sigSize);

        if (strcmp(sig, sign) == 0) {
            int32_t ret = (uint32_t ) *mAddr;
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

/**
 * Возаращет адрес начала записи определения метода в MP. Функция ищет
 * в пуле методов заданную в параметре сигатуру и найдя ее, возвращает адрес
 * ее начала. Если метод не числится в пуле методов, возвращает -1.
 *
 * @param sig сигнаатура метода
 * @param fdp дескриптор cf
 * @return адрес начала определения метода в CP или -1
 */
int32_t CFUTILS_Get_Method_Cpe_By_Sig(char *sig, char *fdp) {
    int32_t cpSize;
    int32_t mpSize;
    FSS_ReadInt32(&cpSize, fdp, CF_A_CP_SIZE);
    FSS_ReadInt32(&mpSize, fdp, CF_A_MP_SIZE);

    uint32_t ca = (uint32_t) (CF_HEADER_SIZE + cpSize);
    while (ca < cpSize + mpSize) {
        int16_t sigSize;
        FSS_ReadInt16(&sigSize, fdp, ca);
        char *sign = malloc(sizeof(char) * sigSize);
        FSS_ReadBytes(sign, fdp, ca + 2, (uint32_t) sigSize);

        if (strcmp(sig, sign) == 0) {
            int32_t ret = (uint32_t ) ca;
            free(sign);

            return ret;
        }

        free(sign);
        ca = ca + 2 + sigSize + 4;
    }

    return (uint32_t) -1;
}

