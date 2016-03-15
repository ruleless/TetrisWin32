#ifndef __VECTOR2X2_H__
#define __VECTOR2X2_H__

#include "Vector2.h"

class Vector2x2
{
public:
	Vector2 v1, v2;

	Vector2x2() : v1(), v2()
	{
	}

	Vector2x2(const Vector2 &a, const Vector2 &b)
		:v1(a), v2(b)
	{
	}
};

#endif // __VECTOR2X2_H__