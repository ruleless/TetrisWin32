#ifndef __GDIRENDERSYSTEM_H__
#define __GDIRENDERSYSTEM_H__

#include "common.h"
#include "RenderSystem.h"

namespace tetris
{
	class GdiRenderSystem : public RenderSystem
	{
	public:
		GdiRenderSystem(HWND hWnd, HINSTANCE inst);
		virtual ~GdiRenderSystem();

		virtual void renderOneFrame(float delta);
		virtual void _renderRenderable(Renderable *r, void *arg);

		virtual Vector2x2 getRenderArea() const;
	protected:
		struct SGdiRenderParam 
		{
			HDC hdcmem;
			HBITMAP bmpmem;
		};

		HWND mWnd;
		HINSTANCE mInst;
		RECT mRC;
	};
}

#endif // __GDIRENDERSYSTEM_H__