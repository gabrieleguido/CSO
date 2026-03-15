#include "linked_list.h"
typedef struct IntListItem{
    ListItem list;
    int info;
}IntListItem;

void IntListItem_print(ListItem* item);