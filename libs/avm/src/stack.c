#include "../includes/stack.h"

Node *threadsPool = NULL;

/**
 * Размещает в пуле новый поток. При размещении у последнего должен быть
 * задан tid.
 *
 * @param thread указатель на поток для размещения в пуле
 * @return FALSE если произошел критический сбой при добавлении потока
 */
bool STACK_PushThread(Thread *thread) {
    bool tExist = FALSE;
    for (int i = 0; i < LIST_Length(threadsPool); i++) { //Проверяем имеется ли в пуле поток с указанным в новом потоке tid
        if (((Thread*) LIST_Get(threadsPool, i))->ref == thread->ref) {
            tExist = TRUE;
        }
    }

    if (tExist == TRUE) {
        char bf[] = {};
        sprintf(bf, "Thread with ref %d already exist", thread->ref);
        RLOGGER_log(bf);
        return FALSE;
    }

    LIST_Push(&threadsPool, (int) thread);
}

/**
 * Возвращает указатель на поток по заданному идентификатору
 *
 * @param tRef указатель референс потока
 * @return указатель на поток
 */
Thread* STACK_GetThread(uint16_t *tRef) {
    for (int i = 0; i < LIST_Length(threadsPool); i++) { //Проверяем имеется ли в пуле поток с указанным в новом потоке tid
        Thread *t = ((Thread*) LIST_Get(threadsPool, i));
        if (t->ref == *tRef) {
            return t;
        }
    }

    return NULL;
}

/**
 * Возращает первый свободный идентификатор потока
 *
 * @return идентификатор потока
 */
uint16_t STACK_Get_Free_Ref() {
    bool tidExist = FALSE;
    for (uint16_t i = 0; i < 127; i++) {
        tidExist = FALSE;
        for (int j = 0; j < LIST_Length(threadsPool); j++) { //Проверяем имеется ли в пуле поток с указанным в новом потоке tid
            if (((Thread*) LIST_Get(threadsPool, j))->ref == i) {
                tidExist = TRUE;
            }
        }

        if (tidExist == FALSE)
            return i;
    }

    return (uint16_t) -1;
}

/**
 * Размещает фрейм на вершину стека потока с заданным референсом
 *
 * @param frame указатель на размещаемый фрейм
 * @param tRef указатель на референс потока
 * @return результат выполнения
 */
bool STACK_pushFrame(Frame *frame, uint16_t *tRef) {
    for (int i = 0; i < LIST_Length(threadsPool); i++) { //Проверяем имеется ли в пуле поток с указанным в новом потоке tid
        Thread *t = ((Thread*) LIST_Get(threadsPool, i));
        if (t->ref == *tRef) {
            LIST_Push(&(t->framesStack), (int) frame);
            return TRUE;
        }
    }

    return FALSE;
}

/**
 * Размещаает значение типа int на стеке опреандов фрейма из аргумента
 *
 * @param frame целевой фрейм
 * @param n число для размещения
 * @return  результат выполнения
 */
bool STACK_pushIntToOS(Frame *frame, uint32_t *n) {
    uint8_t *val = (uint8_t*) malloc(sizeof(uint8_t) * 4);
    // uint8_t val[4] = {0};

    for (int i = 0; i < 4; i++) {
        val[i] = (uint8_t) (*n >> (i * 8));
    }

    LIST_Shift(&(frame->os), (int) val);
//    int b = (int) ((val[0]) | (val[1] << 8) | (val[2] << 16) | (val[3] << 24));

    return TRUE;
}

uint32_t STACK_popIntFromOS(Frame *frame) {
    uint8_t *val = (uint8_t*) LIST_Pop(&(frame->os));

    return (uint32_t) ((val[0]) | (val[1] << 8) | (val[2] << 16) | (val[3] << 24));
}