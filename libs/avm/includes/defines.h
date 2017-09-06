//
// Created by serbis on 10.08.17.
//

#ifndef AVMMOD_DEFINES_H
#define AVMMOD_DEFINES_H

/** Размер кучи виртуальной машины */
#define HEAP_SIZE 50

#define TRUE 1
#define FALSE 0

#define TYPE_VOID 0

/** Размер заголовка cf в байтах */
#define CF_HEADER_SIZE 8
/** Смещеие адреса метки CP_SIZE */
#define CF_A_CP_SIZE 0
/** Смещеие адреса метки MP_SIZE */
#define CF_A_MP_SIZE 4

typedef unsigned short bool;

#endif //AVMMOD_DEFINES_H

