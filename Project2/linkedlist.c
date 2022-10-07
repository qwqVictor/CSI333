#include "linkedlist.h"

typedef struct {
    char data[256];
    int index;
    LinkedList* next;
} LinkedList;