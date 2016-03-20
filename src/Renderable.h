#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

#include "RenderSystem.h"
#include "Vector2x2.h"
#include "Colour.h"

namespace tetris
{
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

		virtual SRgb getRGB() const
		{
			return mColor;
		}

		void setShape(const Vector2 &v1, const Vector2 &v2)
		{
			mShape.v1 = v1;
			mShape.v2 = v2;
		}

		void setShape(const Vector2x2 &s)
		{
			mShape = s;
		}


		void setRGB(const SRgb &c)
		{
			mColor = c;
		}
	protected:
		Vector2x2 mShape;
		SRgb mColor;
	};

	class RenderableLine : public RenderableTetris
	{
	public:
		static ObjectPool<RenderableLine>& ObjPool();
		static void destroyObjPool();

		virtual void onReclaimObject() {}
		virtual void release();

		virtual ERenderType getRenderType() const
		{
			return RenderType_Line;
		}
	};

	class RenderableRect : public RenderableTetris
	{
	public:
		static ObjectPool<RenderableRect>& ObjPool();
		static void destroyObjPool();

		virtual void onReclaimObject() {}
		virtual void release();

		virtual ERenderType getRenderType() const
		{
			return RenderType_Rect;
		}
	};
}

#endif // __RENDERABLE_H__