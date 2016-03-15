#include "GdiRenderSystem.h"

GdiRenderSystem::GdiRenderSystem()
{
}

GdiRenderSystem::~GdiRenderSystem()
{
}

void GdiRenderSystem::_renderRenderable(Renderable *r)
{
	switch (r->getRenderType())
	{
	case RenderType_Line:
		break;
	case RenderType_Rect:
		break;
	default:
		break;
	}
}