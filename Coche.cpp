#include "Coche.h"
#include "glut.h"


Coche::Coche()
{
}

Coche::Coche(float l, float x, float y, Vector2D vector_vel, unsigned char roj, unsigned char ver, unsigned char azu)
{
	longitud = l;
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vector_vel.x;
	velocidad.y = vector_vel.y;
	rojo = roj;
	verde = ver;
	azul = azu;
}

Coche::~Coche()
{
}

void Coche::Dibuja()
{
	glPushMatrix();
	glColor3ub(rojo, verde, azul);
	glTranslatef(posicion.x, posicion.y, 0.0f);
	//PARA DIBUJAR UN RECTÁNGULO
	glScalef(longitud, 0.8, 1);//longitud, ancho y altura
	glutSolidCube(1);
	glPopMatrix();
	glEnd();
}

void Coche::Mueve(float t)
{
	// Ecuacion de movimiento NO acelerado para los coches
	// Se podría hacer que las motos si tengan aceleracion y los coches no, por ejemplo
	posicion.x = posicion.x + velocidad.x*t;
	posicion.y = posicion.y + velocidad.y*t;

}


