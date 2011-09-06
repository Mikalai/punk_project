/*
	File: Fog.cpp
	Author: Abramov Nickolai
	Description: Nothing to say
*/

#include "fog.h"

Fog::Fog() : m_type(PUNK_FOG_EXP), m_density(0.35f), m_start(1.0), m_end(5.0)
{
	m_color[0] = 0.5f;
	m_color[1] = 0.5f;
	m_color[2] = 0.5f;
	m_color[3] = 1.0f;
}

Fog::~Fog()
{
}

Fog::Fog(const Fog &fog)
{
	if (this != &fog)
	{
		m_type = fog.m_type;
		m_density = fog.m_density;
		m_start = fog.m_start;
		m_end = fog.m_end;
		memcpy(m_color, fog.m_color, sizeof(m_color));
	}
}

Fog& Fog::operator =(const Fog &fog)
{
	if (this != &fog)
	{
		m_type = fog.m_type;
		m_density = fog.m_density;
		m_start = fog.m_start;
		m_end = fog.m_end;
		memcpy(m_color, fog.m_color, sizeof(m_color));
	}
	return *this;
}

FogType Fog::GetType() const
{
	return m_type;
}

void Fog::SetType(FogType type)
{
	m_type = type;
	switch(type)
	{
	case PUNK_FOG_EXP:
		glFogi(GL_FOG_MODE, GL_EXP);
		break;
	case PUNK_FOG_EXP2:
		glFogi(GL_FOG_MODE, GL_EXP2);
		break;
	case PUNK_FOG_LINEAR:
		glFogi(GL_FOG_MODE, GL_LINEAR);
		break;
	default:
		throw Exception(PUNK_TEXT("Unsupported fog mode"));
	}
}

void Fog::SetColor(float r, float g, float b, float a)
{
	m_color[0] = r;
	m_color[1] = g;
	m_color[2] = b;
	m_color[3] = a;

	glFogfv(GL_FOG_COLOR, m_color);
}

void Fog::SetDensity(float density)
{
	m_density = density;

	glFogf(GL_FOG_DENSITY, m_density);
}

void Fog::SetEnd(float end)
{
	m_end = end;
	glFogf(GL_FOG_END, m_end);
}

void Fog::SetStart(float start)
{
	m_start = start;
	glFogf(GL_FOG_START, m_start);
}

float* Fog::GetColor()
{
	return m_color;
}

float Fog::GetDensity() const
{
	return m_density;
}

float Fog::GetEnd() const
{
	return m_end;
}

float Fog::GetStart() const
{
	return m_start;
}


void Fog::Enable()
{
	glEnable(GL_FOG);
	switch(m_type)
	{
	case PUNK_FOG_EXP:
		glFogi(GL_FOG_MODE, GL_EXP);
		break;
	case PUNK_FOG_EXP2:
		glFogi(GL_FOG_MODE, GL_EXP2);
		break;
	case PUNK_FOG_LINEAR:
		glFogi(GL_FOG_MODE, GL_LINEAR);
		break;
	default:
		throw Exception(PUNK_TEXT("Unsupported fog mode"));
	}

	glFogfv(GL_FOG_COLOR, m_color);
	glFogf(GL_FOG_DENSITY, m_density);
	glFogf(GL_FOG_START, m_start);
	glFogf(GL_FOG_END, m_end);
}

void Fog::Disable()
{
	glDisable(GL_FOG);
}
#include <windows.h>
#include <gl\gl.h>
#include <gl\glext.h>
#include <exception>

#include "Fog.h"

TFog::TFog() : m_type(PUNK_FOG_EXP), m_density(0.35f), m_start(1.0), m_end(5.0)
{
	m_color[0] = 0.5f;
	m_color[1] = 0.5f;
	m_color[2] = 0.5f;
	m_color[3] = 1.0f;
}

TFog::~TFog()
{
}

TFog::TFog(const TFog &fog)
{
	if (this != &fog)
	{
		m_type = fog.m_type;
		m_density = fog.m_density;
		m_start = fog.m_start;
		m_end = fog.m_end;
		memcpy(m_color, fog.m_color, sizeof(m_color));
	}
}

TFog& TFog::operator =(const TFog &fog)
{
	if (this != &fog)
	{
		m_type = fog.m_type;
		m_density = fog.m_density;
		m_start = fog.m_start;
		m_end = fog.m_end;
		memcpy(m_color, fog.m_color, sizeof(m_color));
	}
	return *this;
}

FogType TFog::GetType() const
{
	return m_type;
}

void TFog::SetType(FogType type)
{
	m_type = type;
	switch(type)
	{
	case PUNK_FOG_EXP:
		glFogi(GL_FOG_MODE, GL_EXP);
		break;
	case PUNK_FOG_EXP2:
		glFogi(GL_FOG_MODE, GL_EXP2);
		break;
	case PUNK_FOG_LINEAR:
		glFogi(GL_FOG_MODE, GL_LINEAR);
		break;
	default:
		throw Exception(PUNK_TEXT("Unsupported fog mode"));
	}
}

void TFog::SetColor(float r, float g, float b, float a)
{
	m_color[0] = r;
	m_color[1] = g;
	m_color[2] = b;
	m_color[3] = a;

	glFogfv(GL_FOG_COLOR, m_color);
}

void TFog::SetDensity(float density)
{
	m_density = density;

	glFogf(GL_FOG_DENSITY, m_density);
}

void TFog::SetEnd(float end)
{
	m_end = end;
	glFogf(GL_FOG_END, m_end);
}

void TFog::SetStart(float start)
{
	m_start = start;
	glFogf(GL_FOG_START, m_start);
}

float* TFog::GetColor()
{
	return m_color;
}

float TFog::GetDensity() const
{
	return m_density;
}

float TFog::GetEnd() const
{
	return m_end;
}

float TFog::GetStart() const
{
	return m_start;
}


void TFog::Enable()
{
	glEnable(GL_FOG);
	switch(m_type)
	{
	case PUNK_FOG_EXP:
		glFogi(GL_FOG_MODE, GL_EXP);
		break;
	case PUNK_FOG_EXP2:
		glFogi(GL_FOG_MODE, GL_EXP2);
		break;
	case PUNK_FOG_LINEAR:
		glFogi(GL_FOG_MODE, GL_LINEAR);
		break;
	default:
		throw Exception(PUNK_TEXT("Unsupported fog mode"));
	}

	glFogfv(GL_FOG_COLOR, m_color);
	glFogf(GL_FOG_DENSITY, m_density);
	glFogf(GL_FOG_START, m_start);
	glFogf(GL_FOG_END, m_end);
}

void TFog::Disable()
{
	glDisable(GL_FOG);
}