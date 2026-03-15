#include "linked_list.h"
#include "int_list.h"
#include <stdio.h>


void IntList_print(ListHead* head){
    ListItem* aux = head->first;
    IntListItem* elem = (IntListItem*)aux;
    printf("[");
    while(aux){
        printf("%d,",elem->info);
        aux = aux->next;
        elem = (IntListItem*)aux;
    }
    printf("]");
}
