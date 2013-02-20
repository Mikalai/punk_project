#include <algorithm>
#include "../../math/vec4.h"
#include "pen.h"

namespace GPU
{
	struct Pen::PenImpl
	{
		Math::vec4 m_color;
		float m_width;

		void SetColor(const Math::vec4& color)
		{
			m_color = color;
		}

		void SetColor(float r, float g, float b, float a)
		{
			m_color.Set(r, g, b, a);
		}

		void SetWidth(float value)
		{
			m_width = value;
		}

		const Math::vec4& GetColor() const
		{
			return m_color;
		}

		float GetWidth() const
		{
			return m_width;
		}
	};

	Pen::Pen()
		: impl(new PenImpl)
	{}

	Pen::~Pen()
	{
		delete impl;
		impl = nullptr;
	}

	Pen::Pen(const Pen& value)
		: impl(new PenImpl(*value.impl))
	{}

	Pen& Pen::operator= (const Pen& value)
	{
		Pen temp(value);
		std::swap(temp.impl, impl);
		return *this;
	}

	void Pen::SetColor(const Math::vec4& color)
	{
		impl->SetColor(color);
	}

	void Pen::SetColor(float r, float g, float b, float a)
	{
		impl->SetColor(r, g, b, a);
	}

	void Pen::SetWidth(float value)
	{
		impl->SetWidth(value);
	}

	const Math::vec4& Pen::GetColor() const 
	{
		return impl->GetColor();
	}

	float Pen::GetWidth() const 
	{
		return impl->GetWidth();
	}
}