#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// inizializza head della lista
void List_init(ListHead *head) {
  head->first = NULL;
  head->last = NULL;
  head->size = 0;
}
// cerca item in head, se lo trova lo restituisce, altrimenti restituisce NULL
ListItem *List_find(ListHead *head, ListItem *item) {
  ListItem *aux = head->first;
  while (aux) {
    if (aux == item) {
      return item;
    }
    aux = item->next;
  }
  return NULL;
}
// inserisce item dopo prev in head
ListItem *List_insert(ListHead *head, ListItem *prev, ListItem *item){
  if(item->next || item->prev){
    return NULL;
  }
  #ifdef _LIST_DEBUG_
  ListItem* instance = List_find(head,item);
  assert(!instance);

  if(prev){
    ListItem* prev_instance = List_find(head,prev);
    assert(prev_instance);
  }
  #endif
  ListItem* next = prev? prev->next : head->first;
  if(prev){
    item->prev = prev;
    prev->next = item;
  }
  if(next){
    item->next = next;
    next->prev = item;
  }
  if(!prev){
    head->first = item;
  }
  if(!next){
    head->last = item;
    head->size++;
    return item;
  }
}
// rimuove item da head e lo restituisce (se presente), altrimenti ritorna NULL
ListItem *List_detach(ListHead *head, ListItem *item){
  #ifdef _LIST_DEBUG_ 
  ListItem* instance = List_find(head,item);
  asset(instance);
  #endif

  ListItem* prev = item->prev;
  ListItem* next = item->next;
  if(prev){
    prev->next = next;
  }
  if(next){
    next->prev = prev;
  }
  if(item == head->first){
    head->first = next;
  }
  if(item == head->last){
    head->last = prev;
  }
  head->size--;
  item->next = item->prev = NULL;
  return item;
}

void ListItem_constructor(ListItem* item,ListItemOps* ops){
  item->next = item->prev = NULL;
  item->ops = ops;
}

void List_print(ListHead* head){
  ListItem* aux = head->first;
  printf("Prtinting list of %d items:\n",head->size);
  int k = 0;
  while(aux){
    printf("[%d]",k);
    ListItem_print(aux);
    aux = aux->next;
    k++;
  }
}

void List_destroy(ListHead* head){
  assert(head);
  ListItem* item;
  while(head->first){
      ListItem* item = List_detach(head,item);
    ListItem_destroy(item);
    free(item);
  }
}

void ListItem_destroy(ListItem* item){
  assert(item);
  assert(item->ops && item->ops->dtor_fn);
  (*item->ops->dtor_fn)(item);
}

void ListItem_print(ListItem* item){
  assert(item);
  assert(item->ops && item->ops->print_fn);
  (*item->ops->print_fn)(item);
}
