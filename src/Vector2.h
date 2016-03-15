#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#include "Matrix4.h"

class Vector2
{
public:
	float x, y;

	Vector2() : x(0), y(0)
	{
	}

	Vector2(float a, float b) : x(a), y(b)
	{
	}
	
	Vector2(const Vector2 &v)
	{
		x = v.x;
		y = v.y;
	}

	Vector2& operator= (const Vector2 &v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	Vector2 operator+ (const Vector2 &v)
	{
		Vector2 rc;
		rc.x = x+v.x;
		rc.y = y+v.y;
		return rc;
	}

	Vector2& operator+= (const Vector2 &v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	float operator* (const Vector2 &v)
	{
		return x*v.x + y*v.y;
	}

	Vector2 operator* (const Matrix4 &m)
	{
		Vector2 res;
		res.x = x*m._11 + y*m._21;
		res.y = x*m._12 + y*m._22;
		return res;
	}
};

#endif // __VECTOR2_H__