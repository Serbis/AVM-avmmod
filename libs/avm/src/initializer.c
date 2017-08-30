#include "../includes/initializer.h"

void INITIALIZER_Init(char *cf, char *config) {
    //Создать первичный поток
    Thread *deft = (Thread*) malloc(sizeof(Thread));
    deft->ref = STACK_Get_Free_Ref();
    if (deft->ref == -1) { //Если не удалось получить референс потока
        char bf[] = "--Unable to initialize vm. Can't init default thread.";
        STDOUT_println(bf, sizeof(bf));

        return;
    }
    bool rs = STACK_PushThread(deft);
    if (rs != TRUE) {
        char bf[] = "--Unable to initialize vm. Can't push default thread to stack.";
        STDOUT_println(bf, sizeof(bf));

        return;
    }

    //CLASSLOADER_Load - вернет сRef
    uint16_t cRef;
    CLASSLOADER_Load(cf, deft->ref, &cRef);

    INTERPRETATOR_Preprocess();
    //Вызвать препроцессор интерпретатора, ручной запуск процесса инерпретации для выполнения <clinit>()
    //Ручной запуск необходим, поскольку инетпретатор был до этого не запущен

    //Найти метод main и передать ему управление
    int32_t mad = CFUTILS_Get_Method_Cpe_By_Sig("main()V", cf);
    if (mad == -1)
        RLOGGER_log("main()V not found");
    INTERPRETATOR_Exec_Invokespetial((uint32_t) mad);

    //Вызвать препроцессор интерпретатора, ручной запуск процесса инерпретации
    //Тут же ручной запуск необходим потому что после выполнения <clinit>() поток вывалится из интерпретатора
    //а так как он не был до этого запущен, нужно будет запускать его по новой
    INTERPRETATOR_Set_PPStop(FALSE);
    INTERPRETATOR_Preprocess();
}
