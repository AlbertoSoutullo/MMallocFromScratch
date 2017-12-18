#ifndef _LIB_MMALLOC_H
#define _LIB_MMALLOC_H

#include "lista.h"
//No repite las cabeceras cada vez que yo las copie

//Las estructuras tambien deberian estar en esta cabecera

//Deberia tener un puntero a la ram y su tamaño. tambien nos interesa el tamaño restante ya quye vamos a estar sacando trozos
typedef  struct ram_struct_t 
{
	void* ptr_ram;
	size_t total_size;
	size_t free_size;
	lista_t *nodosOcupados;
	lista_t *nodosLibres;
}ram_struct_t;

//La memoria alineada es dependiente del tipo del proyecto (x86 o x64). Esta En la barra de arriva del Visual
//Cuando trabajemos con memoria deberiamos usar size_t

//Inicializaria nuestra libreria a partir de un puntero raw apuntando al inicio de la RAM que vamos a estar utilizando.
//Nuestro gestor de memoria lo que va a hacer es coger un trozo de memoria y gestionarlo.
void init_mmalloc(void* ptr_ram, size_t size);


void* mmalloc(size_t size);
void* mrealloc(void* ptr, size_t size);
int mfree(void* ptr);

#endif