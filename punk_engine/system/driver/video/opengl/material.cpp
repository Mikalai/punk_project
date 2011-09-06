#include <memory.h>
#include "material.h"

namespace Driver
{
	Material::Material() : m_shine(0), m_subMaterial(0), m_subMaterialCount(0), m_transparency(0)
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

	Material::Material(const Material &material)
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
				m_subMaterial = new Material;
				memcpy(m_subMaterial, material.m_subMaterial, sizeof(Material)*m_subMaterialCount);
			}
		}
	}

	Material& Material::operator =(const Material &material)
	{
		if (this != &material)
		{
			memcpy(m_ambient, material.m_ambient, sizeof(m_ambient));
			memcpy(m_diffuse, material.m_diffuse, sizeof(m_diffuse));
			memcpy(m_specular, material.m_specular, sizeof(m_specular));
			m_shine = material.m_shine;
			m_transparency = material.m_transparency;

			delete[] m_subMaterial;
			m_subMaterial = 0;

			m_subMaterialCount = material.m_subMaterialCount;
			if (m_subMaterialCount > 0)
			{
				m_subMaterial = new Material;
				memcpy(m_subMaterial, material.m_subMaterial, sizeof(Material)*m_subMaterialCount);
			}
		}
		return *this;
	}

	Material::~Material()
	{
		m_subMaterial;
		m_subMaterial = 0;
	}

	float* Material::GetAmbient()
	{
		return m_ambient;
	}

	float* Material::GetDiffuse()
	{
		return m_diffuse;
	}

	float* Material::GetSpecular()
	{
		return m_specular;
	}

	float Material::GetShine() const
	{
		return m_shine;
	}

	float Material::GetTransparency() const
	{
		return m_transparency;
	}

	void Material::SetAmbient(float r, float g, float b, float a)
	{
		m_ambient[0] = r;
		m_ambient[1] = g;
		m_ambient[2] = b;
		m_ambient[3] = a;
	}

	void Material::SetDiffuse(float r, float g, float b, float a)
	{
		m_diffuse[0] = r;
		m_diffuse[1] = g;
		m_diffuse[2] = b;
		m_diffuse[3] = a;
	}

	void Material::SetSpecular(float r, float g, float b, float a)
	{
		m_specular[0] = r;
		m_specular[1] = g;
		m_specular[2] = b;
		m_specular[3] = a;
	}

	void Material::SetShine(float shine)
	{
		m_shine = shine;
	}

	void Material::SetTransparency(float transparency)
	{
		m_transparency = transparency;
	}

	int Material::GetSubMaterialsCount() const
	{
		return m_subMaterialCount;
	}

	Material* Material::GetSubMaterials()
	{
		return m_subMaterial;
	}

	float Material::GetShineStrength() const
	{
		return m_shineStrength;
	}

	void Material::SetShineStrength(float shineStrength)
	{
		m_shineStrength = shineStrength;
	}

	void Material::Apply()
	{

	}
}
