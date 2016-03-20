#include "Node.h"

namespace tetris
{
	Node::Node()
		:mPostion()
		,mRotation(Matrix4::I)
	{
	}

	Node::Node(const Node &obj)
		:mRotation(obj.mRotation)
		,mPostion(obj.mPostion)
	{
	}

	Node::~Node()
	{
	}

	Node& Node::operator= (const Node &obj)
	{
		mRotation = obj.mRotation;
		mPostion = obj.mPostion;
		return *this;
	}

	void Node::translate(const Vector2 &v)
	{
		mPostion += v;
	}

	void Node::rotate(const Matrix4 &r)
	{
		mRotation = mRotation*r;
	}
}