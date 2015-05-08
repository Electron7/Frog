#ifndef _VECTOR2D_H
#define _VECTOR2D_H

#include <math.h>
#include "../../lib/glut.h"

class Vector2D
{
public:
	Vector2D(float xv = 0.0f, float yv = 0.0f);
	virtual ~Vector2D();
	float x;
	float y;
	float z;
	Vector2D operator+(Vector2D &);
	Vector2D operator-(Vector2D &);
	Vector2D operator*(float);
	float operator*(Vector2D &);
	float modulo();
	float argumento();
	Vector2D unitario();
};

#endif
