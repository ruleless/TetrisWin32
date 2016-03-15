#ifndef __GDIRENDERSYSTEM_H__
#define __GDIRENDERSYSTEM_H__

#include "RenderSystem.h"

class GdiRenderSystem : public RenderSystem
{
public:
	GdiRenderSystem();
	virtual ~GdiRenderSystem();

	virtual void _renderRenderable(Renderable *r);
protected:
};

#endif // __GDIRENDERSYSTEM_H__