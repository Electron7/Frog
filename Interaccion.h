#ifndef _INTERACCION_H
#define _INTERACCION_H

#include "../../lib/glut.h"
#include "Rana.h"
#include "Caja.h"
#include "Coche.h"
#include "Tronco.h"

class Interaccion
{
public:
	Interaccion();
	virtual ~Interaccion();
	static void Rebote(Rana &h, Caja c,Tronco tronco);
	static void Rebote(Coche &c, Caja caja);
	static void Rebote(Tronco &t, Caja caja);
	static void Rebote(Rana &r, Coche c);
};

#endif
