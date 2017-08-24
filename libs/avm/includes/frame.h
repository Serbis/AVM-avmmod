#ifndef AVMMOD_FRAME_H
#define AVMMOD_FRAME_H

#include "linklist.h"

/**
 * Определение фрейма
 */
typedef struct Frame {
    /** Референс объекта которому принадлежит фрейм */
    uint16_t *aRef;
    /** Референс класса которому принадлежит фрейм */
    uint16_t *cRef;
    /** Стек операндов */
    Node *os;
    /** Адррес текущей инструкции */
    uint32_t *cia;
    /** Укахатель на родительский фрейм */
    struct Frame *parent;
} Frame;

#endif //AVMMOD_FRAME_H
