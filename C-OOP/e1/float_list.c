#include "linked_list.h"
#include "float_list.h"
#include <stdio.h>


void FloatList_print(ListHead* head){
    ListItem* aux = head->first;
    FloatListItem* elem = (FloatListItem*)aux;
    printf("[");
    while(aux){
        printf("%f,",elem->info);
        aux = aux->next;
        elem = (FloatListItem*)aux;
    }
    printf("]");
}