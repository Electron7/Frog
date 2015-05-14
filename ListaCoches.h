#pragma once
#define MAX_COCHES 100
#include "dominio\Coche.h"

class ListaCoches
{
public:
	ListaCoches();
	~ListaCoches();

	bool Agregar(Coche *c);
	void Dibuja();
	void Mueve(float t);
	//Para eliminar los coches al llegar al final de la carretera
	void Eliminar(int index);
	void Eliminar(Coche *c);
	void DestruirContenido();

private:
	// Vector de punteros a objeto tipo Coche, capaz de almacenar 100 punteros
	Coche * lista[MAX_COCHES];
	// Atributo que lleva la cuenta de las esferas que llevamos almacenadas
	int numero;
};

