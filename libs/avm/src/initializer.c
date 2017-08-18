#include "../includes/initializer.h"


void INITIALIZER_Init(char *cf, char *config) {
    //Создать первичный поток
    Thread *deft = (Thread*) malloc(sizeof(Thread));
    deft->ref = STACK_Get_Free_Ref();
    STACK_PushThread(deft);

    //CLASSLOADER_Load - вернет сRef
    uint16_t cRef;
    CLASSLOADER_Load(cf, deft->ref, &cRef);

    //Найти метод main и выполнить его

}
