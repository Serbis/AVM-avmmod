#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

/**
 * Реализация односвязного списка на указателях
 */


/**
 * Добавялет элемент в конец списка
 *
 * @param head указатель на указатель на вершину списоку
 * @param value значение для вставки
 */
void LIST_Push(Node **head, int value) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    tmp->value = value;
    tmp->next = (*head);
    (*head) = tmp;
}

/**
 * Дказатель на указатель на вершину списоку
 *
 * @param head извлекает последний элемент из списка
 * @return значение элемента
 */
int LIST_Pop (Node **head) {
    Node* prev = NULL;
    int val;
    if (head == NULL) {
        exit(-1);
    }
    prev = (*head);
    val = prev->value;
    (*head) = (*head)->next;
    free(prev);
    return val;
}

/**
 * Возврвщает указатель на элемент в списке с заданной позицией
 *
 * @param head указатель на вершину списка
 * @param n номер элемента
 * @return указатель на искомый элемент
 */
Node* LIST_Get(Node* head, int n) {
    int counter = 0;
    while (counter < n && head) {
        head = head->next;
        counter++;
    }
    return head;
}


/**
 * Возращает указатель на последний элемент списка
 *
 * @param head указатель на вершину списка
 * @return указатель на искомый элемент
 */
Node* LIST_GetLast(Node *head) {
    if (head == NULL) {
        return NULL;
    }
    while (head->next) {
        head = head->next;
    }
    return head;
}

/**
 * Добавляет элемент в начало списка
 *
 * @param head указатель на вершину списка
 * @param value значение для вставки
 */
void LIST_Shift(Node *head, int value) {
    Node *last = LIST_GetLast(head);
    Node *tmp = (Node*) malloc(sizeof(Node));
    tmp->value = value;
    tmp->next = NULL;
    last->next = tmp;
}

/**
 * Удаляет последний элемент
 *
 * @param head указатель на указатель на вершину списока
 */
void LIST_Unshift(Node **head) {
    Node *pFwd = NULL;  //текущий узел
    Node *pBwd = NULL;  //предыдущий узел
    //Получили NULL
    if (!head) {
        exit(-1);
    }
    //Список пуст
    if (!(*head)) {
        exit(-1);
    }

    pFwd = *head;
    while (pFwd->next) {
        pBwd = pFwd;
        pFwd = pFwd->next;
    }

    if (pBwd == NULL) {
        free(*head);
        *head = NULL;
    } else {
        free(pFwd->next);
        pBwd->next = NULL;
    }
}

/**
 * Добавляет новый элемент на заданную позицию
 *
 * @param head указатель на вершину списка
 * @param n позиция добавления
 * @param val значение для добавления
 */
void LIST_Insert(Node *head, unsigned n, int val) {
    unsigned i = 0;
    Node *tmp = NULL;
    //Находим нужный элемент. Если вышли за пределы списка, то выходим из цикла,
    //ошибка выбрасываться не будет, произойдёт вставка в конец
    while (i < n && head->next) {
        head = head->next;
        i++;
    }
    tmp = (Node*) malloc(sizeof(Node));
    tmp->value = val;
    //Если это не последний элемент, то next перекидываем на следующий узел
    if (head->next) {
        tmp->next = head->next;
        //иначе на NULL
    } else {
        tmp->next = NULL;
    }
    head->next = tmp;
}

/**
 * Удаляет элемент из списка
 *
 * @param head указатель на указатель на вершину списка
 * @param n удаляемая позиция
 * @return значение удаленного элемента
 */
int LIST_Remove(Node **head, int n) {
    if (n == 0) {
        return LIST_Pop(head);
    } else {
        Node *prev = LIST_Get(*head, n-1);
        Node *elm  = prev->next;
        int val = elm->value;

        prev->next = elm->next;
        free(elm);
        return val;
    }
}

/**
 * Возвращает длинну списка
 *
 * @param head указатель на вершину списка
 * @return длинна списка
 */
int LIST_Length(const Node *head) {
    int len = 0;
    while (head) {
        len++;
        head = head-> next;
    }

    return len;
}