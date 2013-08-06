#include "../../math/mat3.h"
#include "../../math/vec4.h"

#include "brush.h"

namespace Gpu
{
	struct Brush::BrushImpl
	{
		Math::vec4 m_color;
		Math::mat3 m_transform;
		int m_style;
		const Texture2D* m_texture;

		void SetColor(const Math::vec4& value)
		{
			m_color = value;
		}

		const Math::vec4& GetColor() const
		{
			return m_color;
		}

		void SetMatrix(const Math::mat3& value)
		{
			m_transform = value;
		}

		const Math::mat3& GetMatrix() const
		{
			return m_transform;
		}

		void SetStyle(int value)
		{
			m_style = value;
		}

		int GetStyle() const
		{
			return m_style;
		}

		void SetTexture(const Texture2D* texture)
		{
			m_texture = texture;
		}

		const Texture2D* GetTexture() const
		{
			return m_texture;
		}
	};

	Brush::Brush()
		: impl(new BrushImpl)
	{}

	Brush::~Brush()
	{
		delete impl;
		impl = nullptr;
	}

	Brush::Brush(const Brush& value)
		: impl(new BrushImpl(*value.impl))
	{}

	Brush& Brush::operator= (const Brush& value)
	{
		Brush temp(value);
		std::swap(temp.impl, impl);
		return *this;
	}

	void Brush::SetColor(const Math::vec4& value)
	{
		impl->SetColor(value);
	}

	const Math::vec4& Brush::GetColor() const
	{
		return impl->GetColor();
	}

	void Brush::SetMatrix(const Math::mat3& value)
	{
		impl->SetMatrix(value);
	}

	const Math::mat3& Brush::GetMatrix() const
	{
		return impl->GetMatrix();
	}

	void Brush::SetStyle(int value)
	{
		impl->SetStyle(value);
	}

	int Brush::GetStyle() const
	{
		return impl->GetStyle();
	}

	void Brush::SetTexture(const Texture2D* texture)
	{
		impl->SetTexture(texture);
	}

	const Texture2D* Brush::GetTexture() const
	{
		return impl->GetTexture();
	}
}
