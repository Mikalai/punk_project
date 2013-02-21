#ifndef _H_PUNK_OPENGL_PAINT_ENGINE
#define _H_PUNK_OPENGL_PAINT_ENGINE

#include "../../painter/paint_engine.h"

namespace GPU
{
	namespace OpenGL
	{
		class RenderTargetTexture;

		class OpenGLPaintEngine : public PaintEngine
		{
		public:
			OpenGLPaintEngine();
			virtual	~OpenGLPaintEngine();

			void SetRenderTarget(RenderTargetTexture* value);
			RenderTargetTexture* GetRenderTarget();

			virtual bool Begin(PaintDevice* device) override;
			virtual void DrawLines(const Math::Line2D* lines, size_t count) override;
			virtual void DrawRects(const Math::Rect* rects, size_t count) override;
			virtual void DrawArc(float xc, float yc, float width, float height, float start_angle, float span_angle) override;
			virtual void DrawChord(float xc, float yc, float width, float height, float start_angle, float span_angle) override;
			virtual void DrawPoint(float x, float y) override;
			virtual void DrawEllipse(float xc, float yc, float major_axis, float minor_axis) override;
			virtual void DrawRect(const Math::Rect& rect) override;
			virtual bool End() override;
			virtual void SetSurfaceSize(int width, int height) override;

			struct OpenGLPaintEngineImpl;
			OpenGLPaintEngineImpl* impl;

		private:
			OpenGLPaintEngine(const OpenGLPaintEngine&);
			OpenGLPaintEngine& operator = (const OpenGLPaintEngine&);
		};
	}
}

#endif	//	_H_PUNK_OPENGL_PAINT_ENGINE