#include "linked_list.h"
#include "float_list.h"
#include <stdio.h>


void FloatListItem_print(ListItem* item){
    printf("[float] %f\n",((FloatListItem*) item)->info);
}