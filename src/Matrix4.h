#ifndef __MATRIX4_H__
#define __MATRIX4_H__

#include <stdio.h>
#include <string.h>

class Matrix4
{
public:
	union
	{
		float _a[2][2];
		struct  
		{
			float _11, _12;
			float _21, _22;
		};
	};

	static const Matrix4 Zero;
	static const Matrix4 I;

	Matrix4() : _11(0), _12(0), _21(0), _22(0)
	{
	}

	Matrix4(float aa, float ab, float ba, float bb) : _11(aa), _12(ab), _21(ba), _22(bb)
	{
	}

	Matrix4(const Matrix4 &m) : _11(m._11), _12(m._12), _21(m._21), _22(m._22)
	{
	}

	Matrix4& operator=(const Matrix4 &m)
	{
		memcpy(_a, m._a, sizeof(_a));
		return *this;
	}

	Matrix4 operator* (const Matrix4 &m)
	{
		Matrix4 res;
		res._11 = _11*m._11 + _12*m._21;
		res._12 = _11*m._12 + _12*m._22;
		res._21 = _21*m._11 + _22*m._21;
		res._22 = _21*m._12 + _22*m._22;
		return res;
	}
};

extern const Matrix4& getMatForRot90();
extern const Matrix4& getMatForRot180();
extern const Matrix4& getMatForRot270();

#endif // __MATRIX4_H__