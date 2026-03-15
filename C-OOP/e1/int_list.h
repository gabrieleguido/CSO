#include "linked_list.h"
typedef struct IntListItem{
    ListItem list;
    int info;
}IntListItem;

void IntList_print(ListHead* head);