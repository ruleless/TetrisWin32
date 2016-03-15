#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Vector2.h"
#include "Matrix4.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	void translate(const Vector2 &v);
	void rotate(const Matrix4 &r);
protected:
	Vector2 mPostion;
	Matrix4 mRotation;
};

#endif // __ENTITY_H__