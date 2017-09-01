#include <stddef.h>
#include "../includes/interpretator.h"

/** Ссылка на текущий фрейм */
Frame *currentFrame = NULL;
/** Флаг процессиногового останова */
bool pStop = FALSE;
/** Флаг препрцессингового останова */
bool ppStop = FALSE;


/**
 * Возаращает перечень типов аргументов метода в буфер. Каждый элемент в буфере
 * представляет собой значение типа.
 *
 * @param буефер для записи перечня типов аргументов
 * @param sig сигнатура метода
 */
uint8_t INTERPRETATOR_GetMethodArgs(char * sig, int8_t* bf) {
    return 0;
    //Пока он ничего не возвращает, просто выкидывает назад 0 - нет аргументов.
}

/**
 * Возвращает тип возвращаемого значения метода по его сигнатуре
 *
 * @param sig сигнатура метода
 */
uint8_t INTERPRETATOR_GetMethodRetType(char * sig) {
    return TYPE_VOID;
    //Пока он возвращает только VOID.
}

/**
 * Полностью останавливает интерпретатор
 */
void INTERPRETATOR_Stop() {
    ppStop = TRUE;
    pStop = TRUE;
}



/**
 * Дествие: Создает новый объект
 * Результат: 1. Размещение на OS ссылки на объект типа aref
 *            2. Размешение на osOut ссылки на объект типа aref
 * Механика: В нормальном режиме получает в качестве аргумена адрес
 *           значения в CP с определение создаваемого объекта а с вершины
 *           стека TID, в котором необходимо создать эземлпяр.
 *           Работа разделяется на четыре режма:
 *
 *           1. Если оба аргумента являются положительными значениями.
 *           Получив данные значения, задействует загрузчик в части функции
 *           Load которая в реузльтате свой работы вернет вернет aref,
 *           который помещается на вершину OS.
 *
 *           2. Если в качестве TID будет получено значение
 *           -2. То интрукция сначала создаст новый поток а затем
 *           произведет действия описаные в п.1 относительно созданнного
 *           потока.
 *
 *           3. Если в качестве TID будет получено значение
 *           -1. То интрукция создаст объект в текущем потоке
 *
 *           4. Если в качетсве указателя на CP указано отрицательно значение,
 *           задействует режим первичной загрузки класса. В данным режиме,
 *           создаст новый поток, и передст загрузчику в качестве пути
 *           загрузки FDP. Получив aref, заносит его в массив вывода osOut,
 *           для  возможности деальнешего считывания переферией вм.
 *
 * @param cpPointer указатель определения класса в CP
 */
void INTERPRETATOR_Exec_New(uint32_t *cpPointer) {


    /*
      1. Делаем эту инструкция (переделка Load загрузчика
      2. Провряем ее работу (корректируем иннициализатор)
      4. Релизовать метод bipush
      3. Делаем инутрукцию invokeseptial
      6. Делаем инструкцию invokevirtal
     */
}

/**
 * Вспомогательная функция для обеспечения работы инструкции invokevirtal.
 *
 * @param pSize количество аргуентов
 * @return список аргументов
 */
Node* INTERPRETATOR_ProcessHWM(int32_t pSize) {
    Node *params = NULL;
    if (LIST_Length(currentFrame->os) < pSize) {
        char bf[120];
        sprintf(bf, "--Runtime error. I->0x07, A->0x%08X, R->Insufficient operands on the OS.", *(currentFrame->cia));
        STDOUT_println(bf, sizeof(bf));
        INTERPRETATOR_Stop();
        return NULL;
    }
    for (int i = 0; i < pSize; i++) {
        int32_t *op = (int32_t*) malloc(4);
        *op = STACK_popIntFromOS(currentFrame);
        LIST_Shift(&params, (int) op);
    }

    return params;
}

/**
 * Дествие: Производит вызов аппаратого метода
 * Результат: Передает управление из виртуальной машины в код прошивки
 *            устройства на котором исполняется вм
 * Механика: В агрументе инструкции передается номер аппаратного метода (АМ)
 *           который должен быть вызван. В файле hardm.h имеются определения
 *           для всех возможных номеров АМ вида HARDM_X. Там же имеется
 *           дефайн вида HADM_PARMAS_MX указывающий количество параметров,
 *           которое должен принять АМ. Этот дефайн, должен переопределить
 *           разработчик АМ. Так же разработчик должен написать определние
 *           самого АМ в файле hardm.c. Реализация функции АМ один аргумент
 *           в котороый передается структура Node, внутренняя реализация
 *           свзяного списка. В данном вязном списке  находятся указатели
 *           на массивы байт, определяющие значение аргумента. Разработчик
 *           АМ должен привести данные массивы к конечным необходмым ему
 *           значениям. Значения передаваемые в АМ извлекаются с вершины
 *           стека, и могут быть нетипизированным четырехразрадным числом,
 *           адресом в пуле констант, референсом объекта или класса. Каким
 *           образом будут использоваться данные значения, оставляется на
 *           усмотрение разработчика АМ.
 *
 *
 * @param method
 */
void INTERPRETATOR_Exec_Invokehardware(uint8_t method) {
    Node *params = NULL;
    if (method == 0) {
        if (HARDM_PARMAS_M0 == 0) {
            HARDM_M0(NULL);
            return;
        }
        params = INTERPRETATOR_ProcessHWM(HARDM_PARMAS_M0);
        if (params == NULL) return;
        HARDM_M0(params);
    } else if (method == 1) {
        if (HARDM_PARMAS_M1 == 0) {
            HARDM_M1(NULL);
            return;
        }
        params = INTERPRETATOR_ProcessHWM(HARDM_PARMAS_M1);
        if (params == NULL) return;
        HARDM_M1(params);
    } else if (method == 2) {
        if (HARDM_PARMAS_M2 == 0) {
            HARDM_M2(NULL);
            return;
        }
        params = INTERPRETATOR_ProcessHWM(HARDM_PARMAS_M2);
        if (params == NULL) return;
        HARDM_M2(params);
    }


    LIST_Free(params);
    params = NULL;
}



/**
 * Действе: Вызывает специальный метод объекта. К специальным методам относятся
 *          - методы суперкласса, конструкторы (включая статический
 *          инициализатор) и приватные методы.
 * Результат: Создание нового фрейма, переиницилазиация интерпретатора и передача
 *            управления в целевой метод
 * Входные данные: 1. Стек - Ссылка на объект (aref) в котором будет вызван метод.
 *                 2. Первый аргумент - адрес определения метода в пуле методов.
 * Механика:
 *
 * @param adr
 */
void INTERPRETATOR_Exec_Invokespetial(uint32_t adr) {
    Class *cls = HEAP_GetClass(currentFrame->cRef);
    if (cls == NULL) {
        char bf[100];
        sprintf(bf, "--Runtime error. I->0xB7, A->0x%08X, arg1->0x%08X, R->Can not get class.", *(currentFrame->cia),  adr);
        STDOUT_println(bf, sizeof(bf));
        INTERPRETATOR_Stop();
        return;
    }
    char *fdp = cls->fdp;


    int16_t sigSize;
    int *mAddr = (int*) malloc(4);
    FSS_ReadInt16(&sigSize, fdp, adr);
    FSS_ReadInt32(mAddr, fdp, adr + (uint32_t) sigSize + 2);
    char *sig = malloc(sizeof(char) * sigSize);
    FSS_ReadBytes(sig, fdp, adr + 2, (uint32_t) sigSize);

    //Если адрес метода -1, значит в методе нет кода, выход из функции
    if (*mAddr == -1)
        return;

    //Тут находится механика взятия аргументов по сигнатуре методов. Это перспективная механика
    //поэтому код ниже закомментирован
    //int8_t * args = NULL;
    //int8_t argsCount = INTERPRETATIR_GetMethodArgs(sig, args);

    //Тут должна быть механника взятия аргументов с OS текущего фрейма для последующего размещения
    //их на OS порождаемого фрейма, но покольку это перспективная механика, тут сейчас ничего не
    //происходит

    free(sig);

    //Тут нужно взять с OS aref. Дальше проверить, если они отличиается от
    //aref текущего фрейма !!! aref хранится во фрейме  а не в интерпретаторе !!!
    //и если они различны, то : То это перспективная механика и она требует
    //дальнейшей реализации. Если же они одентичны, то:

    //Создать новый фрейм и инициализировать его окружением для выполнения целевого метода
    //текущего инстанса
    Frame *frame = (Frame*) malloc(sizeof(Frame));
    frame->cRef = currentFrame->cRef;
    frame->aRef = currentFrame->aRef;
    frame->cia = (uint32_t *) mAddr;
    frame->parent = currentFrame;
    frame->os = NULL;

    //Инициализировать интерпретатор новым фреймом
    currentFrame = frame;

    //Установить процессинговый флаг выхода из текушего блока интерпретации
    //(интерпретатор запуска препроцессор. Если функция инерпретациии сталкивается
    // со специальным флагом, она завершает свою работа и отает управление перпроцессору
    // который тут же стартует ее по новой. Это необходимо для дублирования виртуального
    // стека, аппаратным стеком вызовов функции интепретатора.)
    pStop = TRUE;

    //Завершить работу метода
}

/**
 * Действе: Производит void выход из метода
 * Результат: Возврат управление в родительский метод
 * Входные данные: Отсутсвуют
 * Механика: Устанавливает в качестве текущего фрейма (A) интерпретатора
 *           родительский фрейм (B), после чего освобождает память занимаему
 *           (A)
 */
void INTERPRETATOR_Exec_Return() {
    //Скопировать ссылку на родительский фрейм
    Frame *parentLink = currentFrame->parent;

    //Выполнить особождение текущего фрейма
    STACK_freeFrame(currentFrame);

    //Установить родительский фрейм в качестве текущего
    currentFrame = parentLink;
}

/**
 * Действе: Размещает на OS текущего фрейма значение типа int8_t
 *          приведя его к unsigned int
 * Результат: Размещение значение типа int на стеке
 * Входные данные: op - операнд типа int8_t
 * Механика: Пробразовывет входящий операнд к int32_t и размещает его на
 *           OS текущего фрейма
 *
 * @param op первый операнд
 */
void INTERPRETATOR_Exec_Bipush(int8_t op) {
    int32_t *s = (int32_t) malloc(4);
    *s = (int32_t) op;
    if (STACK_pushIntToOS(currentFrame, s) == FALSE) {
        char bf[130];
        sprintf(bf, "--Runtime error. I->0x10, A->0x%08X, R->Impossible to place the operation result on the OS.", *(currentFrame->cia));
        STDOUT_println(bf, sizeof(bf));
        INTERPRETATOR_Stop();
    }
}

/**
 * Действе: Складывает два значения на OS текущего фрейма как int и размещает
 *          результат данной операции там же.
 * Результат: Размещение результат целозначение сложения на OS
 * Входные данные: Отсутсвуют
 * Механика: Выбирает два последних значение с OS как int, складывает их и
 *           размещает полученный резльтат как int на вершину OS
 *
 */
void INTERPRETATOR_Exec_IAdd() {
    if (LIST_Length(currentFrame->os) < 2) {
        char bf[120];
        sprintf(bf, "--Runtime error. I->0x60, A->0x%08X, R->Insufficient operands on the OS.", *(currentFrame->cia));
        STDOUT_println(bf, sizeof(bf));
        INTERPRETATOR_Stop();
        return;
    }
    int32_t op1 = STACK_popIntFromOS(currentFrame);
    int32_t op2 = STACK_popIntFromOS(currentFrame);
    int32_t *r = (int32_t) malloc(4);
    *r = op1 + op2;
    if (STACK_pushIntToOS(currentFrame, r) == FALSE) {
        char bf[130];
        sprintf(bf, "--Runtime error. I->0x60, A->0x%08X, R->Impossible to place the operation result on the OS.", *(currentFrame->cia));
        STDOUT_println(bf, sizeof(bf));
        INTERPRETATOR_Stop();
    }
}

/**
 * Действе:
 * Результат:
 * Механика:
 *
 * @param op первый операнд
 */
void INTERPRETATOR_Exec_If_Cmpeq(int32_t op) {
    if (LIST_Length(currentFrame->os) < 2) {
        char bf[120];
        sprintf(bf, "--Runtime error. I->0xA1, A->0x%08X, R->Insufficient operands on the OS.", *(currentFrame->cia));
        STDOUT_println(bf, sizeof(bf));
        INTERPRETATOR_Stop();
        return;
    }

    int32_t op1 = STACK_popIntFromOS(currentFrame);
    int32_t op2 = STACK_popIntFromOS(currentFrame);
    if (op1 == op2) {
        *currentFrame->cia = (uint32_t) op;
    }

}


void INTERPRETATOR_Preprocess() {
    while (ppStop == FALSE) {
        pStop = FALSE;
        INTERPRETATOR_Process();
    }
}

void INTERPRETATOR_Process() {
    int8_t ins = 0;
    while (pStop == FALSE) {

        //Если указатель инструкции текущего фрейма указывает в никуда, завершить работу процессора и препроцессора.
        //Данная ситуация возможна только на этапе инициализации вм, когда метод clinit пуст, его фрейм не создается
        //и в качестве текущего фрейма остается стартовый фрейм с указателем инструкции (cia) равным NULL. Так как
        //после статртового clinit при инициализации должен быть программно вызван main, неободимо полностью прекратить
        //работу интерпретатора и передать управление обратно в инициализатор.
        if (currentFrame->cia == NULL) {
            ppStop = TRUE;
            return;
        }

        //Прочитать код инструкции
        ins = FSS_ReadInt8(HEAP_GetClass(currentFrame->cRef)->fdp, *(currentFrame->cia));

        //Селектор инструкций
        switch (ins) {
            case (int8_t) 0xB1: //return
                *(currentFrame->cia) = *(currentFrame->cia) + 1;
                INTERPRETATOR_Exec_Return();
                break;
            case (int8_t) 0x10: //bipush
                *(currentFrame->cia) = *(currentFrame->cia) + 2;
                INTERPRETATOR_Exec_Bipush(FSS_ReadInt8(HEAP_GetClass(currentFrame->cRef)->fdp, *(currentFrame->cia) - 1));
                break;
            case (int8_t) 0x60: //iadd
                *(currentFrame->cia) = *(currentFrame->cia) + 1;
                INTERPRETATOR_Exec_IAdd();
                break;
            case (int8_t) 0x07: //invokehardware
                *(currentFrame->cia) = *(currentFrame->cia) + 2;
                INTERPRETATOR_Exec_Invokehardware((uint8_t ) FSS_ReadInt8(HEAP_GetClass(currentFrame->cRef)->fdp, *(currentFrame->cia) - 1));
                break;
            case (int8_t) 0xA1: //if_icmpeq
                *(currentFrame->cia) = *(currentFrame->cia) + 5;
                int32_t *r = (int32_t) malloc(4);
                FSS_ReadInt32(r, HEAP_GetClass(currentFrame->cRef)->fdp, *(currentFrame->cia) - 4);
                INTERPRETATOR_Exec_If_Cmpeq(*r);
                free(r);
                break;
            default:
                //ОШИБКА - НИЗВЕСТНАЯ ИНСТРКЦИЯ

                break;
        }

    }
}

void INTERPRETATOR_Set_Current_Frame(Frame *frame) {
    currentFrame = frame;
}

Frame* INTERPRETATOR_Get_Current_Frame() {
    return currentFrame;
}

void INTERPRETATOR_Set_PPStop(bool set) {
    ppStop = set;
}