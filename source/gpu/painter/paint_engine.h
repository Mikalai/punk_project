#ifndef _H_PUNK_PAINT_ENGINE
#define _H_PUNK_PAINT_ENGINE

#include "../../config.h"

namespace Math 
{ 
	class Line2D;
	class vec2;
	class Rect;
}

namespace GPU
{
	class PaintDevice;
	class Painter;

	/**
	*	This is an interface for Painter. This should be reimplemented
	*	using OpenGL or other low level api
	*	Paint engine performs its rendering into PaintDevice
	*/
	class PUNK_ENGINE PaintEngine abstract
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