#include "Entity.h"
#include "Tetris.h"

namespace tetris
{
	//////////////////////////////////////////////////////////////////////////
	extern Tetris *gTetris;
	Entity::Entity()
		:mVertexCount(0)
		,mState(State_Alive)
	{
	}

	Entity::~Entity()
	{
	}

	Entity* Entity::clone()
	{
		Entity *pNewObj = _newObject();
		pNewObj->mParentNode = mParentNode;
		pNewObj->mVertexCount = mVertexCount;
		for (int i = 0; i < mVertexCount; ++i)
		{
			pNewObj->mVertex[i] = mVertex[i];
		}
		pNewObj->mState = mState;
		return pNewObj;
	}

	Node* Entity::getParentNode()
	{
		return &mParentNode;
	}

	int Entity::getAllVertex(Vector2 *verts, int &vertcount) const
	{
		Vector2 fixV;
		vertcount = min(vertcount, mVertexCount);
		for (int i = 0; i < vertcount; ++i)
		{
			verts[i] = mVertex[i]*mParentNode.mRotation + mParentNode.mPostion;
			fixV.x = max(verts[i].x - floorf(verts[i].x), fixV.x);
			fixV.y = max(verts[i].y - floorf(verts[i].y), fixV.y);
		}
		for (int i = 0; i < vertcount; ++i)
		{
			verts[i] += fixV;
			TetrisAssert(fabs(verts[i].x - (int)verts[i].x) < eps);
			TetrisAssert(fabs(verts[i].y - (int)verts[i].y) < eps);
		}

		return vertcount;
	}

	bool Entity::translate(const Vector2 &v)
	{
		Vector2 fixV;
		Vector2 verts[MaxVertexCount];
		for (int i = 0; i < mVertexCount; ++i)
		{
			verts[i] = mVertex[i]*mParentNode.mRotation + (mParentNode.mPostion+v);
			fixV.x = max(verts[i].x - floorf(verts[i].x), fixV.x);
			fixV.y = max(verts[i].y - floorf(verts[i].y), fixV.y);
		}
		for (int i = 0; i < mVertexCount; ++i)
		{
			verts[i] += fixV;
			TetrisAssert(fabs(verts[i].x - (int)verts[i].x) < eps);
			TetrisAssert(fabs(verts[i].y - (int)verts[i].y) < eps);
			if (gTetris->collision((int)verts[i].x, (int)verts[i].y))
			{
				return false;
			}
		}
		mParentNode.translate(v);
		return true;
	}

	bool Entity::rotate(const Matrix4 &r)
	{
		Vector2 fixV;
		Vector2 verts[MaxVertexCount];
		for (int i = 0; i < mVertexCount; ++i)
		{
			verts[i] = mVertex[i]*mParentNode.mRotation*r + mParentNode.mPostion;
			fixV.x = max(verts[i].x - floorf(verts[i].x), fixV.x);
			fixV.y = max(verts[i].y - floorf(verts[i].y), fixV.y);
		}
		for (int i = 0; i < mVertexCount; ++i)
		{
			verts[i] += fixV;
			TetrisAssert(fabs(verts[i].x - (int)verts[i].x) < eps);
			TetrisAssert(fabs(verts[i].y - (int)verts[i].y) < eps);
			if (gTetris->collision((int)verts[i].x, (int)verts[i].y))
			{
				return false;
			}
		}
		mParentNode.rotate(r);
		return true;
	}

	bool Entity::collision() const
	{
		Vector2 verts[MaxVertexCount];
		int vertcount = mVertexCount;
		getAllVertex(verts, vertcount);
		for (int i = 0; i < vertcount; ++i)
		{
			if (gTetris->collision((int)verts[i].x, (int)verts[i].y))
			{
				return true;
			}
		}

		return false;
	}
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	static ObjectPool<Entity_1> s_objPoolEntity1("Entity_1");
	template<> ObjectPool<Entity_1> *Entity_T<Entity_1>::mEntity = &s_objPoolEntity1;

	Entity_1::Entity_1() : Entity_T<Entity_1>()
	{
		mVertexCount = 4;
		mVertex[0].x = -1.5; mVertex[0].y = 0;		
		mVertex[1].x = -0.5; mVertex[1].y = 0;		
		mVertex[2].x =  0.5; mVertex[2].y = 0;
		mVertex[3].x =  1.5; mVertex[3].y = 0;
		mParentNode.translate(Vector2(1.5, 0));
	}

	static ObjectPool<Entity_2> s_objPoolEntity2("Entity_2");
	template<> ObjectPool<Entity_2> *Entity_T<Entity_2>::mEntity = &s_objPoolEntity2;

	Entity_2::Entity_2() : Entity_T<Entity_2>()
	{
		mVertexCount = 4;
		mVertex[0].x = -0.5; mVertex[0].y = -1;
		mVertex[1].x = -0.5; mVertex[1].y = 0;		
		mVertex[2].x =  0.5; mVertex[2].y = 0;
		mVertex[3].x =  0.5; mVertex[3].y = 1;
		mParentNode.translate(Vector2(0.5, 0));
	}

	static ObjectPool<Entity_3> s_objPoolEntity3("Entity_3");
	template<> ObjectPool<Entity_3> *Entity_T<Entity_3>::mEntity = &s_objPoolEntity3;

	Entity_3::Entity_3() : Entity_T<Entity_3>()
	{
		mVertexCount = 4;
		mVertex[0].x = -0.5; mVertex[0].y = -1;
		mVertex[1].x = -0.5; mVertex[1].y = 0;		
		mVertex[2].x =  0.5; mVertex[2].y = 0;
		mVertex[3].x =  0.5; mVertex[3].y = 1;
		mParentNode.translate(Vector2(0.5, 0));
	}

	static ObjectPool<Entity_4> s_objPoolEntity4("Entity_4");
	template<> ObjectPool<Entity_4> *Entity_T<Entity_4>::mEntity = &s_objPoolEntity4;

	Entity_4::Entity_4() : Entity_T<Entity_4>()
	{
		mVertexCount = 4;
		mVertex[0].x = -0.5; mVertex[0].y = -0.5;
		mVertex[1].x = -0.5; mVertex[1].y = 0.5;		
		mVertex[2].x =  0.5; mVertex[2].y = 0.5;
		mVertex[3].x =  0.5; mVertex[3].y = -0.5;
		mParentNode.translate(Vector2(0.5, 0));
	}

	static ObjectPool<Entity_5> s_objPoolEntity5("Entity_5");
	template<> ObjectPool<Entity_5> *Entity_T<Entity_5>::mEntity = &s_objPoolEntity5;

	Entity_5::Entity_5() : Entity_T<Entity_5>()
	{
		mVertexCount = 4;
		mVertex[0].x = -0.5; mVertex[0].y =  1.5;
		mVertex[1].x = -0.5; mVertex[1].y =  0.5;		
		mVertex[2].x = -0.5; mVertex[2].y = -0.5;
		mVertex[3].x =  0.5; mVertex[3].y = -0.5;
		mParentNode.translate(Vector2(0.5, 0));
	}

	static ObjectPool<Entity_6> s_objPoolEntity6("Entity_6");
	template<> ObjectPool<Entity_6> *Entity_T<Entity_6>::mEntity = &s_objPoolEntity6;

	Entity_6::Entity_6() : Entity_T<Entity_6>()
	{
		mVertexCount = 4;
		mVertex[0].x =  0.5; mVertex[0].y =  1.5;
		mVertex[1].x =  0.5; mVertex[1].y =  0.5;		
		mVertex[2].x =  0.5; mVertex[2].y = -0.5;
		mVertex[3].x = -0.5; mVertex[3].y = -0.5;
		mParentNode.translate(Vector2(0.5, 0));
	}

	static ObjectPool<Entity_7> s_objPoolEntity7("Entity_7");
	template<> ObjectPool<Entity_7> *Entity_T<Entity_7>::mEntity = &s_objPoolEntity7;

	Entity_7::Entity_7() : Entity_T<Entity_7>()
	{
		mVertexCount = 4;
		mVertex[0].x =  0; mVertex[0].y =  0.5;
		mVertex[1].x = -1; mVertex[1].y = -0.5;
		mVertex[2].x =  0; mVertex[2].y = -0.5;
		mVertex[3].x =  1; mVertex[3].y = -0.5;
		mParentNode.translate(Vector2(1, 0.5));
	}

	static ObjectPool<Entity_8> s_objPoolEntity8("Entity_8");
	template<> ObjectPool<Entity_8> *Entity_T<Entity_8>::mEntity = &s_objPoolEntity8;

	Entity_8::Entity_8() : Entity_T<Entity_8>()
	{
		mVertexCount = 5;
		mVertex[0].x =  0; mVertex[0].y =  0.5;
		mVertex[1].x =  0; mVertex[1].y =  1.5;
		mVertex[2].x = -1; mVertex[2].y = -0.5;
		mVertex[3].x =  0; mVertex[3].y = -0.5;
		mVertex[4].x =  1; mVertex[4].y = -0.5;
		mParentNode.translate(Vector2(1, 0.5));
	}
	//////////////////////////////////////////////////////////////////////////
}