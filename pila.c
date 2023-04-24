#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pila.h"

typedef struct Node Node;



struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List *local = (List*) malloc(sizeof(List));
  if (local == NULL) exit(EXIT_FAILURE);
  local->head = NULL;
  return local;
}

void * firstList(List * list) {
  if (list->head == NULL) return NULL;
  return list->head->data;
}

void pushFront(List * list, void * data) {
  Node *aux = createNode(data);
  aux->next = list->head;
  list->head = aux;
}

void * popFront(List * list) {
  Node * aux = list->head->data;
  if (!list->head->next) {
    list->head = NULL;
  }
  else{
    list->head = list->head->next;
    list->head->prev = NULL;
  }
  return aux;
}