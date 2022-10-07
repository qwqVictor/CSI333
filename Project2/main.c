#include <stdio.h>
#include "linkedlist.h"

#define eq(x) (!strncmp(cmd, x, sizeof(x)))

int main(int argc, char const *argv[]) {
    LinkedList* list = llNewList();
    char cmd[5], text[255];
    int index;
    while (1) {
        cmd[0] = text[0] = 0;
        scanf("%s", cmd);
        if (eq("ina")) {
            scanf("%d %s", &index, text);
            LinkedListErrorType err = llInsertAfter(list, text, strlen(text), index);
            switch (err) {
                case OPERATION_OK:
                    puts("Insertion After OK!");
                    break;
                case INSERTION_DUPLICATE:
                    puts("Insertion of a duplicate failed!");
                    break;
                case INSERTED_AT_BORDER:
                    puts("Inserted at the end!");
                    break;
            }
        }
        else if (eq("inb")) {
            scanf("%d %s", &index, text);
            LinkedListErrorType err = llInsertBefore(list, text, strlen(text), index);
            switch (err) {
            case OPERATION_OK:
                puts("Insertion Before OK!");
                break;
            case INSERTION_DUPLICATE:
                puts("Insertion of a duplicate failed!");
                break;
            case INSERTED_AT_BORDER:
                puts("Inserted at the front!");
                break;
            }
        }
        else if (eq("del")) {
            scanf("%d", &index);
            LinkedListErrorType err = llDelete(list, index);
            switch (err) {
            case OPERATION_OK:
                puts("Deletion OK!");
                break;
            case UNCHANGED:
                puts("No changes!");
                break;
            }
        }
        else if (eq("rep")) {
            scanf("%d %s", &index, text);
            LinkedListErrorType err = llReplace(list, text, strlen(text), index);
            switch (err) {
            case OPERATION_OK:
                puts("Replacement OK!");
                break;
            case UNCHANGED:
                puts("No changes!");
                break;
            }
        }
        else if (eq("prn")) {
            llPrint(list, stdout, "Empty list!");
        }
        else if (eq("exit")) {
            goto EXIT;
        }
    }
EXIT:
    return 0;
}