#ifndef __LISTA_INCLUDED_H
#define __LISTA_INCLUDED_H

// a common function used to free malloc'd objects
typedef void (*freeFunction)(void *);

typedef enum { FALSE, TRUE } bool;

typedef bool (*listaIterator)(void *);

typedef struct _listaNo {
  void *data;
  struct _listaNo *next;
} listaNo;

typedef struct {
  int logicalLength;
  int elementoSize;
  listaNo *prim;
  listaNo *tail;
  freeFunction freeFn;
} lista;

void lista_new(lista *lista, int elementoSize, freeFunction freeFn);
void lista_destroy(lista *lista);

void lista_prepend(lista *lista, void *elemento);
void lista_append(lista *lista, void *elemento);
int lista_size(lista *lista);

void lista_for_each(lista *lista, listaIterator iterator);
void lista_prim(lista *lista, void *elemento, bool removeFromList);
void lista_tail(lista *lista, void *elemento);

#endif
