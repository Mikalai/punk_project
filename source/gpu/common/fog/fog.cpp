#include "fog.h"

namespace GPU
{

	FogDescription::FogDescription()
		: m_enable(false)
		, m_mode(FogMode::Linear)
		, m_color(1,1,1,1)
		, m_density(1)
		, m_start(0)
		, m_end(1)
	{}

	void FogDescription::Enable(bool value)
	{
		m_enable = value;
	}

	void FogDescription::SetMode(FogMode value)
	{
		m_mode = value;
	}

	void FogDescription::SetColor(const Math::vec4& value)
	{
		m_color = value;
	}

	void FogDescription::SetColor(float r, float g, float b, float a)
	{
		m_color.Set(r, g, b, a);
	}

	void FogDescription::SetDensity(float value)
	{
		m_density = value;
	}

	void FogDescription::SetStart(float value)
	{
		m_start = value;
	}

	void FogDescription::SetEnd(float value)
	{
		m_end = value;
	}

	bool FogDescription::IsEnabled() const
	{
		return m_enable;
	}

	const FogMode FogDescription::GetMode() const
	{
		return m_mode;
	}

	const Math::vec4& FogDescription::GetColor() const
	{
		return m_color;
	}

	float FogDescription::GetDensity() const
	{
		return m_density;
	}

	float FogDescription::GetStart() const
	{
		return m_start;
	}

	float FogDescription::GetEnd() const
	{
		return m_end;
	}
}