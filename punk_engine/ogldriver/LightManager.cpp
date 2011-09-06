#include "LightManager.h"

TLightManager::TLightManager()
{
	m_ambient[0] = 0.2f;
	m_ambient[1] = 0.2f;
	m_ambient[2] = 0.2f;
	m_ambient[3] = 0.1f;
}

TLightManager::TLightManager(const TLightManager &lightManager)
{
	if (this != &lightManager)
	{
		memcpy(m_light, lightManager.m_light, sizeof(TLight)*PUNK_MAX_LIGHTS);
	}
}

TLightManager& TLightManager::operator =(const TLightManager &lightManager)
{
	if (this != &lightManager)
	{
		memcpy(m_light, lightManager.m_light, sizeof(TLight)*PUNK_MAX_LIGHTS);
	}
	return *this;
}

void TLightManager::EnableLighting()
{
	glEnable(GL_LIGHTING);
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL_EXT, GL_SEPARATE_SPECULAR_COLOR);
}

void TLightManager::DisableLighting()
{
	glDisable(GL_LIGHTING);
}

ILight* TLightManager::GetLight(int id)
{
	if (id < 0 || id >= PUNK_MAX_LIGHTS)
		return NULL;
	m_light[id].m_id = id;
	return m_light + id;
}

TLightManager::~TLightManager()
{
}

void TLightManager::SetAmbient(float r, float g, float b, float a)
{
	m_ambient[0] = r;
	m_ambient[1] = g;
	m_ambient[2] = b;
	m_ambient[3] = a;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, m_ambient);
}