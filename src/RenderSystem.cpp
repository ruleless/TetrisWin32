#include "RenderSystem.h"

RenderSystem::RenderSystem()
:mRenderQueue()
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::addRenderable(Renderable *r)
{
	mRenderQueue.push_back(r);
}

void RenderSystem::_render()
{
	RenderQueue::iterator it = mRenderQueue.begin();
	for (; it != mRenderQueue.end(); ++it)
	{
		Renderable *pRenderable = *it;
		if (pRenderable)
		{
			_renderRenderable(pRenderable);
			pRenderable->release();
		}
	}
	mRenderQueue.clear();
}