#ifndef _H_PUNK_PAINT_ENGINE
#define _H_PUNK_PAINT_ENGINE

#include <cstddef>
#include "../../config.h"

namespace Math
{
	class Line2D;
	class vec2;
	class Rect;
	class vec4;
}

namespace System { class string; }

namespace GPU
{
	class PaintDevice;
	class Painter;
	class Texture2D;

	/**
	*	This is an interface for Painter. This should be reimplemented
	*	using OpenGL or other low level api
	*	Paint engine performs its rendering into PaintDevice
	*/
	class PUNK_ENGINE_PUBLIC PaintEngine
	{
	public:

        PaintEngine();
		virtual ~PaintEngine();

		virtual bool Begin(PaintDevice* device) = 0;
		virtual void DrawLines(const Math::Line2D* lines, size_t count) = 0;
		virtual void DrawRects(const Math::Rect* rects, size_t count) = 0;
		virtual void DrawArc(float xc, float yc, float width, float height, float start_angle, float span_angle) = 0;
		virtual void DrawChord(float xc, float yc, float width, float height, float start_angle, float span_angle) = 0;
		virtual void DrawPoint(float x, float y) = 0;
		virtual void DrawEllipse(float xc, float yc, float major_axis, float minor_axis) = 0;
		virtual void DrawRect(const Math::Rect& rect) = 0;
		virtual void SetColor(const Math::vec4& value) = 0;
		virtual void SetColor(float r, float g, float b, float a) = 0;
		virtual void SetFillColor(const Math::vec4& value) = 0;
		virtual void SetFillColor(float r, float g, float b, float a) = 0;
		virtual void SetFillTexture(const Texture2D* value) = 0;
		virtual void SetLineWidth(float value) = 0;
		virtual void SetPointSize(float value) = 0;
		virtual void DrawString(float x, float y, const System::string& text) = 0;
		virtual void SetFontName(const System::string& font) = 0;
		virtual void SetFontSize(int size) = 0;
		virtual void EnableFill(bool value) = 0;
		virtual void EnableBorder(bool value) = 0;
		virtual bool End() = 0;
		virtual void SetSurfaceSize(int width, int height) = 0;

		PaintDevice* GetPaintDevice() const;
		Painter* GetPainter() const;

	protected:
		void SetPaintDevice(PaintDevice* value);
		void SetPainter(Painter* value);

	private:
		//	this should not be delete
		PaintDevice* m_device;
		Painter* m_painter;

		//	no copy
		PaintEngine(const PaintEngine&);
		PaintEngine& operator = (const PaintEngine&);

		friend class Painter;
	};

	inline void PaintEngine::SetPaintDevice(PaintDevice* value)
	{
		m_device = value;
	}

	inline void PaintEngine::SetPainter(Painter* value)
	{
		m_painter = value;
	}

	inline PaintDevice* PaintEngine::GetPaintDevice() const
	{
		return m_device;
	}

	inline Painter* PaintEngine::GetPainter() const
	{
		return m_painter;
	}
}

#endif	//	_H_PUNK_PAINT_ENGINE
