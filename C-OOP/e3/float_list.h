#pragma once 
#include <stdio.h>
#include "linked_list.h"

typedef struct FloatListItem{
    ListItem list;
    float info;
}FloatListItem;

void FloatListItem_print(ListItem* head);