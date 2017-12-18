#include "mmalloc.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
//Para acelerar los tiempos de compilacion, cuantos menos .h haya en otros .h más rapidas suelen ser las compilaciones. Si metemos stdio
//En distintos includes es probable que se te acabe repitiendo.

ram_struct_t* ram; //Representa los metadatos sobre esta ram (inicio, tamaño y tamaño libre.)
//Si lo ponemos asi, solo su referencia va a estar en stack. En verdad se deberían hacer con variables externas pero lo hacemos así
//para simplificar el código.

void init_mmalloc(void* ptr_ram, size_t size)
{
	//Deberiamos empezar reservando el espacio al puntero para nuestra estructura.
	//Si lo ponemos como variable global, estaría en stack, y no deberiamos usar el stack, ya que nuestro objetivo es que esté todo de la ram, y este metadato
	//estaría fuera de esa memoria. Teneoms que intentar que todo esté definido dentro de nuestro ptr.
	ram = (ram_struct_t*)ptr_ram; //Ya podemos empezar a utilizarla 1º
	ram->ptr_ram = ptr_ram;      //2º
	ram->total_size = size;
	size_t aux = (size_t)ram->ptr_ram; //almacenamos la primera linea y lo almacenamos en algo parecido a un int, sumamos el desplazamiento y reapuntamos.
	aux += sizeof(ram_struct_t);
	ram->ptr_ram = (void*)aux;

	//Lo ponemos como char* porque ptr_ram es void*, entonces no sabe sumar sobre esto. Entonces cambiamos a char* que permite indexar a nivel de byte, ya que char* ocupa un byte.
	//Esto seria otra manera de hacer lo mismo
	//((char*)ram->ptr_ram) += sizeof(ram_struct_t); //3º(dibujo en libreta) //Avanzamos para que las siguientes reservas no sobreescriban nuestros datos.

	ram->free_size = ram->total_size - sizeof(ram_struct_t); //El tamaño que le queda es el que tenemos menos lo que ocupa la estructura.

	ram->nodosOcupados = initList(ram);
	ram->nodosLibres = initList(ram);
}




void* mmalloc(size_t size)
{
	//tamaño libre? tenemos que mirar si hay ram libre suficiente

	//añadir búsqueda de bloques libres(practica)

	addNewNode(ram, ram->nodosOcupados, size);
	
	return ram->nodosOcupados->last->ram_ptr;

	//return NULL;
}

void* mrealloc(void* ptr, size_t size)
{
	int i = 0;
	nodo_t* nNode = getNode(ram->nodosOcupados, ptr);
	if (nNode == NULL)
	{
		return NULL;
	}
	if (nNode->size < size)
	{
		//crear nuevo nodo
		addNewNode(ram, ram->nodosOcupados, size);
		nodo_t* onode = ram->nodosOcupados->last;
		//copiar datos
		char* datain = (char*)onode->ram_ptr;
		char* dataout = (char*)nNode->ram_ptr;
		for (i = 0; i < nNode->size; i++)
		{
			((char*)onode->ram_ptr)[i] = ((char*)nNode->ram_ptr)[i];

		}
		//liberar nodo antiguo
		mfree(ptr);
		//devolver el nuevo puntero
		return onode->ram_ptr;
	}
	else
	{
		return nNode->ram_ptr;
	}
	return NULL;
}

int mfree(void* ptr)
{
	nodo_t* nNode = getNode(ram->nodosOcupados, ptr);
	if (nNode == NULL)
	{
		return -1;
	}
	removeNode(ram->nodosOcupados, nNode);
	addNode(ram->nodosLibres, nNode);
	return 1;
}


/*pides memoria para el siguiente tamaño que sea multipli de lo que han pedido
si es multiplo tienes que añadir un hueco mas
de ese hueco si has reservado 16 megas vas a necesitar 16 mas algo par ahacer la conversion
a eso le aplicamos la mascara &0xfff0
quitamos el trozo que usamos para la conversion


numero de bits a cero que necesito es el logaritmo en base 2 del tamaño del alineamiento que te han pedido

malig_mall(size, align)
{
	((size/alig)+1)*align
}

*/
