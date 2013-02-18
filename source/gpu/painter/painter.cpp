#include "painter.h"
#include "../opengl/painter/gl_painter.h"

namespace GPU
{
	Painter::Painter()
	{
		impl = new PainterImpl();
	}

	Painter::~Painter()
	{
		delete impl;
	}

	void Painter::Begin(RenderTarget* value)
	{
		impl->Begin(value);
	}

	void Painter::End()
	{
		impl->End();
	}

	void Painter::DrawLine(const Math::vec2& a, const Math::vec2& b)
	{
		impl->DrawLine(a, b);
	}

	void Painter::DrawLine(const Math::Line2D& line)
	{
		impl->DrawLine(line);
	}

	void Painter::DrawPoint(const Math::vec2& point)
	{
		impl->DrawPoint(point);
	}
}