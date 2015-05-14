#include "Mundo.h"
#include "glut.h"
#include <math.h>

Mundo::Mundo()
{
}

void Mundo::RotarOjo()
{
	float dist=sqrt(x_ojo*x_ojo+z_ojo*z_ojo);
	float ang=atan2(z_ojo,x_ojo);
	ang+=0.05f;
	x_ojo=dist*cos(ang);
	z_ojo=dist*sin(ang);
}
void Mundo::Dibuja()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
			7.5, 5.0, 0.0,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)   

	//aqui es donde hay que poner el codigo de dibujo

	plataforma.Dibuja();
	rana.Dibuja();
	coche.Dibuja();
	tronco.Dibuja();
	coches.Dibuja(); // Lista de coches..
	tronco2.Dibuja();

}

void Mundo::Mueve()
{
	coche.Mueve(0.025f);
	tronco.Mueve(0.025f);
	coches.Mueve(0.025f);
	tronco2.Mueve(0.025f);
	rana.Mueve(0.025f);

	//Para que redibuje cuando la rana pase los limites.
	Interaccion::Rebote(rana, plataforma, tronco);
	Interaccion::Rebote(coche, plataforma);
	Interaccion::Rebote(tronco, plataforma);
	Interaccion::Rebote(rana, coche);
	// Interacciones para el tronco2.. borrar cuando hagamos la lista de troncos
	Interaccion::Rebote(rana, plataforma, tronco2);
	Interaccion::Rebote(tronco2, plataforma);



}

// Ahora inicializamos todo lo que haya que inicializar.
// Como por ejemplo, la posicion inicial de la rana, a traves del metodo
// SetPos de la clase rana.

void Mundo::Inicializa()
{
	x_ojo=7.5;
	y_ojo=-5;
	z_ojo=15;


	//Inicializaciones de la ranita
	rana.SetPos(7.5f, 0.5f);


	// Inicializaciones del coche
	// La posición de salida viene determinada por 'x' e 'y'. El comando de dibujo dibuja a partir del vértice inferior,
	// así que para esta en el medio de una calle habrá que poner numeros enteros, y no medios. Esto es justo lo 
	// contrario de lo que ocurre con la rana esfera, que se sitúa dando como parámetro el centro de la esfera, y por
	// tanto, si se quiere que esté en el medio de una calle, habrá que poner por ejemplo 3.5
	coche.SetPos(15, 1.5f);

	coche.SetColor(255, 0, 0);

	Vector2D vel_coche;
	vel_coche.x = -3;
	vel_coche.y = 0;
	coche.SetVel(vel_coche);


	//Inicializaciones del tronco1
	tronco.SetPos(15, 8.5f); 
	tronco.SetColor(255, 255, 0);
	//Inicializaciones del tronco2
	tronco2.SetPos(15, 6.5f);
	tronco2.SetColor(255, 255, 0);

	Vector2D vel_tronco;
	vel_tronco.x = -4;
	vel_tronco.y = 0;
	tronco.SetVel(vel_tronco);
	tronco2.SetVel(vel_tronco);

	// Inicializadores de la lista de coches
	// NOTA: Esto te pinta todos de la misma forma. Si queremos motos, coches y troncos
	// en diferentes carriles creo que habrá que hacer diferentes clases con diferentes 'Mueve'
	// y 'Dibuja'. Aunque la clase ListaCoches podria usarse para las listas de todo.. (creo)
	// Ya lo tengo, lo ideal seria sobrecargar el constructor para así hacer diferentes coches (pag114 del guion 
	// viene explicado perfecto.

	//Gracias a la variable auxiliar aux, vamos metiendo uno por uno los objetos "coche" en la lista de coches.
	for (int i = 0; i < 4; i++)
	{
		// Carril 1..
		Coche* aux1 = new Coche;
		aux1->SetPos(15+4*i, 1.5f);
		Vector2D vel1;
		vel1.x = (-3);
		vel1.y = 0;
		aux1->SetVel(vel1);

		// Carril 2..
		Vector2D vel2;
		vel2.x = 3.0f;
		vel2.y = 0.0f; 
		Coche* aux2 = new Coche(2.0f, 0 - 6 * i, 2.5f, vel2, 255, 0, 0);

		// Carril 3..
		Vector2D vel3;
		vel3.x = -3.5f;
		vel3.y = 0.0f;
		Coche* aux3 = new Coche(0.8f, 15 + 6 * i, 3.5f, vel3, 70, 200, 0);

		// Carril 4..
		Vector2D vel4;
		vel4.x = 2.5f;
		vel4.y = 0.0f;
		Coche* aux4 = new Coche(1.3f, 0 - 6 * i, 4.5f, vel4, 255, 100, 0);
		
		
		coches.Agregar(aux1);
		coches.Agregar(aux2);
		coches.Agregar(aux3);
		coches.Agregar(aux4);
	}

}

void Mundo::Tecla(unsigned char key)
{
	switch (key)
	{
	case 'a':
		rana.SetPos(rana.posicion.x - 1.0, rana.posicion.y);
		break;
	case 'd':
		rana.SetPos(rana.posicion.x + 1.0, rana.posicion.y);
		break;
	case 'w':
		rana.SetPos(rana.posicion.x, rana.posicion.y + 1.0);
		break;
	case 's':
		rana.SetPos(rana.posicion.x, rana.posicion.y - 1.0);
		break;

	}
}

Mundo::~Mundo()
{
	coches.DestruirContenido();
}
