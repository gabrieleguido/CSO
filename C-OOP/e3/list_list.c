#pragma once
#include <stdio.h>
#include "linked_list.h"
#include "list_list.h"
#include <assert.h>

void ListListItem_print(ListItem* item){
    assert(item);
    ListListItem* listlist = (ListListItem*) item;
    assert(listlist->elem_list_head);
    List_print(listlist->elem_list_head);
}
void ListListItem_destroy(ListItem* item){
    assert(item);
    ListListItem* listlist = (ListListItem*) item;
    List_destroy(listlist->elem_list_head);
}
