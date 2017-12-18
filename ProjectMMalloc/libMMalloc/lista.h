#ifndef __LISTA_H__
#define __LISTA_H__
#include <stdio.h>
#include <stdlib.h>
#include "mmalloc.h"

typedef struct nodo_t
{
	void* ram_ptr;
	size_t size;
	size_t id;
	//Ponemos aqui struct para ayudar al compilador a pasar por este trozo de codigo, ya que si no
	//el referenciarse a si mismo daria error.
	struct nodo_t * next;
	struct nodo_t * prev;

}nodo_t;

typedef struct lista_t
{
	int size; //cuantos nodos tenemos
	struct nodo_t * first;
	struct nodo_t * last;

}lista_t;

lista_t* initList(struct ram_struct_t* ram);

//Para crear nuevos nodos
nodo_t* newNode(struct ram_struct_t* ram);

//Nos deberia de crear un nuevo nodo con ese tamaño de memoria reservado
void addNewNode(struct ram_struct_t* ram, lista_t* list, size_t size);

//Nos devolveria un nodo con la informacion que guardamos usando esa key.
nodo_t* getNode(lista_t* list, void* key);

int removeNode(lista_t* list, nodo_t* rNode);
int addNode(lista_t* list, nodo_t* nNode);

#endif