#include "painter.h"
#include "brush.h"
#include "pen.h"
#include "../../math/mat3.h"

namespace Gpu
{
	struct Painter::PainterImpl
	{
		void Begin(PaintDevice* device = nullptr)
		{
            (void)device;
		}

		void End()
		{
		}

		void DrawArc(float xc, float yc, float width, float height, float start_angle, float span_angle)
		{
            (void)xc; (void)yc; (void)width; (void)height; (void)start_angle; (void)span_angle;
		}

		void DrawChord(float xc, float yc, float width, float height, float start_angle, float span_angle)
		{
            (void)xc; (void)yc; (void)width; (void)height; (void)start_angle; (void)span_angle;
		}

		void DrawConvexPolygon(const Math::vec2* points, size_t count)
		{
            (void)points; (void)count;
		}

		void DrawConvexPolygon(const std::vector<Math::vec2>& points)
		{
            (void)points;
		}

		void DrawPoint(const Math::vec2& point)
		{
            (void)point;
		}

		void DrawPoint(float x, float y)
		{
            (void)x; (void)y;
		}

		void DrawLine(const Math::vec2& a, const Math::vec2& b)
		{
            (void)a; (void)b;
		}

		void DrawLine(const Math::Line2D& line)
		{
            (void)line;
		}

		void DrawLine(float x1, float y1, float x2, float y2)
		{
            (void)x1; (void)y1; (void)x2; (void)y2;
		}

		void DrawLines(const Math::Line2D* lines, size_t count)
		{
            (void)lines; (void)count;
		}

		void DrawLines(const std::vector<Math::Line2D>& lines)
		{
            (void)lines;
		}

		void DrawEllipse(float xc, float yc, float major_axis, float minor_axis)
		{
            (void)xc; (void)yc; (void)major_axis; (void)minor_axis;
		}

		void DrawEllipse(const Math::Rect& rect)
		{
            (void)rect;
		}

		void DrawImage(float x, float y, const ImageModule::Image& image)
		{
            (void)x; (void)y; (void)image;
		}

		void DrawImage(const Math::vec2& point, const ImageModule::Image& image)
		{
            (void)point; (void)image;
		}        

		void DrawRect(const Math::Rect& rect)
		{
            (void)rect;
		}

		void DrawRect(float x, float y, float width, float height)
		{
            (void)x; (void)y; (void)width; (void)height;
		}

		void DrawRoundedRect(float x, float y, float x_r, float y_r)
		{
            (void)x; (void)y; (void)x_r; (void)y_r;
		}

		void DrawText(float x, float y, const System::string& text)
		{
            (void)x; (void)y; (void)text;
		}

		void EraseRect(const Math::Rect& rect)
		{
            (void)rect;
		}

		void FillRect(const Math::Rect& rect, const Brush& brush)
		{
            (void)rect; (void)brush;
		}

		void SetOpacity(float value)
		{
            (void)value;
		}

		float GetOpacity() const
		{
			return 0;
		}

		void SetPen(const Pen& pen)
		{
            (void)pen;
		}

		const Pen& GetPen() const
		{
            throw;
		}

		PaintEngine* GetPaintEngine() const
		{
			return 0;
		}

		void Save()
		{
		}

		void Restore()
		{
		}

		void Scale(float x, float y)
		{
            (void)x; (void)y;
		}

		void Translate(float x, float y)
		{
            (void)x; (void)y;
		}

		void SetWorldTransform(const Math::mat3& value)
		{
            (void)value;
		}

		const Math::mat3& GetWorldTransform() const
		{
            throw;
		}

		void SetBackgroundBrush(const Brush& value)
		{
            (void)value;
		}
		
		const Brush& GetBackgroundBrush() const
		{
            throw;
		}

		void SetBrush(const Brush& value)
		{
            (void)value;
		}

		const Brush& GetBrush() const
		{
            throw;
		}
	};

	Painter::Painter()
		: impl(new Painter::PainterImpl)
	{}

	Painter::~Painter()
	{
		delete impl;
        impl = 0;
	}

	void Painter::Begin(PaintDevice* device)
	{
		impl->Begin(device);
	}

	void Painter::End()
	{
		impl->End();
	}

	void Painter::DrawArc(float xc, float yc, float width, float height, float start_angle, float span_angle)
	{
		impl->DrawArc(xc, yc, width, height, start_angle, span_angle);
	}

	void Painter::DrawChord(float xc, float yc, float width, float height, float start_angle, float span_angle)
	{
		impl->DrawChord(xc, yc, width, height, start_angle, span_angle);
	}

	void Painter::DrawConvexPolygon(const Math::vec2* points, size_t count)
	{
		impl->DrawConvexPolygon(points, count);
	}

	void Painter::DrawConvexPolygon(const std::vector<Math::vec2>& points)
	{
		impl->DrawConvexPolygon(points);
	}

	void Painter::DrawPoint(const Math::vec2& point)
	{
		impl->DrawPoint(point);
	}

	void Painter::DrawPoint(float x, float y)
	{
		impl->DrawPoint(x, y);
	}

	void Painter::DrawLine(const Math::vec2& a, const Math::vec2& b)
	{
		impl->DrawLine(a, b);
	}

	void Painter::DrawLine(const Math::Line2D& line)
	{
		impl->DrawLine(line);
	}

	void Painter::DrawLine(float x1, float y1, float x2, float y2)
	{
		impl->DrawLine(x1, y1, x2, y2);
	}

	void Painter::DrawLines(const Math::Line2D* lines, size_t count)
	{
		impl->DrawLines(lines, count);
	}

	void Painter::DrawLines(const std::vector<Math::Line2D>& lines)
	{
		impl->DrawLines(lines);
	}

	void Painter::DrawEllipse(float xc, float yc, float major_axis, float minor_axis)
	{
		impl->DrawEllipse(xc, yc, major_axis, minor_axis);
	}

	void Painter::DrawEllipse(const Math::Rect& rect)
	{
		impl->DrawRect(rect);
	}

	void Painter::DrawImage(float x, float y, const ImageModule::Image& image)
	{
		impl->DrawImage(x, y, image);
	}

	void Painter::DrawImage(const Math::vec2& point, const ImageModule::Image& image)
	{
		impl->DrawImage(point, image);
	}
	
	void Painter::DrawRect(const Math::Rect& rect)
	{
		impl->DrawRect(rect);
	}

	void Painter::DrawRect(float x, float y, float width, float height)
	{
		impl->DrawRect(x, y, width, height);
	}

	void Painter::DrawRoundedRect(float x, float y, float x_r, float y_r)
	{
		impl->DrawRoundedRect(x, y, x_r, y_r);
	}

	void Painter::DrawText(float x, float y, const System::string& text)
	{
        impl->DrawText(x, y, text);
	}

	void Painter::EraseRect(const Math::Rect& rect)
	{
        impl->EraseRect(rect);
	}

	void Painter::FillRect(const Math::Rect& rect, const Brush& brush)
	{
        impl->FillRect(rect, brush);
	}

	void Painter::SetOpacity(float value)
	{
        impl->SetOpacity(value);
	}

	float Painter::GetOpacity() const
	{
		return impl->GetOpacity();
	}

	void Painter::SetPen(const Pen& pen)
	{
        impl->SetPen(pen);
	}

	const Pen& Painter::GetPen() const
	{
		return impl->GetPen();
	}

	PaintEngine* Painter::GetPaintEngine() const
	{
		return impl->GetPaintEngine();
	}

	void Painter::Save()
	{
        impl->Save();
	}

	void Painter::Restore()
	{
        impl->Restore();
	}

	void Painter::Scale(float x, float y)
	{
        impl->Scale(x, y);
	}

	void Painter::Translate(float x, float y)
	{
        impl->Translate(x, y);
	}

	void Painter::SetWorldTransform(const Math::mat3& value)
	{
        impl->SetWorldTransform(value);
	}

	const Math::mat3& Painter::GetWorldTransform() const
	{
		return impl->GetWorldTransform();
	}

	void Painter::SetBackgroundBrush(const Brush& value)
	{
        impl->SetBackgroundBrush(value);
	}

	const Brush& Painter::GetBackgroundBrush() const
	{
		return impl->GetBackgroundBrush();
	}

	void Painter::SetBrush(const Brush& value)
	{
        impl->SetBrush(value);
	}

	const Brush& Painter::GetBrush() const
	{
		return impl->GetBrush();
	}
}
