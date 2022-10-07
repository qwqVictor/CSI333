#ifndef VICTORHUANG_LINKEDLIST
#define VICTORHUANG_LINKEDLIST

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define LINKED_LIST_MAX_LENGTH (256)

typedef struct LinkedList LinkedList;
struct LinkedList {
    char text[LINKED_LIST_MAX_LENGTH];
    int index;
    LinkedList *next;
};

typedef enum {
    OPERATION_OK = 0,
    UNCHANGED,
    INSERTION_DUPLICATE,
    INSERTED_AT_BORDER,
    OUT_OF_BOUND
} LinkedListErrorType;

LinkedList* llNewList();
LinkedListErrorType llInsertAfter(LinkedList *list, char *text, int len, int index);
LinkedListErrorType llInsertBefore(LinkedList *list, char *text, int len, int index);
LinkedListErrorType llDelete(LinkedList *list, int index);
LinkedListErrorType llReplace(LinkedList *list, char *text, int len, int index);
LinkedListErrorType llPrint(LinkedList *list, FILE *stream, const char *emptyMessage);

#endif