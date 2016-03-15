#ifndef __RENDERSYSTEM_H__
#define __RENDERSYSTEM_H__

#include <vector>
#include "ObjectPool.h"

enum ERenderType
{
	RenderType_Line,
	RenderType_Rect,
};

class Renderable : public PoolObject
{
public:
	virtual ~Renderable() {};

	virtual void release() = 0;

	virtual ERenderType getRenderType() const = 0;
	virtual void* getRenderData() const = 0;
};

class RenderSystem
{
public:
	RenderSystem();
	virtual ~RenderSystem();

	void addRenderable(Renderable *r);

	void _render();
	virtual void _renderRenderable(Renderable *r) = 0;
protected:
	typedef std::vector<Renderable *> RenderQueue;
	RenderQueue mRenderQueue;
};

#endif // __RENDERSYSTEM_H__