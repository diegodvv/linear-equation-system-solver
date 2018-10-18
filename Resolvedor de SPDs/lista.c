#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "lista.h"

void lista_new(lista *lista, int elementoSize, freeFunction freeFn)
{
  assert(elementoSize > 0);
  lista->logicalLength = 0;
  lista->elementoSize = elementoSize;
  lista->prim = lista->tail = NULL;
  lista->freeFn = freeFn;
}

void lista_destroy(lista *lista)
{
  listaNo *current;
  while(lista->prim != NULL) {
    current = lista->prim;
    lista->prim = current->next;

    /*if(lista->freeFn) {
      lista->freeFn(current->data);
    }*/

    free(current->data);
    free(current);
  }
}

void lista_prepend(lista *lista, void *elemento)
{
  listaNo *No = malloc(sizeof(listaNo));
  No->data = malloc(lista->elementoSize);
  memcpy(No->data, elemento, lista->elementoSize);

  No->next = lista->prim;
  lista->prim = No;

  // first No?
  if(!lista->tail) {
    lista->tail = lista->prim;
  }

  lista->logicalLength++;
}

void lista_append(lista *lista, void *elemento)
{
  listaNo *No = malloc(sizeof(listaNo));
  No->data = malloc(lista->elementoSize);
  No->next = NULL;

  memcpy(No->data, elemento, lista->elementoSize);

  if(lista->logicalLength == 0) {
    lista->prim = lista->tail = No;
  } else {
    lista->tail->next = No;
    lista->tail = No;
  }

  lista->logicalLength++;
}

void lista_for_each(lista *lista, listaIterator iterator)
{
  assert(iterator != NULL);

  listaNo *No = lista->prim;
  bool result = TRUE;
  while(No != NULL && result) {
    result = iterator(No->data);
    No = No->next;
  }
}

void lista_prim(lista *lista, void *elemento, bool removeFromList)
{
  assert(lista->prim != NULL);

  listaNo *No = lista->prim;
  memcpy(elemento, No->data, lista->elementoSize);

  if(removeFromList) {
    lista->prim = No->next;
    lista->logicalLength--;

    free(No->data);
    free(No);
  }
}

void lista_tail(lista *lista, void *elemento)
{
  assert(lista->tail != NULL);
  listaNo *No = lista->tail;
  memcpy(elemento, No->data, lista->elementoSize);
}

int lista_size(lista *lista)
{
  return lista->logicalLength;
}
