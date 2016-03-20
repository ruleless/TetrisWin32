#include "GdiRenderSystem.h"
#include "Tetris.h"
#include "Vector2x2.h"

namespace tetris
{
	extern Tetris *gTetris;

	GdiRenderSystem::GdiRenderSystem(HWND hWnd, HINSTANCE inst)
		:RenderSystem()
		,mWnd(hWnd)
		,mInst(inst)
	{
	}

	GdiRenderSystem::~GdiRenderSystem()
	{
	}

	void GdiRenderSystem::renderOneFrame(float delta)
	{
		GetClientRect(mWnd, &mRC);

		HDC hdc = GetDC(mWnd);
		SGdiRenderParam renderParam;
		renderParam.hdcmem = CreateCompatibleDC(hdc);
		renderParam.bmpmem = CreateCompatibleBitmap(hdc, mRC.right-mRC.left, mRC.bottom-mRC.top);
		SelectObject(renderParam.hdcmem, renderParam.bmpmem);

		gTetris->render(this);
		renderQueue(delta, (void *)&renderParam);

		BitBlt(hdc, mRC.left, mRC.top, mRC.right-mRC.left, mRC.bottom-mRC.top, renderParam.hdcmem, 0, 0, SRCCOPY);
		ReleaseDC(mWnd, hdc);
		DeleteDC(renderParam.hdcmem);
		DeleteObject(renderParam.bmpmem);
		ValidateRect(mWnd,&mRC);
	}

	void GdiRenderSystem::_renderRenderable(Renderable *r, void *arg)
	{
		SGdiRenderParam *param = (SGdiRenderParam *)arg;
		switch (r->getRenderType())
		{
		case RenderType_Line:
			{
				SRgb color = r->getRGB();
				HPEN hPen=CreatePen(PS_SOLID, 1, RGB(color.r, color.g, color.b));
				DeleteObject(SelectObject(param->hdcmem, hPen));

				RECT line;
				Vector2x2 *data = (Vector2x2 *)r->getRenderData();
				line.left = data->v1.x;
				line.top = data->v1.y;
				line.right = data->v2.x;
				line.bottom = data->v2.y;
				MoveToEx(param->hdcmem, line.left,line.top,NULL);
				LineTo(param->hdcmem, line.right, line.bottom);

				DeleteObject(hPen);
			}
			break;
		case RenderType_Rect:
			{
				SRgb color = r->getRGB();
				HBRUSH hBrush = CreateSolidBrush(RGB(color.r, color.g, color.b));
				DeleteObject(SelectObject(param->hdcmem, hBrush));

				RECT rect;
				Vector2x2 *data = (Vector2x2 *)r->getRenderData();
				rect.left = data->v1.x;
				rect.top = data->v1.y;
				rect.right = data->v2.x;
				rect.bottom = data->v2.y;
				Rectangle(param->hdcmem, rect.left, rect.top, rect.right, rect.bottom);

				DeleteObject(hBrush);
			}
			break;
		default:
			break;
		}
	}

	Vector2x2 GdiRenderSystem::getRenderArea() const
	{
		Vector2x2 r;
		r.v1.x = mRC.left;
		r.v1.y = mRC.top;
		r.v2.x = mRC.right;
		r.v2.y = mRC.bottom;
		return r;
	}
}