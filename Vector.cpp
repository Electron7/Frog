#include "Vector2D.h"

Vector2D:: ~Vector2D()
{

}

Vector2D::Vector2D(float xv, float yv)
{
	x = xv;
	y = yv;
}

Vector2D Vector2D::operator+(Vector2D &op)
{
	Vector2D resultado;
	resultado.x = x + op.x;
	resultado.y = y + op.y;
	return resultado;
}

Vector2D Vector2D::operator-(Vector2D &op)
{
	Vector2D resultado;
	resultado.x = x - op.x;
	resultado.y = y - op.y;
	return resultado;
}

Vector2D Vector2D::operator*(float ix)
{
	Vector2D resultado;
	resultado.x = x * ix;
	resultado.y = y * ix;
	return resultado;
}

float Vector2D::operator*(Vector2D &op)
{
	float resultado;
	Vector2D operador;
	float alpha = (operador.x*op.x + operador.y*operador.x) / (sqrt(operador.x*operador.x + operador.y*operador.y)*sqrt(op.x*op.x + op.y*op.y));
	resultado = operador.modulo()*op.modulo()*alpha;
	return resultado;
}

float Vector2D::modulo()
{
	return (float)sqrt(x*x + y*y);
}

float Vector2D::argumento()
{
	return (float)atan2(y,x);
}

Vector2D Vector2D::unitario()
{
	Vector2D retorno(x, y);
	float mod = modulo();
	if (mod > 0.00001)
	{
		retorno.x /= mod;
		retorno.y /= mod;
	}
	return retorno;
}

