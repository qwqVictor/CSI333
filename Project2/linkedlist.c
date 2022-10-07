/**
 * Author: Huang Kaisheng <2020215138@stu.cqupt.edu.cn>
 * Description: Implementation of linked list
 * Version: 2022/10/07
 */
#include "linkedlist.h"

/**
 * (private) Find previous node of index
 * @param list the linked list
 * @param index the index to find
 * @return previous node of index
 */
LinkedList* _llFindIndex(LinkedList* list, const int index) {
    LinkedList* p = list;
    for (; p->next != NULL; p = p->next) {
        if (p->next != NULL && (p->next)->index == index)       // find the proper node or last node
            return p;
    }
    return p;
}

LinkedList* llNewList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList)); // allocate memory
    list->index = 0;
    list->next = NULL;
    list->text[LINKED_LIST_MAX_LENGTH - 1] = 0;
    return list;
}

LinkedListErrorType llInsertAfter(LinkedList* list, char* text, const int len, const int index) {
    LinkedList *prev = _llFindIndex(list, index), *target = NULL, *node;
    LinkedListErrorType ret = OPERATION_OK;
    if (prev->next != NULL)
        target = prev->next;
    else {
        ret = INSERTED_AT_BORDER;
        target = prev;
    }
    for (LinkedList* i = list->next; i != NULL; i = i->next)          // deduplication
        if (strlen(i->text) == len && (!strncmp(text, i->text, len)))
            return INSERTION_DUPLICATE;
    node = llNewList();
    node->index = target->index + 1;
    strncpy(node->text, text, len);             // copy data
    if (target->next != NULL) {                 // if not the end, update index after this respectively
        node->next = target->next;
        int newIndex = node->index + 1;
        for (LinkedList* i = node->next; i != NULL; i = i->next)
            i->index = newIndex++;
    } else {
        node->next = NULL;
    }
    target->next = node;    // update next pointer
    return ret;
}

LinkedListErrorType llInsertBefore(LinkedList* list, char* text, const int len, const int index) {
    LinkedList *prev = _llFindIndex(list, index), *target = NULL, *node;
    LinkedListErrorType ret = OPERATION_OK;
    if (prev->next == NULL) {
        ret = INSERTED_AT_BORDER;
        target = list;              // if found the last node as prev, use first meta node
    }
    else {
        target = prev;
    }
    for (LinkedList* i = list->next; i != NULL; i = i->next)
        if (strlen(i->text) == len && (!strncmp(text, i->text, len)))
            return INSERTION_DUPLICATE;
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
    target->next = node;
    return ret;
}

LinkedListErrorType llDelete(LinkedList* list, const int index) {
    LinkedList* prev = _llFindIndex(list, index);
    if (prev->next == NULL) {
        return UNCHANGED;
    }
    else {
        LinkedList* toBeDeleted = prev->next;
        prev->next = toBeDeleted->next;
        free((void*)toBeDeleted);       // recycle memory
        int newIndex = prev->index + 1;
        for (LinkedList* i = prev->next; i != NULL; i = i->next)
            i->index = newIndex++;
    }
    return OPERATION_OK;
}

LinkedListErrorType llReplace(LinkedList* list, char* text, const int len, const int index) {
    LinkedList* prev = _llFindIndex(list, index);
    if (prev->next == NULL)
        return UNCHANGED;
    LinkedList* target = prev->next;
    for (LinkedList* i = list->next; i != NULL; i = i->next)
        if (strlen(i->text) == len && (!strncmp(text, i->text, len)))
            return UNCHANGED;
    LinkedList* node = llNewList();
    node->next = target->next;
    node->index = target->index;
    strncpy(node->text, text, len);
    free((void*)target);
    prev->next = node;
    return OPERATION_OK;
}

void llPrint(LinkedList* list, FILE* stream, const char* emptyMessage) {
    if (list->next != NULL) {
        for (LinkedList* i = list->next; i != NULL; i = i->next) {
            if (i != list->next)        // if not the first one, print comma
                fprintf(stream, ", ");
            fprintf(stream, "'%s'", i->text);
        }
        fputc('\n', stream);
    }
    else
        fprintf(stream, "%s\n", emptyMessage);
}