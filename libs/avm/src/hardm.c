#include <zconf.h>
#include "../includes/hardm.h"

/**
 * Обеспечивает возврат значения в вм из аппаратного метода. Аргументом
 * функции является int32, который фактически долженн являться значением
 * из четрех байт с некоторым числом, корректным для вм.
 *
 * @param value число
 */
void HARDM_ret(uint32_t value) {
    int32_t *val = (uint32_t) malloc(4);
    *val = value;
    STACK_pushIntToOS(INTERPRETATOR_Get_Current_Frame(), val);
    INTERPRETATOR_Get_Current_Frame();
}



void HARDM_M0(Node *params) {
    printf("M->HARDM_M0, arg0->%d, arg1->%d\n", *LIST_Get(params, 0), *LIST_Get(params, 1));
    HARDM_ret((uint32_t) (*LIST_Get(params, 0) + *LIST_Get(params, 1)));

}

void HARDM_M1(Node *params) {
    printf("Result: %d\n", *LIST_Get(params, 0));
}

void HARDM_M2(Node *params) {
    sleep(1);
}
