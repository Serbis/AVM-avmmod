#include "../includes/hardm.h"

void HARDM_Select(uint8_t mn, Node* params) {
    switch(mn) {
        case 0:
            HARDM_M0(params);
            break;
        default:
            break;
    }
}
void HARDM_M0(Node *params) {
    char bf[200];
    printf("M->HARDM_M0, arg0->%d, arg1->%d", *((int32_t*) LIST_Get(params, 0)), *((int32_t*) LIST_Get(params, 1)));
}
