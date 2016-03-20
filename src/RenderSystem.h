#ifndef __RENDERSYSTEM_H__
#define __RENDERSYSTEM_H__

#include <vector>
#include "ObjectPool.h"
#include "Vector2x2.h"
#include "Colour.h"

namespace tetris
{
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
		virtual SRgb getRGB() const = 0;
		virtual void* getRenderData() const = 0;
	};

	class RenderSystem
	{
	public:
		RenderSystem();
		virtual ~RenderSystem();

		void addRenderable(Renderable *r);

		virtual void renderOneFrame(float delta) = 0;
		void renderQueue(float delta, void *arg);
		virtual void _renderRenderable(Renderable *r, void *arg) = 0;

		virtual Vector2x2 getRenderArea() const = 0;
	protected:
		typedef std::vector<Renderable *> RenderQueue;
		RenderQueue mRenderQueue;
	};
}

#endif // __RENDERSYSTEM_H__