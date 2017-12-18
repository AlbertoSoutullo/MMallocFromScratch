#include "mmalloc.h"
#include "lista.h"

#include <stdio.h>
#include <stdlib.h>

lista_t* initList(struct ram_struct_t* ram)
{
	lista_t* list = (lista_t*)ram->ptr_ram; //sacamos otro trozo de la lista que vamos a utilizar y avanzamos
	((char*)ram->ptr_ram) += sizeof(lista_t);
	ram->free_size -= sizeof(lista_t);

	list->size = 0;
	list->first = NULL;
	list->last = NULL;

	return list;
}

nodo_t* newNode(struct ram_struct_t* ram)
{
	nodo_t* nNode = (nodo_t*)(ram->ptr_ram);
	((char*)ram->ptr_ram) += sizeof(nodo_t);
	ram->free_size -= sizeof(nodo_t);

	nNode->id = nNode->size = 0;
	nNode->next = nNode->prev = nNode->ram_ptr = NULL;

	return nNode;
}


void addNewNode(struct ram_struct_t* ram, lista_t* list, size_t size) 
{
	nodo_t* last = list->last;
	nodo_t* nNode = newNode(ram);
	nNode->ram_ptr = ram->ptr_ram;

	((char*)ram->ptr_ram) += size;
	ram->free_size -= size;

	nNode->id = (size_t)nNode->ram_ptr;
	nNode->size = size;

	addNode(list, nNode);
}

nodo_t* getNode(lista_t* list, void* key)
{
	int i = 0;
	int size = list->size;
	if (list == NULL)
	{
		return NULL;
	}
	if (size == 0)
	{
		return NULL;
	}
	nodo_t* lastChecked = list->first;

	for (i=0; i < list->size; i++)
	{
		if (lastChecked->id == (size_t)key)
		{
			return lastChecked;
		}
		else
		{
			lastChecked = lastChecked->next;
		}
	}
	return NULL;
}

int removeNode(lista_t* list, nodo_t* rNode)
{
	nodo_t* nNode = getNode(list, (void*)rNode->id);
	if (nNode != NULL)
	{
		nNode->prev->next = nNode->next;
		nNode->prev->prev = nNode->prev;
		if (list->first == nNode)
		{
			list->first = nNode->next;
		}
		if (list->last == nNode)
		{
			list->last = nNode->prev;
		}
		list->size--;
		if (list->size == 0)
		{
			list->first = list->last = NULL;
		}
		return 0;
	}
	return -1;
}

int addNode(lista_t* list, nodo_t* nNode)
{
	int i = 0;
	nodo_t* last = list->last;

	int nNodes = list->size;
	if (nNodes == 0)
	{
		list->first = list->last = nNode;
		nNode->next = nNode->prev = nNode;
	}
	else
	{
		last->next = nNode;
		list->last = nNode;
		list->first->prev = nNode;
		nNode->next = list->first;
		nNode->prev = last;
	}

	list->size++;
	return 0;
}
