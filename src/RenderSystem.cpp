#include "RenderSystem.h"

namespace tetris
{
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

	void RenderSystem::renderQueue(float delta, void *arg)
	{
		RenderQueue::iterator it = mRenderQueue.begin();
		for (; it != mRenderQueue.end(); ++it)
		{
			Renderable *pRenderable = *it;
			if (pRenderable)
			{
				_renderRenderable(pRenderable, arg);
				pRenderable->release();
			}
		}
		mRenderQueue.clear();
	}
}