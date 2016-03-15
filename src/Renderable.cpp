#include "Renderable.h"

static ObjectPool<RederableLine> s_lineObjPool("RederableLine");
ObjectPool<RederableLine>& RederableLine::ObjPool()
{
	return s_lineObjPool;
}

void RederableLine::destroyObjPool()
{
	s_lineObjPool.destroy();
}


static ObjectPool<RederableRect> s_rectObjPool("RederableRect");
ObjectPool<RederableRect>& RederableRect::ObjPool()
{
	return s_rectObjPool;
}

void RederableRect::destroyObjPool()
{
	s_rectObjPool.destroy();
}