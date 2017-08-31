#include "../includes/heap.h"

Node *objectsPool = NULL;
Node *classPool = NULL;

/**
 * Размещает в пуле новый объект. При размещении у последнего должен быть
 * задан ref.
 *
 * @param object указатель на объект для размещения в пуле
 * @return FALSE если произошел критический сбой при добавлении объекта
 */
bool HEAP_PushObject(Object *object) {
    bool tExist = FALSE;
    for (int i = 0; i < LIST_Length(objectsPool); i++) {
        if (((Object*) LIST_Get(objectsPool, i))->ref == object->ref) {
            tExist = TRUE;
        }
    }

    if (tExist == TRUE) {
        char bf[50];
        sprintf(bf, "--Object with aRef %d already exist", *(object->ref));
        STDOUT_println(bf, sizeof(bf));

        return FALSE;
    }

    LIST_Push(&objectsPool, (int) object);
}


/**
 * Размещает в пуле новый класс. При размещении у последнего должен быть
 * задан ref.
 *
 * @param class указатель на класс для размещения в пуле
 * @return FALSE если произошел критический сбой при добавлении класса
 */
bool HEAP_PushClass(Class *class) {
    bool tExist = FALSE;
    for (int i = 0; i < LIST_Length(objectsPool); i++) {
        if (((Class*) LIST_Get(classPool, i))->ref == class->ref) {
            tExist = TRUE;
        }
    }

    if (tExist == TRUE) {
        char bf[50];
        sprintf(bf, "--Class with cRef %d already exist", *(class->ref));
        STDOUT_println(bf, sizeof(bf));

        return FALSE;
    }

    LIST_Push(&classPool, (int) class);
}



/**
 * Возращает первый свободный референс объект. Рефенс аллогцируется в хип
 * чере malloc. Данная точка является точкой порождения любого рефенса
 * данного типа.
 *
 * @return референс объекта
 */
uint16_t* HEAP_Get_Free_aRef() {
    bool refExist = FALSE;
    for (uint16_t i = 0; i < 65535; i++) {
        refExist = FALSE;
        for (int j = 0; j < LIST_Length(objectsPool); j++) {
            if ((*((Object*) LIST_Get(objectsPool, j))->ref) == i) {
                refExist = TRUE;
            }
        }

        if (refExist == FALSE) {
            uint16_t *nm = malloc(sizeof(uint16_t));
            *nm = i;
            return nm;
        }
    }

    char bf[] = "--No available aRefs";
    STDOUT_println(bf, sizeof(bf));

    return NULL;
}

/**
 * Возвращает первый свободный референс класса. Рефенс аллогцируется в хип
 * чере malloc. Данная точка является точкой порождения любого рефенса
 * данного типа.
 *
 * @return референс класса
 */
uint16_t* HEAP_Get_Free_cRef() {
    bool refExist = FALSE;
    for (uint16_t i = 0; i < 65535; i++) {
        refExist = FALSE;
        for (int j = 0; j < LIST_Length(classPool); j++) {
            if ((*((Class*) LIST_Get(classPool, j))->ref) == i) {
                refExist = TRUE;
            }
        }

        if (refExist == FALSE) {
            uint16_t *nm = malloc(sizeof(uint16_t));
            *nm = i;
            return nm;
        }
    }

    char bf[] = "--No available cRefs";
    STDOUT_println(bf, sizeof(bf));

    return NULL;
}

/**
 * Возаращает указатель на класс по его референсу
 *
 * @param cRef референс
 * @return указатель на класс
 */
Class* HEAP_GetClass(uint16_t *cRef) {
    for (int i = 0; i < LIST_Length(classPool); i++) { //Проверяем имеется ли в пуле класс с указанным в новом потоке tid
        Class *t = ((Class*) LIST_Get(classPool, i));
        if (*(t->ref) == *cRef) {
            return t;
        }
    }

    char bf[50];
    sprintf(bf, "--Class with cRef %d does not exist", *(cRef));
    STDOUT_println(bf, sizeof(bf));

    return NULL;
}
