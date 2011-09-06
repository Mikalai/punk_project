
#include <windows.h>
#include <gl\gl.h>
#include <gl\glext.h>
#include "Light.h"

TLight::TLight() : m_spotExponent(0.0f), m_spotCutoff(90.0f), m_constantAttenuation(1.0f),
m_linearAttenuation(0.0f), m_quadraticAttenuation(0.0f)
{
	m_ambient[0] = 0.6f;
	m_ambient[1] = 0.6f;
	m_ambient[2] = 0.6f;
	m_ambient[3] = 1.0f;

	m_diffuse[0] = 1.0f;
	m_diffuse[1] = 1.0f;
	m_diffuse[2] = 1.0f;
	m_diffuse[3] = 1.0f;

	m_specular[0] = 0.0f;
	m_specular[1] = 0.0f;
	m_specular[2] = 0.0f;
	m_specular[3] = 0.0f;

	m_position[0] = 0.0f;
	m_position[1] = 5.0f;
	m_position[2] = 5.0f;
	m_position[3] = 0.0f;

	m_spotDirection[0] = 0.0f;
	m_spotDirection[1] = 0.0f;
	m_spotDirection[2] = -1.0f;
}

TLight::TLight(const TLight &light)
{
	if (this != &light)
	{
		m_spotCutoff = light.m_spotCutoff;
		m_spotExponent = light.m_spotExponent;
		m_constantAttenuation = light.m_constantAttenuation;
		m_linearAttenuation = light.m_linearAttenuation;
		m_quadraticAttenuation = light.m_quadraticAttenuation;

		memcpy(m_ambient, light.m_ambient, sizeof(m_ambient));
		memcpy(m_diffuse, light.m_diffuse, sizeof(m_diffuse));
		memcpy(m_specular, light.m_specular, sizeof(m_specular));
		memcpy(m_position, light.m_position, sizeof(m_position));
		memcpy(m_spotDirection, light.m_spotDirection, sizeof(m_spotDirection));
	}	
}

TLight& TLight::operator =(const TLight &light)
{
	if (this != &light)
	{
		m_spotCutoff = light.m_spotCutoff;
		m_spotExponent = light.m_spotExponent;
		m_constantAttenuation = light.m_constantAttenuation;
		m_linearAttenuation = light.m_linearAttenuation;
		m_quadraticAttenuation = light.m_quadraticAttenuation;

		memcpy(m_ambient, light.m_ambient, sizeof(m_ambient));
		memcpy(m_diffuse, light.m_diffuse, sizeof(m_diffuse));
		memcpy(m_specular, light.m_specular, sizeof(m_specular));
		memcpy(m_position, light.m_position, sizeof(m_position));
		memcpy(m_spotDirection, light.m_spotDirection, sizeof(m_spotDirection));
	}	
	return *this;
}

TLight::~TLight()
{
}

const float* TLight::GetAmbient() const
{
	return m_ambient;
}

const float* TLight::GetDiffuse() const
{
	return m_diffuse;
}

const float* TLight::GetSpecular() const
{
	return m_specular;
}

const float* TLight::GetPosition() const
{
	return m_position;
}

const float* TLight::GetSpotDirection() const
{
	return m_spotDirection;
}

float TLight::GetSpotExponent() const
{
	return m_spotExponent;
}

float TLight::GetSpotCutoff() const
{
	return m_spotCutoff;
}

float TLight::GetConstantAttenuation() const
{
	return m_constantAttenuation;
}

float TLight::GetLinearAttenuation() const
{
	return m_linearAttenuation;
}

float TLight::GetQuadraticAttenuation() const
{
	return m_quadraticAttenuation;
}

void TLight::SetAmbient(float r, float g, float b, float a)
{
	m_ambient[0] = r;
	m_ambient[1] = g;
	m_ambient[2] = b;
	m_ambient[3] = a;
	glLightfv(GL_LIGHT0+m_id, GL_AMBIENT, m_ambient);
}

void TLight::SetDiffuse(float r, float g, float b, float a)
{
	m_diffuse[0] = r;
	m_diffuse[1] = g;
	m_diffuse[2] = b;
	m_diffuse[3] = a;
	glLightfv(GL_LIGHT0+m_id, GL_DIFFUSE, m_diffuse);
}

void TLight::SetPosition(float x, float y, float z, float w)
{
	m_position[0] = x;
	m_position[1] = y;
	m_position[2] = z;
	m_position[3] = w;
	glPushMatrix();
	glLoadIdentity();
	glLightfv(GL_LIGHT0+m_id, GL_POSITION, m_position);
	glPopMatrix();
}

void TLight::SetSpecular(float r, float g, float b, float a)
{
	m_specular[0] = r;
	m_specular[1] = g;
	m_specular[2] = b;
	m_specular[3] = a;
	glLightfv(GL_LIGHT0+m_id, GL_SPECULAR, m_specular);
}

void TLight::SetSpotDirection(float x, float y, float z)
{
	m_spotDirection[0] = x;
	m_spotDirection[1] = y;
	m_spotDirection[2] = z;
	glLightfv(GL_LIGHT0+m_id, GL_SPOT_DIRECTION, m_spotDirection);
}
	
void TLight::SetConstantAttenuation(float c)
{
	m_constantAttenuation = c;
	glLightf(GL_LIGHT0+m_id, GL_CONSTANT_ATTENUATION, m_constantAttenuation);
}

void TLight::SetLinearAttenuation(float c)
{
	m_linearAttenuation = c;
	glLightf(GL_LIGHT0+m_id, GL_LINEAR_ATTENUATION, m_linearAttenuation);
}

void TLight::SetQuadraticAttenuation(float c)
{
	m_quadraticAttenuation = c;
	glLightf(GL_LIGHT0+m_id, GL_QUADRATIC_ATTENUATION, m_quadraticAttenuation);
}

void TLight::SetSpotCutoff(float c)
{
	m_spotCutoff = c;
	glLightf(GL_LIGHT0+m_id, GL_SPOT_CUTOFF, m_spotCutoff);
}

void TLight::SetSpotExponent(float e)
{
	m_spotExponent = e;
	glLightf(GL_LIGHT0+m_id, GL_SPOT_EXPONENT, m_spotExponent);
}

void TLight::TurnOff()
{
	glDisable(GL_LIGHT0+m_id);
}

void TLight::TurnOn()
{
	glEnable(GL_LIGHT0+m_id);
}

void TLight::Apply()
{
	glLightfv(GL_LIGHT0+m_id, GL_AMBIENT, m_ambient);
	glLightfv(GL_LIGHT0+m_id, GL_DIFFUSE, m_diffuse);
	glLightfv(GL_LIGHT0+m_id, GL_SPECULAR, m_specular);
	glLightfv(GL_LIGHT0+m_id, GL_POSITION, m_position);
	glLightfv(GL_LIGHT0+m_id, GL_SPOT_DIRECTION, m_spotDirection);
	glLightf(GL_LIGHT0+m_id, GL_SPOT_EXPONENT, m_spotExponent);
	glLightf(GL_LIGHT0+m_id, GL_SPOT_CUTOFF, m_spotCutoff);
	glLightf(GL_LIGHT0+m_id, GL_CONSTANT_ATTENUATION, m_constantAttenuation);
	glLightf(GL_LIGHT0+m_id, GL_LINEAR_ATTENUATION, m_linearAttenuation);
	glLightf(GL_LIGHT0+m_id, GL_QUADRATIC_ATTENUATION, m_quadraticAttenuation);
	glEnable(GL_LIGHT0+m_id);
}