#ifndef _H_PUNK_GPU_PAINTER
#define _H_PUNK_GPU_PAINTER

#include "../../config.h"

namespace Math
{
	class Line2D;
	class Triangle2D;
	class vec2;
	class ivec2;	
}

namespace GPU
{
	class RenderTarget;
	class Brush;
	
	class PUNK_ENGINE Painter
	{
	public:
		Painter();
		~Painter();
		void Begin(RenderTarget* target = nullptr);
		void End();
		void DrawPoint(const Math::vec2& point);
		void DrawLine(const Math::vec2& a, const Math::vec2& b);
		void DrawLine(const Math::Line2D& line);
		void SetBrush(const Brush& value);
		const Brush& GetBrush();

		struct PainterImpl;
		PainterImpl* impl;
	};
}

#endif	//	_H_PUNK_GPU_PAINTER