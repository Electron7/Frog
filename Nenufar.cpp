#include "Nenufar.h"

void Nenufar::Dibuja()
{
	glPushMatrix();
	glColor3ub(rojo, verde, azul);
	glTranslatef(posicion.x, posicion.y, -0.5f);
	//PARA DIBUJAR UN RECT¡NGULO
	glScalef(longitud, 0.8, 1);//longitud, ancho y altura
	glutSolidTeapot(longitud);
	glPopMatrix();
	glEnd();
}

Nenufar::~Nenufar()
{
}

Nenufar& Nenufar::operator=(const Nenufar& n)
{
	Tronco::operator=(n);
	longitud = n.longitud;
	return *this;
}
