#include <stddef.h>
#include <malloc.h>
#include "libs/avm/includes/linklist.h"
#include "libs/avm/includes/avm.h"
#include "libs/avm/includes/fss.h"

typedef struct Pair {
    int a;
    int b;
} Pair;

void Lst(char **list) {
    char *e1 = *(list + 1);
}

int main(int argc, char** argv)
{
    /*
     * 1. Попробовать сделать свзяный список на указателях
     * 2. Попробовать сделать кросс-хеадерный файл
     */

    FSS_Open("/home/serbis/tmp/fft.avmb");


    Pair *p1 = (Pair*) malloc(sizeof(Pair));
    Pair *p2 = (Pair*) malloc(sizeof(Pair));
    Pair *p3 = (Pair*) malloc(sizeof(Pair));

    p1->a = 11;
    p1->b = 12;
    p2->a = 21;
    p2->b = 22;
    p3->a = 31;
    p3->b = 32;

    int p1p = (int) p1; //Пулить адрес указателя на указетль на структуру
    Pair *ap = (Pair *) (int*) p1p; //Создать указатель на струтуру по указателю на который указвает указатель
    int a  = ap->a;


    Node *head = NULL;
    //LIST_Push(&head, (int) p1); //(int) p1
    //LIST_Shift(head, (int) p2); //(int) p2
    //LIST_Shift(head, (int) p3); //(int) p3

    //int c = LIST_Get(head, 0)->value;

    AVM_Run("aaa", "bbb");

    Pair *pa = (Pair *) (int*) LIST_Get(head, 0);
    //int r1 = ((Pair *) (int*) LIST_Get(head, 0)->value)->a;
    //int r2 = ((Pair *) (int*) LIST_Get(head, 1)->value)->a;
    //int r3 = ((Pair *) (int*) LIST_Get(head, 2)->value)->a;

   // нужно упростить данный конструктив


    char *strArr[2];
    strArr[0] = "AAA";
    strArr[1] = "BBB";

    Lst(strArr);


    return 0;
}

