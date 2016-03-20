#ifndef __NODE_H__
#define __NODE_H__

#include "Vector2.h"
#include "Matrix4.h"

namespace tetris
{
	class Node
	{
	public:
		Node();
		Node(const Node &obj);
		virtual ~Node();

		Node& operator= (const Node &obj);

		void translate(const Vector2 &v);
		void rotate(const Matrix4 &r);
	protected:
		friend class Entity;

		Vector2 mPostion;
		Matrix4 mRotation;
	};
}

#endif // __NODE_H__