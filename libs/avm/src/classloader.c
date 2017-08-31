#include "../includes/classloader.h"

bool CLASSLOADER_Load(char *classFilePath, uint16_t tid, uint16_t *cRefBuf) {
    //Получить ссылку на текущий фрей интерпретатора
    Frame *frame = INTERPRETATOR_Get_Current_Frame();

    //Создать файловый дескриптор для CF
    if (FSS_Open(classFilePath) == FALSE) {
        char bf[200];
        sprintf(bf, "--Can not load class %s. Can not read file", classFilePath);
        STDOUT_println(bf, sizeof(bf));

        return FALSE;
    }

    //Создать новый класс (проверить есть ли он в пуле) !!!ПРОВЕРИТЬ!!!!!!
    Class *class = (Class*) malloc(sizeof(Class));
    class->ref = HEAP_Get_Free_cRef();
    if (class->ref == NULL) {
        char bf[200];
        sprintf(bf, "--Can not load class %s. Can not get new cRef", classFilePath);
        STDOUT_println(bf, sizeof(bf));

        return FALSE;
    }
    class->fdp = classFilePath;
    if (HEAP_PushClass(class) == FALSE) {
        char bf[200];
        sprintf(bf, "--Can not load class %s. Can not allocate class in heap", classFilePath);
        STDOUT_println(bf, sizeof(bf));

        return FALSE;
    }

    //Создать объект (проверить есть ли он в пуле) !!!ПРОВЕРИТЬ!!!!!!
    Object *obj = (Object*) malloc(sizeof(Object));
    obj->ref = HEAP_Get_Free_aRef();
    obj->cRef = class->ref;
    if (obj->ref == NULL) {
        char bf[200];
        sprintf(bf, "--Can not load class %s. Can not get new aRef", classFilePath);
        STDOUT_println(bf, sizeof(bf));

        return FALSE;
    }
    if (HEAP_PushObject(obj) == FALSE) {
        char bf[200];
        sprintf(bf, "--Can not load class %s. Can not allocate object in heap", classFilePath);
        STDOUT_println(bf, sizeof(bf));

        return FALSE;
    }

    //Если у интерпретатора нет фрейма, то это первичная загрузка, поэтому создать данный фрейм (иницилизировать его arefом объекта и класса) и добавить его в поток
    if (frame == NULL) {
        frame = (Frame*) malloc(sizeof(Frame));
        frame->aRef = obj->ref;
        frame->cRef = class->ref;
        frame->cia = 0;
        if (STACK_pushFrame(frame, &tid) == FALSE) {
            char bf[200];
            sprintf(bf, "--Can not load class %s. Can not push frame in to thread", classFilePath);
            STDOUT_println(bf, sizeof(bf));

            return FALSE;
        }
    }

    //Разместить на OS фрейма в интепретаторе aref созданного объекта
    if (STACK_pushIntToOS(frame, (int32_t*) obj->ref) == FALSE) {
        char bf[200];
        sprintf(bf, "--Can not load class %s. Can not push aRef in to frame stack", classFilePath);
        STDOUT_println(bf, sizeof(bf));

        return FALSE;
    };

    //Обновить состояние фрейма в интерпретаторе
    INTERPRETATOR_Set_Current_Frame(frame);

    //Найти адрес нулевого метода
    int32_t cpSize;
    FSS_ReadInt32(&cpSize, classFilePath, CF_A_CP_SIZE);

    //Выполнить инструкцию invokesptial для <clinit>()V
    INTERPRETATOR_Exec_Invokespetial((uint32_t) (CF_HEADER_SIZE + cpSize));

    return TRUE;
}