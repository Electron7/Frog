#include "Interaccion.h"

Interaccion::Interaccion()
{
}

Interaccion::~Interaccion()
{
}

void Interaccion::Rebote(Rana &h, Caja c,Tronco tronco)
{
	Vector2D velocidadnula;
	h.velocidad = velocidadnula;

	float xmin = c.linea.limite1.x;
	float xmax = c.linea.limite4.x;
	float ymax = c.llegada.limite2.y;
	float ymin = c.acera.limite1.y;
	if (h.posicion.x > xmax)h.posicion.x = xmax;
	if (h.posicion.x < xmin)h.posicion.x = xmin;
	if (h.posicion.y > ymax)h.posicion.y = ymax;
	if (h.posicion.y < ymin)h.posicion.y = ymin;

	float ymax_rio=c.rio.limite2.y;
	float ymin_rio=c.rio.limite1.y;
	if ((h.posicion.y < ymax_rio) && (h.posicion.y > ymin_rio))
	{
		if ((h.posicion.x > tronco.posicion.x - 10) && (h.posicion.x < tronco.posicion.x + 10))
		{
			if (tronco.posicion.y == h.posicion.y)
			{
				h.velocidad = tronco.velocidad;
			}
			else
			{
				h.velocidad = velocidadnula;
			}
		}
		else
			h.posicion = h.origen;
	}

}


void Interaccion::Rebote(Coche &c, Caja caja)
{
	float xmin = caja.linea.limite4.x;
	if (c.posicion.x > xmin)c.posicion.x = -20.0f;
}

void Interaccion::Rebote(Tronco &t, Caja caja)
{
	float xmin = caja.rio.limite2.x;
	if (t.posicion.x < xmin)t.posicion.x = 20.0f;
}

void Interaccion::Rebote(Rana &r, Coche c)
{
	float dist;
	Vector2D delta= r.posicion - c.posicion;
	dist = delta.modulo() - r.altura - c.altura;
	
	if (dist <= 0) r.posicion = r.origen;
}
