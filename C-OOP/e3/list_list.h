#pragma once
#include <stdio.h>
#include "linked_list.h"


typedef struct ListListItem{
    ListItem list;
    ListHead* elem_list_head;
}ListListItem;

void ListListItem_print(ListItem* item);
void ListListItem_destroy(ListItem* item);
