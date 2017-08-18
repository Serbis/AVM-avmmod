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

   // bytes[i] = (byte)(x >> (i * 8));

    *(obj->ref) = 1000;
    uint8_t *val = (uint8_t*) malloc(sizeof(uint8_t) * 4);
   // uint8_t val[4] = {0};

    for (int i = 0; i < 4; i++) {
        val[i] = (uint8_t) (*(obj->ref) >> (i * 8));
        printf("a[%d] = %d", i, val[i]);
    }
    int b = (int) ((val[0]) | (val[1] << 8) | (val[2] << 16) | (val[3] << 24));


    STACK_pushIntToOS(frame, (uint32_t *) obj->ref);


    //obj->ref
   // LIST_Push((Node **) frame->os, (int) val);
    //Разместить на OS фрейма в интепретаторе aref созданного объекта


    //Найти адрес нулевого метода
    int32_t cpSize;
    FSS_ReadInt(&cpSize, classFilePath, CF_A_CP_SIZE);

    //Выполнить инструкцию invokesptial для <clinit>()V
    INTERPRETATOR_Exec_Invokespetial((uint32_t) (CF_HEADER_SIZE + cpSize));

    //Вызвать препроцессор интерпретатора, ручной запуск процесса инерпретации


}