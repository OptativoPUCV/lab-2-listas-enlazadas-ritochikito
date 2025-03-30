#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
  void *data;
  Node *next;
  Node *prev;
};

struct List {
  Node *head;
  Node *tail;
  Node *current;
};

typedef List List;

Node *createNode(void *data) {
  Node *new = (Node *)malloc(sizeof(Node));
  assert(new != NULL);
  new->data = data;
  new->prev = NULL;
  new->next = NULL;
  return new;
}

List *createList() {
  List *L = (List *)malloc(sizeof(List));
  L->head = NULL;
  L->tail = 0;
  L->current = NULL;
  return L;
}

void *firstList(List *list) {
  list->current = list->head;
  if (list->current)
    return (list->current->data);
  return NULL;
}

void *nextList(List *list) {
  if (!list || !list->current)
    return NULL;
  list->current = list->current->next;
  if (list->current)
    return (list->current->data);
  return NULL;
}

void *lastList(List *list) {
  if (!list)
    return NULL;
  list->current = list->head;
  while (list->current->next != NULL) {
    list->current = list->current->next;
  }
  return (list->current->data);
}

void *prevList(List *list) {
  if (!list || !list->current)
    return NULL;
  list->current = list->current->prev;
  if (list->current)
    return (list->current->data);
  return NULL;
}

void pushFront(List *list, void *data) {
  Node *newNode = createNode(data);
  if (list->head == NULL) {
    list->head = newNode;
    list->tail = newNode;
  } else {
    newNode->next = list->head;
    list->head->prev = newNode;
    list->head = newNode;
  }
}

void pushBack(List *list, void *data) {
  list->current = list->tail;
  pushCurrent(list, data);
}

void pushCurrent(List *list, void *data) {
  if (list->current == NULL) return;
  
  Node *newNode = createNode(data);
  newNode->next = list->current->next;
  newNode->prev = list->current;
  
  if (list->current->next != NULL)
    list->current->next->prev = newNode;
  else
    list->tail = newNode;
    
  list->current->next = newNode;
}

void *popFront(List *list) {
  list->current = list->head;
  return popCurrent(list);
}

void *popBack(List *list) {
  list->current = list->tail;
  return popCurrent(list);
}

void *popCurrent(List *list) {
  if (list->current == NULL) return NULL;

  Node *nodeToRemove = list->current;
  void *data = nodeToRemove->data;

  if (nodeToRemove->prev != NULL)
    nodeToRemove->prev->next = nodeToRemove->next;
  else
    list->head = nodeToRemove->next;

  if (nodeToRemove->next != NULL)
    nodeToRemove->next->prev = nodeToRemove->prev;
  else
    list->tail = nodeToRemove->prev;

  list->current = nodeToRemove->next;
  free(nodeToRemove);
  return data;
}

void cleanList(List *list) {
  while (list->head != NULL) {
    popFront(list);
  }
}