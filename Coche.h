#pragma once
#include "C:\Users\Windows 8\Desktop\Videojuego\Juego FROG 14_15\Tema4_inicial_2010\Pang\src\dominio\ObjetoMovil.h"
class Coche :
	public ObjetoMovil
{
	friend class Interaccion;

public:
	Coche();

	// Sobrecarga de Coche. Lo dejo comentado porque aun no tengo claro para que utilizarlo.
	// Antes de utilizarlo, cambiar el metodo SetVel que recoja dos float en vez de un Vector2D.

	Coche(float l, float x, float y, Vector2D vector_vel, unsigned char roj, unsigned char ver, unsigned char azu);

	~Coche();
	void Dibuja();
	void Mueve(float t);

private:
	float longitud=2;
};
