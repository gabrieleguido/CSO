#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linked_list.h"
#include "float_list.h"
#include "list_list.h"
#define ROWS 4
#define COLUMNS 6

void Float_List_List_print(ListHead* head){
    ListItem* aux = head->first; 
    printf("[\n");
    while(aux){
        ListListItem* elem_list = (ListListItem*)aux;
        FloatList_print(elem_list->elem_list_head);
        printf("\n");
        aux = aux->next;
    }
    printf("]\n");

}

int main(int argc, char** argv) {
    ListHead head;
    List_init(&head);
    for(int i=0;i<ROWS;i++){
        ListListItem* elem_list = (ListListItem*)malloc(sizeof(ListListItem));
        elem_list->list.next = NULL;
        elem_list->list.prev = NULL;
        elem_list->elem_list_head = (ListHead*)malloc(sizeof(ListHead));
        List_init(elem_list->elem_list_head);
        List_insert(&head,head.last,(ListItem*)elem_list);
        for(int j = 0; j<COLUMNS;j++){
            FloatListItem* elem = (FloatListItem*)malloc(sizeof(FloatListItem));
            elem->list.next = NULL;
            elem->list.prev = NULL;
            elem->info = i+j+0.5f;
            List_insert(elem_list->elem_list_head,elem_list->elem_list_head->last,(ListItem*)elem);
        }
    }
    // printf("qui\n");
    Float_List_List_print(&head);
}