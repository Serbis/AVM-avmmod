#include "../includes/classloader.h"

bool CLASSLOADER_Load(char *classFilePath, uint16_t tid, uint16_t *cRefBuf) {
    //Получить ссылку на текущий фрей интерпретатора
    Frame *frame = INTERPRETATOR_Get_Current_Frame();

    //Создать файловый дескриптор для CF
    FSS_Open(classFilePath);

    //Создать новый класс (проверить есть ли он в пуле) !!!ПРОВЕРИТЬ!!!!!!
    Class *class = (Class*) malloc(sizeof(Class));
    class->ref = HEAP_Get_Free_cRef();
    class->fdp = classFilePath;
    HEAP_PushClass(class);

    //Создать объект (проверить есть ли он в пуле) !!!ПРОВЕРИТЬ!!!!!!
    Object *obj = (Object*) malloc(sizeof(Object));
    obj->ref = HEAP_Get_Free_aRef();
    obj->cRef = class->ref;
    HEAP_PushObject(obj);

    //Если у интерпретатора нет фрейма, то это первичная загрузка, поэтому создать данный фрейм (иницилизировать его arefом объекта и класса) и добавить его в поток
    if (frame == NULL) {
        frame = (Frame*) malloc(sizeof(Frame));
        frame->aRef = obj->ref;
        frame->cRef = class->ref;
        STACK_pushFrame(frame, &tid);
    }

    //Разместить на OS фрейма в интепретаторе aref созданного объекта
    STACK_pushIntToOS(frame, (int32_t*) obj->ref);

    //Обновить состояние фрейма в интерпретаторе
    INTERPRETATOR_Set_Current_Frame(frame);

    //Найти адрес нулевого метода
    int32_t cpSize;
    FSS_ReadInt32(&cpSize, classFilePath, CF_A_CP_SIZE);

    //Выполнить инструкцию invokesptial для <clinit>()V
    INTERPRETATOR_Exec_Invokespetial((uint32_t) (CF_HEADER_SIZE + cpSize));

    return TRUE;
}