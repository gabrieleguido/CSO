#pragma once
#include <stdio.h>

typedef struct ListItem {
  struct ListItem* prev;
  struct ListItem* next;
} ListItem;

typedef struct ListHead {
  ListItem* first;
  ListItem* last;
  int size;
} ListHead;


//inizializza head della lista 
void List_init(ListHead* head);
//cerca item in head, se lo trova lo restituisce, altrimenti restituisce NULL
ListItem* List_find(ListHead* head,ListItem* item);
//inserisce item dopo prev in head
ListItem* List_insert(ListHead* head,ListItem* prev,ListItem* item);
//rimuove item da head e lo restituisce (se presente), altrimenti ritorna NULL
ListItem* List_detach(ListHead* head,ListItem* item);