#include "cola.h"
#include "testing.h"
#include "pila.h"
#include "vector_dinamico.h"
#include <stddef.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_cola_vacia() { 

	cola_t* cola = cola_crear();
	
	print_test("Crear cola nueva",cola);
	print_test("Cola vacia inicialmente",cola_esta_vacia(cola));
	print_test("Cola vacia: Ver primero es NULL",cola_ver_primero(cola) == NULL);
	print_test("Cola vacia: Desencolar es NULL",!cola_desencolar(cola));
	
	cola_destruir(cola,NULL);
}

void pruebas_cola_NULL(){

	cola_t* cola = cola_crear();
	print_test("Crear cola nueva",cola);
	print_test("Cola vacia inicialmente",cola_esta_vacia(cola));

	print_test("Se encola NULL",cola_encolar(cola,NULL));
	print_test("Ver primero muestra NULL",cola_ver_primero(cola) == NULL);
	print_test("Desencolar devuelve NULL",!cola_desencolar(cola));
	print_test("Cola vacia",cola_esta_vacia(cola));
	cola_destruir(cola,NULL);
}

void pruebas_cola_elementos(){

	cola_t* cola = cola_crear();
	print_test("Crear cola nueva",cola);
	print_test("Cola vacia inicialmente",cola_esta_vacia(cola));

	int valor1 = 1;
	int valor2 = 2;
	int valor3 = 3;
	
	void* pvalor1 = &valor1;
	void* pvalor2 = &valor2;
	void* pvalor3 = &valor3;

	print_test("Se encola valor1",cola_encolar(cola,pvalor1));
	print_test("Ver primero muestra valor1",cola_ver_primero(cola) == pvalor1);
	print_test("Se encola valor2",cola_encolar(cola,pvalor2));
	print_test("Ver primero muestra valor1",cola_ver_primero(cola) == pvalor1);
	print_test("Se encola valor3",cola_encolar(cola,pvalor3));
	print_test("Ver primero muestra valor1",cola_ver_primero(cola) == pvalor1);

	print_test("Desencolar devuelve valor1",cola_desencolar(cola) == pvalor1);
	print_test("Ver primero muestra valor 2",cola_ver_primero(cola) == pvalor2);
	print_test("Desencolar devuelve valor2",cola_desencolar(cola) == pvalor2);
	print_test("Ver primero muestra valor 3",cola_ver_primero(cola) == pvalor3);
	print_test("Desencolar devuelve valor3",cola_desencolar(cola) == pvalor3);
	print_test("Cola esta vacia",cola_esta_vacia(cola));

	for(int i=0;i<1000;i++){
		cola_encolar(cola,pvalor1);
	}
	print_test("Se encola 1000 veces valor1",cola_ver_primero(cola) == pvalor1);

	for(int i=0;i<1000;i++){
		cola_desencolar(cola);
	}
	print_test("Se desencola 1000 veces valor1",true);
	print_test("Cola esta vacia",cola_esta_vacia(cola));

	for(int i=0;i<100;i++){
		cola_encolar(cola,pvalor1);
		cola_desencolar(cola);
	}
	print_test("Encolar/desenconlar consecutivo: cola esta vacia",cola_esta_vacia(cola));

	cola_destruir(cola,NULL);
}

void wrapper_pila_destruir(void* pila){
	pila_destruir((pila_t*)pila);
}

void wrapper_vectordinamico_destruir(void* vd){
	vector_destruir(vd);
}

void pruebas_cola_destruir(){

	cola_t* cola = cola_crear();
	print_test("Cola vacia",cola_esta_vacia(cola));

	pila_t* pila1 = pila_crear();
	pila_t* pila2 = pila_crear();
	pila_t* pila3 = pila_crear();
	
	print_test("Se encola pila1",cola_encolar(cola,pila1));
	print_test("Ver primero muestra pila1",cola_ver_primero(cola) == pila1);
	print_test("Se encola pila2",cola_encolar(cola,pila2));
	print_test("Ver primero muestra pila1",cola_ver_primero(cola) == pila1);
	print_test("Se encola pila3",cola_encolar(cola,pila3));
	print_test("Ver primero muestra pila1",cola_ver_primero(cola) == pila1);
	
	cola_destruir(cola,wrapper_pila_destruir);

	cola = cola_crear();
	print_test("Cola vacia",cola_esta_vacia(cola));

	vector_t* vec1 = vector_crear(5);
	vector_t* vec2 = vector_crear(5);
	vector_t* vec3 = vector_crear(5);

	print_test("Se encola vec1",cola_encolar(cola,vec1));
	print_test("Ver primero muestra vec1",cola_ver_primero(cola) == vec1);
	print_test("Se encola vec1",cola_encolar(cola,vec2));
	print_test("Ver primero muestra vec1",cola_ver_primero(cola) == vec1);
	print_test("Se encola vec3",cola_encolar(cola,vec3));
	print_test("Ver primero muestra vec1",cola_ver_primero(cola) == vec1);

	cola_destruir(cola,wrapper_vectordinamico_destruir);
}

void pruebas_cola_alumno(){
	pruebas_cola_vacia();
	pruebas_cola_elementos();
	pruebas_cola_destruir();
}

// //////////////////////////////
