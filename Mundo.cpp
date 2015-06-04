#include "Mundo.h"
using namespace std;
#include <iostream>

bool izquierda;
bool derecha;
bool recto;
bool atras;
bool h;
bool y;

Vector2D posicion_auxiliar;

void Mundo::Dibuja()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
		x_vista, y_vista, z_vista,      // hacia que punto mira  (0,0,0) 
		0, 0, 1);      // definimos hacia arriba (eje Y)   

	//aqui es donde hay que poner el codigo de dibujo
	//NOTESE QUE HEMOS CAMBIADO ESTO
	//PARA MIRAR AL CENTRO DE LA ESCENA
	plataforma.Dibuja();
	rana.Dibuja();
	coches.Dibuja();
	troncos.Dibuja();
	//OpenGL::Print("FROG", 0, 0, 255, 255, 255);
	//OpenGL::Print("by Manu Serrano & Ignacio Arroyo", 0, 20, 155, 255, 0);
}

void Mundo::Mover()
{
	coches.Mueve(0.025f);
	rana.Mueve(0.025f);
	troncos.Mueve(0.025f);

	//LIMITES DE LA RANA
	bool x = Interaccion::Rebote(rana, plataforma,izquierda,derecha,atras,recto);
	y = Interaccion::Llegada(rana, plataforma,recto);

	//LIMITES DE LOS COCHES
	//CREACION Y DESTRUCCION DE COCHES
	Coche *auxiliar_coche_destruido(coches.Destruccion(plataforma));// = coches.Destruccion(plataforma);
	if (auxiliar_coche_destruido != 0)
	{
		if (auxiliar_coche_destruido->SentidoVel(auxiliar_coche_destruido))
		{//auxiliar_coche_destruido->Clonar()
			if (auxiliar_coche_destruido->GetPos().y > 5)
			{
				if (coches.Agregar(new Bicicleta(auxiliar_coche_destruido->longitud,0,auxiliar_coche_destruido->posicion.y,auxiliar_coche_destruido->velocidad,auxiliar_coche_destruido->rojo,auxiliar_coche_destruido->verde,auxiliar_coche_destruido->azul,auxiliar_coche_destruido->ancho,auxiliar_coche_destruido->altura)))
					coches.Eliminar(auxiliar_coche_destruido);
			}
			else if (coches.Agregar(new Coche(auxiliar_coche_destruido->longitud, 0, auxiliar_coche_destruido->GetPos().y, auxiliar_coche_destruido->GetVel(), auxiliar_coche_destruido->GetRed(), auxiliar_coche_destruido->GetVer(), auxiliar_coche_destruido->GetAzu())))
				coches.Eliminar(auxiliar_coche_destruido);
		}
		else if (coches.Agregar(new Coche(auxiliar_coche_destruido->longitud, 15, auxiliar_coche_destruido->GetPos().y, auxiliar_coche_destruido->GetVel(), auxiliar_coche_destruido->GetRed(), auxiliar_coche_destruido->GetVer(), auxiliar_coche_destruido->GetAzu())))
			coches.Eliminar(auxiliar_coche_destruido);
	}
	
	//CREACION Y DESTRUCCION DE TRONCOS
	Tronco *auxiliar_tronco_destruido(troncos.Destruccion(plataforma));// = troncos.Destruccion(plataforma);
	if (auxiliar_tronco_destruido != 0)
	{
		if (auxiliar_tronco_destruido->SentidoVel(auxiliar_tronco_destruido))
		{
			if (troncos.Agregar(new Tronco( 0, auxiliar_tronco_destruido->GetPos().y, auxiliar_tronco_destruido->GetVel(), auxiliar_tronco_destruido->GetRed(), auxiliar_tronco_destruido->GetVer(), auxiliar_tronco_destruido->GetAzu())))
				troncos.Eliminar(auxiliar_tronco_destruido);
		}
		else if ((auxiliar_tronco_destruido->GetPos().y > 7) && (auxiliar_tronco_destruido->GetPos().y < 8))
		{
			if (troncos.Agregar(new Nenufar(15, auxiliar_tronco_destruido->GetPos().y, auxiliar_tronco_destruido->velocidad, auxiliar_tronco_destruido->rojo, auxiliar_tronco_destruido->verde, auxiliar_tronco_destruido->azul, auxiliar_tronco_destruido->longitud)))
				troncos.Eliminar(auxiliar_tronco_destruido);

		}
		else if(troncos.Agregar(new Tronco(15, auxiliar_tronco_destruido->GetPos().y, auxiliar_tronco_destruido->GetVel(), auxiliar_tronco_destruido->GetRed(), auxiliar_tronco_destruido->GetVer(), auxiliar_tronco_destruido->GetAzu())))
			troncos.Eliminar(auxiliar_tronco_destruido);
	}

	//Declaro velocidad nula y posicion origen para tratar la informaciÛn de las interacciones de la rana con las listas.
	Vector2D velocidad_nula;
	Vector2D posicion_origen;
	posicion_origen.x = 7.5f;
	posicion_origen.y = 0.5f;

	//Interacciones para los coches
	Coche *auxiliarcoche = coches.Colision(rana);
	if (auxiliarcoche != 0)
	{
		rana.SetPos(posicion_origen.x, posicion_origen.y);
		rana.z = 0;
		rana.SetVel(velocidad_nula);
		izquierda = false;
		derecha = false;
		recto = false;
		atras = false;
	}

	//Interacciones para los troncos
	Tronco *auxiliartronco = troncos.Rebote(plataforma, rana);
	if (auxiliartronco != 0)
	{
		rana.SetVel(auxiliartronco->GetVel());
		rana.SetPos(rana.GetPos().x, auxiliartronco->GetPos().y);
	}
	else
	{
		if (x == 1)
		{
				rana.SetVel(velocidad_nula);
				rana.SetPos(posicion_origen.x, posicion_origen.y);
		}
		else
		{
			if ((rana.GetPos().y>9)&&(recto==false))
				rana.SetVel(velocidad_nula);
		}
	}

	//MOVIMIENTO DE LA RANA
	if (izquierda == true)
	{
		if (rana.GetPos().x < (posicion_auxiliar.x - 1))
		{
			rana.SetVel(velocidad_nula);
			rana.SetPos(posicion_auxiliar.x-1,posicion_auxiliar.y);
			rana.z = 0;
			izquierda = false;
			rana.salto = false;
		}
	}
	if (derecha == true)
	{
		if (rana.GetPos().x > (posicion_auxiliar.x + 1))
		{
			rana.SetVel(velocidad_nula);
			rana.SetPos(posicion_auxiliar.x +1 , rana.GetPos().y);
			rana.z = 0;
			derecha = false;
			rana.salto = false;
		}
	}
	if (recto == true)
	{
		if (rana.GetPos().y > (posicion_auxiliar.y + 1))
		{
			rana.SetVel(velocidad_nula);
			rana.SetPos(rana.GetPos().x, posicion_auxiliar.y+1);
			rana.z = 0;
			recto = false;
			rana.salto = false;
		}
	}
	if (atras == true)
	{
		if (rana.GetPos().y < (posicion_auxiliar.y - 1))
		{
			rana.SetVel(velocidad_nula);
			rana.SetPos(rana.GetPos().x, posicion_auxiliar.y-1);
			rana.z = 0;
			atras = false;
			rana.salto = false;
		}
	}
}

void Mundo::Inicializa()
{
	x_ojo = 7.5f;
	y_ojo = 5;//-10;//-5
	z_ojo = 15;//15 80

	x_vista = 7.5f;//7.5f;
	y_vista = 5.01f;//10.0f;
	z_vista = 0.0f;

	//Inicializaciones de la ranita
	rana.SetPos(7.5f, 0.5f);
	
	// Inicializadores de la lista de coches
	// NOTA: Esto te pinta todos de la misma forma. Si queremos motos, coches y troncos
	// en diferentes carriles creo que habr· que hacer diferentes clases con diferentes 'Mueve'
	// y 'Dibuja'. Aunque la clase ListaCoches podria usarse para las listas de todo.. (creo) °°°POLIMORFISMO!!!
	// Ya lo tengo, lo ideal seria sobrecargar el constructor para asÌ hacer diferentes coches (pag114 del guion 
	// viene explicado perfecto.

	for (int i = 0; i < 4; i++)
	{
		// Carril 1..
		Vector2D vel1;
		vel1.x = (-3);
		vel1.y = 0;
		Coche* aux1 = new Coche(2.0f, 15 + 6 * i, 1.5f, vel1, 255, 0, 0);

		// Carril 2..
		Vector2D vel2;
		vel2.x = 3.0f;
		vel2.y = 0.0f;
		Coche* aux2 = new Coche(2.0f, 0 - 6 * i, 2.5f, vel2, 255, 0, 0);

		// Carril 3..
		Vector2D vel3;
		vel3.x = -3.5f;
		vel3.y = 0.0f;
		Coche* aux3 = new Coche(1.45f, 15 + 6 * i, 3.5f, vel3, 20, 100, 100);

		// Carril 4..
		Vector2D vel4;
		vel4.x = 2.5f;
		vel4.y = 0.0f;
		Coche* aux4 = new Coche(1.3f, 0 - 6 * i, 4.5f, vel4, 255, 100, 0);

		// Rio 1..
		Vector2D vel_rio1;
		vel_rio1.x = 3.0f;
		vel_rio1.y = 0.0f;
		Tronco* aux_rio1 = new Tronco(0 - 6 * i, 6.5f, vel_rio1, 100, 50, 0);

		// Rio 2..
		Vector2D vel_rio2;
		vel_rio2.x = -3.5f;
		vel_rio2.y = 0.0f;
		Tronco* aux_rio2 = new Nenufar(15 + 6 * i, 7.5f, vel_rio2, 33, 198, 20,0.5);

		// Rio 3..
		Vector2D vel_rio3;
		vel_rio3.x = 2.5f;
		vel_rio3.y = 0.0f;
		Tronco* aux_rio3 = new Tronco(0 - 6 * i, 8.5f, vel_rio3, 150, 75, 0);

		coches.Agregar(aux1);
		coches.Agregar(aux2);
		coches.Agregar(aux3);
		coches.Agregar(aux4);

		troncos.Agregar(aux_rio1);
		troncos.Agregar(aux_rio2);
		troncos.Agregar(aux_rio3);

	}

		//Carril bici..
		Vector2D vel_bici;
		vel_bici.x = 1.5f;
		Coche* bicis = new Bicicleta(1, 0, 5.5, vel_bici, 20, 20, 100,0.4,0.7);//(0, vel_bici, 20, 20, 100);
		coches.Agregar(bicis);
}

void Mundo::TeclaEspecial(unsigned char k)
{
	switch (k)
	{
	case GLUT_KEY_LEFT:
	{
		if (atras == false && derecha == false && izquierda == false && recto == false)
		{
			izquierda = true;
			posicion_auxiliar = rana.mov_izq(rana.GetPos());
		}
	}
	break;
	case GLUT_KEY_RIGHT:
	{
		if (atras == false && derecha == false && izquierda == false && recto == false)
		{
			derecha = true;
			posicion_auxiliar = rana.mov_dch(rana.GetPos());
		}
	}
	break;
	case GLUT_KEY_UP:
	{
		if (y != false)
		{
			if (atras == false && derecha == false && izquierda == false && recto == false)
			{
				recto = true;
				posicion_auxiliar = rana.mov_rec(rana.GetPos());
			}
		}
	}
	break;
	case GLUT_KEY_DOWN:
	{
		if (atras == false && derecha == false && izquierda == false && recto == false)
		{
			atras = true;
			posicion_auxiliar = rana.mov_atr(rana.GetPos());
		}
	}
	break;
	}
}

Mundo::Mundo()
{
}

void Mundo::SetPos_ojo(Mundo* mundo)
{
	mundo->x_ojo = rana.GetPos().x;
	mundo->y_ojo = rana.GetPos().y-rana.GetAltura()-5;
	mundo->z_ojo = rana.z+rana.GetAltura()/2+4;
	mundo->x_vista = rana.GetPos().x;
	mundo->y_vista = 10;
}

void Mundo::Tecla(unsigned char key)
{
	switch (key)
	{
	case 'r':
	{
		camara = true;
	}
	break;
	case 'e':
	{
		camara = false;
		x_ojo = 7.5;
		y_ojo = 5;//-10;
		z_ojo = 15;
		x_vista = 7.5f;
		y_vista = 5.01f;//10.0f;
		z_vista = 0.0f;
	}
	break;
	}
}
