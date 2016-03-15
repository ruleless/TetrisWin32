#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

#include "RenderSystem.h"
#include "Vector2x2.h"

class RenderableTetris : public Renderable
{
public:
	RenderableTetris() : mShape()
	{
	}

	virtual ~RenderableTetris() {}

	virtual void* getRenderData() const
	{
		return (void *)&mShape;
	}

	void setShape(const Vector2 &v1, const Vector2 &v2)
	{
		mShape.v1 = v1;
		mShape.v2 = v2;
	}
protected:
	Vector2x2 mShape;
};

class RederableLine : public RenderableTetris
{
public:
	static ObjectPool<RederableLine>& ObjPool();
	static void destroyObjPool();

	virtual void onReclaimObject() {}

	virtual ERenderType getRenderType() const
	{
		return RenderType_Line;
	}
};

class RederableRect : public RenderableTetris
{
public:
	static ObjectPool<RederableRect>& ObjPool();
	static void destroyObjPool();

	virtual void onReclaimObject() {}
	virtual void release();

	virtual ERenderType getRenderType() const
	{
		return RenderType_Rect;
	}
};

#endif // __RENDERABLE_H__