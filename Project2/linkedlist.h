/**
 * Author: Huang Kaisheng <2020215138@stu.cqupt.edu.cn>
 * Description: Definition of linked list
 * Version: 2022/10/07
 */
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

/**
 * Create a new list or node
 * @return a list node object pointer
 */
LinkedList* llNewList();

/**
 * Insert a node after specified index. If specified index exceeded,
 * we will insert at the end. If text duplicates, no changes will happen.
 * @param list the linked list
 * @param text the text content to be inserted
 * @param len the length of text
 * @param index the index to be inserted after
 * @return error code
 */
LinkedListErrorType llInsertAfter(LinkedList *list, char *text, const int len, const int index);

/**
 * Insert a node before specified index. If specified index exceeded,
 * we will insert at the front. If text duplicates, no changes will happen.
 * @param list the linked list
 * @param text the text content to be inserted
 * @param len the length of text
 * @param index the index to be inserted before
 * @return error code
 */
LinkedListErrorType llInsertBefore(LinkedList *list, char *text, const int len, const int index);

/**
 * Delete a node at specified index. If specified index exceeded, no changes will happen.
 * @param list the linked list
 * @param index the index to be deleted
 * @return error code
 */
LinkedListErrorType llDelete(LinkedList *list, const int index);

/**
 * Insert a node before specified index. If specified index exceeded or text duplicates,
 * no changes will happen.
 * @param list the linked list
 * @param text the text content to be inserted
 * @param len the length of text
 * @param index the index to be inserted before
 * @return error code
 */
LinkedListErrorType llReplace(LinkedList *list, char *text, const int len, const int index);

/**
 * Print all texts in the linked list with comma seperated.
 * @param list the linked list
 * @param stream the file stream to print. If you just want to show on screen, use stdout.
 * @param emptyMessage the message printed if linked list is empty.
 */
void llPrint(LinkedList *list, FILE *stream, const char *emptyMessage);

#endif