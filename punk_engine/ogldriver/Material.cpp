#include <windows.h>
#include <gl\gl.h>
#include <gl\glext.h>
#include "Material.h"

TMaterial::TMaterial() : m_shine(0), m_subMaterial(NULL), m_subMaterialCount(0), m_transparency(0)
{
	m_ambient[0] = 0.2f;
	m_ambient[1] = 0.2f;
	m_ambient[2] = 0.2f;
	m_ambient[3] = 1.0f;

	m_diffuse[0] = 0.8f;
	m_diffuse[1] = 0.8f;
	m_diffuse[2] = 0.8f;
	m_diffuse[3] = 1.0f;

	m_specular[0] = 0.0f;
	m_specular[1] = 0.0f;
	m_specular[2] = 0.0f;
	m_specular[3] = 1.0f;
}

TMaterial::TMaterial(const TMaterial &material)
{
	if (this != &material)
	{
		memcpy(m_ambient, material.m_ambient, sizeof(m_ambient));
		memcpy(m_diffuse, material.m_diffuse, sizeof(m_diffuse));
		memcpy(m_specular, material.m_specular, sizeof(m_specular));
		m_shine = material.m_shine;
		m_transparency = material.m_transparency;
		m_subMaterialCount = material.m_subMaterialCount;
		if (m_subMaterialCount > 0)
		{
			m_subMaterial = new TMaterial;
			memcpy(m_subMaterial, material.m_subMaterial, sizeof(TMaterial)*m_subMaterialCount);
		}
	}
}

TMaterial& TMaterial::operator =(const TMaterial &material)
{
	if (this != &material)
	{
		memcpy(m_ambient, material.m_ambient, sizeof(m_ambient));
		memcpy(m_diffuse, material.m_diffuse, sizeof(m_diffuse));
		memcpy(m_specular, material.m_specular, sizeof(m_specular));
		m_shine = material.m_shine;
		m_transparency = material.m_transparency;
		
		DELETE_ARRAY(m_subMaterial);

		m_subMaterialCount = material.m_subMaterialCount;
		if (m_subMaterialCount > 0)
		{
			m_subMaterial = new TMaterial;
			memcpy(m_subMaterial, material.m_subMaterial, sizeof(TMaterial)*m_subMaterialCount);
		}
	}
	return *this;
}

TMaterial::~TMaterial()
{
	DELETE_ARRAY(m_subMaterial);
}

float* TMaterial::GetAmbient()
{
	return m_ambient;
}

float* TMaterial::GetDiffuse()
{
	return m_diffuse;
}

float* TMaterial::GetSpecular()
{
	return m_specular;
}

float TMaterial::GetShine() const
{
	return m_shine;
}

float TMaterial::GetTransparency() const
{
	return m_transparency;
}

void TMaterial::SetAmbient(float r, float g, float b, float a)
{
	m_ambient[0] = r;
	m_ambient[1] = g;
	m_ambient[2] = b;
	m_ambient[3] = a;
}

void TMaterial::SetDiffuse(float r, float g, float b, float a)
{
	m_diffuse[0] = r;
	m_diffuse[1] = g;
	m_diffuse[2] = b;
	m_diffuse[3] = a;
}

void TMaterial::SetSpecular(float r, float g, float b, float a)
{
	m_specular[0] = r;
	m_specular[1] = g;
	m_specular[2] = b;
	m_specular[3] = a;
}

void TMaterial::SetShine(float shine)
{
	m_shine = shine;
}

void TMaterial::SetTransparency(float transparency)
{
	m_transparency = transparency;
}

int TMaterial::GetSubMaterialsCount() const
{
	return m_subMaterialCount;
}

TMaterial* TMaterial::GetSubMaterials()
{
	return m_subMaterial;
}

float TMaterial::GetShineStrength() const
{
	return m_shineStrength;
}

void TMaterial::SetShineStrength(float shineStrength)
{
	m_shineStrength = shineStrength;
}

void TMaterial::Apply()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, m_shine);
}