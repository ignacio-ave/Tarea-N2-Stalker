#ifndef Pila_h
#define Pila_h

typedef struct List List;

List * createList(void);

void * firstList(List * list);

void pushFront(List * list, void * data);

void * popFront(List * list);

#endif /* Pila_h */