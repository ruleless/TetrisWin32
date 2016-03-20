#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "common.h"
#include "ObjectPool.h"
#include "Vector2.h"
#include "Matrix4.h"
#include "Node.h"
#include "TetrisDef.h"

namespace tetris
{
	//////////////////////////////////////////////////////////////////////////	
	class Entity : public PoolObject
	{
	public:
		enum State
		{
			State_Alive,
			State_Dead,
		};

		Entity();
		virtual ~Entity();

		Entity* clone();
		virtual Entity* _newObject() = 0;
		virtual void release() = 0;;

		Node* getParentNode();
		int getAllVertex(Vector2 *verts, int &vertcount) const;

		bool translate(const Vector2 &v);
		bool rotate(const Matrix4 &r);

		bool collision() const;

		inline State state() const
		{
			return mState;
		}
		inline void state(State s)
		{
			mState = s;
		}
	protected:
		Node mParentNode;
		Vector2 mVertex[MaxVertexCount];
		int mVertexCount;
		State mState;
	};
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	template <class T>
	class Entity_T : public Entity
	{
	public:
		static ObjectPool<T>& ObjPool()
		{
			return *mEntity;
		}
		static void destroyObjPool()
		{
			mEntity->destroy();
		}

		virtual void onReclaimObject() {}
		virtual Entity* _newObject()
		{
			return mEntity->createObject();
		}
		virtual void release()
		{
			return mEntity->reclaimObject((T *)this);
		}

		Entity_T() : Entity() {}
	protected:
		static ObjectPool<T> *mEntity;
	};
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	class Entity_1 : public Entity_T<Entity_1>
	{
	public:
		Entity_1();
	};

	class Entity_2 : public Entity_T<Entity_2>
	{
	public:
		Entity_2();
	};

	class Entity_3 : public Entity_T<Entity_3>
	{
	public:
		Entity_3();
	};

	class Entity_4 : public Entity_T<Entity_4>
	{
	public:
		Entity_4();
	};

	class Entity_5 : public Entity_T<Entity_5>
	{
	public:
		Entity_5();
	};

	class Entity_6 : public Entity_T<Entity_6>
	{
	public:
		Entity_6();
	};

	class Entity_7 : public Entity_T<Entity_7>
	{
	public:
		Entity_7();
	};

	class Entity_8 : public Entity_T<Entity_8>
	{
	public:
		Entity_8();
	};
	//////////////////////////////////////////////////////////////////////////
}

#endif // __ENTITY_H__