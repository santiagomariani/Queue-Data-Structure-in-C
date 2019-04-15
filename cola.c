#include "cola.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct nodo{
	void* dato;
	struct nodo* prox;
}nodo_t;

struct cola{
	nodo_t* prim;
	nodo_t* ult;
};


cola_t* cola_crear(void){
	cola_t* cola;
	cola = malloc(sizeof(cola_t));
	if(!cola){
		return NULL;
	}
	cola->prim = NULL;
	cola->ult = NULL;
	return cola;
}

void cola_destruir(cola_t *cola, void destruir_dato(void*)){
	void* x;

	while(!cola_esta_vacia(cola)){
		x = cola_desencolar(cola);
		if(destruir_dato){
			destruir_dato(x);
		}
	}
	free(cola);
}

bool cola_esta_vacia(const cola_t *cola){
	return cola->prim == NULL;
}

nodo_t* crear_nodo(void *valor){
	nodo_t* nodo = malloc(sizeof(nodo_t));
	nodo->dato = valor;
	nodo->prox = NULL;
	return nodo;
}

bool cola_encolar(cola_t *cola, void* valor){
	nodo_t* nodo_nuevo = crear_nodo(valor);

	if(!nodo_nuevo){
		return false;
	}

	if(cola_esta_vacia(cola)){
		cola->prim = nodo_nuevo;
		cola->ult = nodo_nuevo;
		return true;
	}
	cola->ult->prox = nodo_nuevo;
	cola->ult = nodo_nuevo;
	return true;
}

void* cola_ver_primero(const cola_t *cola){
	if(cola_esta_vacia(cola)){
		return NULL;
	}
	return cola->prim->dato;
}

void* cola_desencolar(cola_t *cola){
	if(cola_esta_vacia(cola)){
		return NULL;
	}
	nodo_t* aux = cola->prim;
	void* x = aux->dato;

	if(cola->prim != cola->ult){
		cola->prim = aux->prox;
		free(aux);
		return x;
	}
	cola->prim = NULL;
	cola->ult = NULL;
	free(aux);
	return x;
}

