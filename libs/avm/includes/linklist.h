#ifndef AVMMOD_LINKLIST_H
#define AVMMOD_LINKLIST_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

void LIST_Push(Node **head, int value);
int* LIST_Pop (Node **head);
int * LIST_Get(Node* head, int n);
Node* LIST_GetLast(Node *head);
void LIST_Shift(Node **head, int value);
void LIST_Unshift(Node **head);
void LIST_Insert(Node *head, unsigned n, int val);
int LIST_Remove(Node **head, int n);
int LIST_Length(const Node *head);
void hello_world();

#endif //AVMMOD_LINKLIST_H
