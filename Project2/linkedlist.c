#include "linkedlist.h"

LinkedList* llFindIndex(LinkedList* list, int index) {
    LinkedList* p = list;
    for (; p != NULL; p = p->next) {
        if (p->next != NULL && (p->next)->index == index)
            return p;
    }
    return p;
}

LinkedList* llNewList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->index = 0;
    list->next = NULL;
    list->text[LINKED_LIST_MAX_LENGTH - 1] = 0;
    return list;
}

LinkedListErrorType llInsertAfter(LinkedList* list, char* text, int len, int index) {
    LinkedList *prev = llFindIndex(list, index), *target = NULL, *node;
    LinkedListErrorType ret = OPERATION_OK;
    if (prev->next != NULL)
        target = prev->next;
    else {
        ret = INSERTED_AT_BORDER;
        target = prev;
    }
    if (strlen(target->text) == len && (!strncmp(text, target->text, len))) {
        return INSERTION_DUPLICATE;
    }
    node = llNewList();
    node->index = target->index + 1;
    strncpy(node->text, text, len);
    if (target->next != NULL) {
        node->next = target->next;
        int newIndex = node->index + 1;
        for (LinkedList* i = node->next; i != NULL; i = i->next)
            i->index = newIndex++;
    } else {
        node->next = NULL;
    }
    return ret;
}

LinkedListErrorType llInsertBefore(LinkedList* list, char* text, int len, int index) {
    LinkedList *prev = llFindIndex(list, index), *target = NULL, *node;
    LinkedListErrorType ret = OPERATION_OK;
    if (prev->next == NULL) {
        ret = INSERTED_AT_BORDER;
        target = list;
    }
    else {
        target = prev;
    }
    if (strlen(target->text) == len && (!strncmp(text, target->text, len))) {
        return INSERTION_DUPLICATE;
    }
    node = llNewList();
    node->index = target->index + 1;
    strncpy(node->text, text, len);
    if (target->next != NULL) {
        node->next = target->next;
        int newIndex = node->index + 1;
        for (LinkedList* i = node->next; i != NULL; i = i->next)
            i->index = newIndex++;
    } else {
        node->next = NULL;
    }
    return ret;
}

LinkedListErrorType llDelete(LinkedList* list, int index) {
    LinkedList* prev = llFindIndex(list, index);
    if (prev->next == NULL) {
        return UNCHANGED;
    }
    else {
        LinkedList* toBeDeleted = prev->next;
        prev->next = toBeDeleted->next;
        free((void*)toBeDeleted);
        int newIndex = prev->index + 1;
        for (LinkedList* i = prev->next; i != NULL; i = i->next)
            i->index = newIndex++;
    }
    return OPERATION_OK;
}

LinkedListErrorType llReplace(LinkedList* list, char* text, int len, int index) {
    LinkedList* prev = llFindIndex(list, index);
    if (prev->next == NULL)
        return UNCHANGED;
    LinkedList* target = prev->next;
    if (strlen(target->text) == len && (!strncmp(text, target->text, len)))
        return UNCHANGED;
    LinkedList* node = llNewList();
    node->next = target->next;
    node->index = target->index;
    strncpy(node->text, text, len);
    free((void*)target);
    return OPERATION_OK;
}

LinkedListErrorType llPrint(LinkedList* list, FILE* stream, const char* emptyMessage) {
    if (list->next != NULL) {
        for (LinkedList* i = list->next; i != NULL; i = i->next) {
            if (i != list->next)
                fprintf(stream, ", ");
            fprintf(stream, "'%s'", i->text);
        }
        fputc('\n', stream);
    }
    else
        fputs(emptyMessage, stream)
    return OPERATION_OK;
}