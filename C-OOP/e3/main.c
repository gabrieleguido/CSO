#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linked_list.h"
#include "float_list.h"
#include "int_list.h"
#include "list_list.h"
#define ROWS 4
#define COLUMNS 6

ListItemOps int_ops = {
    .dtor_fn = 0,
    .print_fn = IntListItem_print
};
ListItemOps float_ops = {
    .dtor_fn = 0,
    .print_fn = FloatListItem_print
};
ListItemOps lislist_ops = {
    .dtor_fn = ListListItem_destroy,
    .print_fn = ListListItem_print
};

int main(int argc, char** argv) {
    ListHead head;
    List_init(&head);
    int k = 0;
    for(int i=0;i<ROWS;i++){
        ListListItem* elem_list = (ListListItem*)malloc(sizeof(ListListItem));
        ListItem_constructor((ListItem*)elem_list,&lislist_ops);
        elem_list->elem_list_head = (ListHead*)malloc(sizeof(ListHead));
        List_init(elem_list->elem_list_head);
        List_insert(&head,head.last,(ListItem*)elem_list);
        for(int j = 0; j<COLUMNS;j++){
            if(k%2){
                FloatListItem* elem = (FloatListItem*)malloc(sizeof(FloatListItem));
                elem->info = i+j+0.5f;
                ListItem_constructor((ListItem*)elem,&float_ops);
                List_insert(elem_list->elem_list_head,elem_list->elem_list_head->last,(ListItem*)elem);
            }else{
                IntListItem* elem = (IntListItem*)malloc(sizeof(IntListItem));
                elem->info = i+j+4;
                ListItem_constructor((ListItem*)elem,&int_ops);
                List_insert(elem_list->elem_list_head,elem_list->elem_list_head->last,(ListItem*)elem);
            }
            k++;
        }
    }
    // printf("qui\n");
    List_print(&head);
}