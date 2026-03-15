#include "linked_list.h"
#include "int_list.h"
#include <stdio.h>


void IntListItem_print(ListItem* item){
    printf("[int] %d\n",((IntListItem*)item)->info);
}    
