#ifndef __VECTOR2X2_H__
#define __VECTOR2X2_H__

#include "Vector2.h"

namespace tetris
{
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

		Vector2x2 operator* (const Vector2x2& a)
		{
			Vector2x2 r;
			r.v1 = v1*a.v1;
			r.v2 = v2*a.v2;
			return r;
		}

		float getWidth() const
		{
			return v2.x-v1.x;
		}

		float getHeight() const
		{
			return v2.y-v1.y;
		}
	};
}

#endif // __VECTOR2X2_H__