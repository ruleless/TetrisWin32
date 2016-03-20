#include "Renderable.h"

namespace tetris
{
	static ObjectPool<RenderableLine> s_lineObjPool("RederableLine");
	ObjectPool<RenderableLine>& RenderableLine::ObjPool()
	{
		return s_lineObjPool;
	}

	void RenderableLine::destroyObjPool()
	{
		s_lineObjPool.destroy();
	}

	void RenderableLine::release()
	{
		s_lineObjPool.reclaimObject(this);
	}


	static ObjectPool<RenderableRect> s_rectObjPool("RederableRect");
	ObjectPool<RenderableRect>& RenderableRect::ObjPool()
	{
		return s_rectObjPool;
	}

	void RenderableRect::destroyObjPool()
	{
		s_rectObjPool.destroy();
	}

	void RenderableRect::release()
	{
		s_rectObjPool.reclaimObject(this);
	}
}