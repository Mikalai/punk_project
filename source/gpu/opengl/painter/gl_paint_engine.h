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
			virtual void SetColor(const Math::vec4& value) override;
			virtual void SetColor(float r, float g, float b, float a) override;
			virtual void SetFillColor(const Math::vec4& value) override;
			virtual void SetFillColor(float r, float g, float b, float a) override;
			virtual void SetFillTexture(const OpenGL::Texture2D* value) override;
			virtual void SetLineWidth(float value) override;
			virtual void SetPointSize(float value) override;
			virtual void DrawString(float x, float y, const System::string& text);
			virtual void SetFontName(const System::string& font) override;
			virtual void SetFontSize(int size) override;
			virtual void EnableFill(bool value) override;
			virtual void EnableBorder(bool value) override;
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