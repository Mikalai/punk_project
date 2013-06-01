#include <memory>
#include <istream>
#include <ostream>
#include "material.h"
#include "../../utility/descriptors/material_desc.h"
#include "../../system/hresource.h"

namespace Virtual
{
	Material::Cache::Cache()
		: m_diffuse_texture_cache(nullptr)
		, m_normal_texture_cache(nullptr)
		, m_diffuse_texture_cache_2(nullptr)
		, m_height_texture_cache(nullptr)
		, m_specular_texture_cache(nullptr)
	{}
	
	Material* Material::DefaultMaterial(new Material);

	Material::Material()
		: m_diffuse_map(L"")
		, m_normal_map(L"")
		, m_diffuse_color(0.1f, 0.1f, 0.1f, 1.0f)
		, m_specular_color(1.0f, 1.0f, 1.0f, 1.0f)
		, m_specular_factor(128)
		, m_name(L"")
		, m_ambient(0.0f)
		, m_diffuse_intensity(1.0f)
		, m_darkness(0.0f)
		, m_diffuse_fresnel(1.0f)
		, m_diffuse_fresnel_factor(0.0f)
		, m_emit(0.0f)
		, m_mirror_color(0.0f, 0.0f, 0.0f, 1.0f)
		, m_roughness(0.0f)
		, m_specular_intensity(128.0f)
		, m_specular_index_of_refraction(1.0f)
		, m_specular_slope(0.0f)
		, m_translucency(0.0f)
	{
		SetType(System::ObjectType::MATERIAL);
	}

	Material::Material(const Utility::MaterialDesc& desc)
	{
		SetType(System::ObjectType::MATERIAL);
		m_diffuse_map = desc.m_diffuse_map;
		m_normal_map = desc.m_normal_map;
		m_diffuse_color = desc.m_diffuse_color; m_diffuse_color.W() = desc.m_alpha;
		m_specular_color = desc.m_specular_color; m_specular_color.W() = desc.m_specular_alpha;
		m_specular_factor = desc.m_specular_factor;
		m_name = desc.m_name;
		m_ambient = desc.m_ambient;
		m_diffuse_intensity = desc.m_diffuse_intensity;
		m_darkness = desc.m_darkness;
		m_diffuse_fresnel = desc.m_diffuse_fresnel;
		m_diffuse_fresnel_factor = desc.m_diffuse_fresnel_factor;
		m_emit = desc.m_emit;
		m_mirror_color = desc.m_mirror_color;
		m_roughness = desc.m_roughness;
		m_specular_intensity = desc.m_specular_intensity;
		m_specular_index_of_refraction = desc.m_specular_index_of_refraction;
		m_specular_slope = desc.m_specular_slope;
		m_translucency = desc.m_translucency;
	}


	void Material::SetTexture0(const System::string& map)
	{
		m_diffuse_map = map;
	}

	void Material::SetTexture1(const System::string& map)
	{
		m_normal_map = map;
	}

	void Material::SetDiffuseColor(const Math::vec4& color)
	{
		m_diffuse_color = color;
	}

	void Material::SetSpecularColor(const Math::vec4& color)
	{
		m_specular_color = color;
	}

	void Material::SetSpecularFactor(float value)
	{
		m_specular_factor = value;
	}

	void Material::SetName(const System::string& name)
	{
		m_name = name;
	}

	const System::string& Material::GetDiffuseMap() const
	{
		return m_diffuse_map;
	}

	const System::string& Material::GetNormalMap() const
	{
		return m_normal_map;
	}

	const Math::vec4& Material::GetDiffuseColor() const
	{
		return m_diffuse_color;
	}

	const Math::vec4& Material::GetSpecularColor() const
	{
		return m_specular_color;
	}

	float Material::GetSpecularFactor() const
	{
		return m_specular_factor;
	}

	const System::string& Material::GetName() const
	{
		return m_name;
	}

	bool Material::Save(std::ostream& stream) const
	{
		m_diffuse_map.Save(stream);
		m_normal_map.Save(stream);
		m_diffuse_color.Save(stream);
		m_specular_color.Save(stream);
		m_name.Save(stream);
		stream.write((char*)&m_specular_factor, sizeof(m_specular_factor));	

		stream.write((char*)&m_ambient, sizeof(m_ambient));	
		stream.write((char*)&m_diffuse_intensity, sizeof(m_diffuse_intensity));	
		stream.write((char*)&m_darkness, sizeof(m_darkness));	
		stream.write((char*)&m_diffuse_fresnel, sizeof(m_diffuse_fresnel));	
		stream.write((char*)&m_diffuse_fresnel_factor, sizeof(m_diffuse_fresnel_factor));	
		stream.write((char*)&m_emit, sizeof(m_emit));			
		m_mirror_color.Save(stream);
		stream.write((char*)&m_roughness, sizeof(m_roughness));			
		stream.write((char*)&m_specular_intensity, sizeof(m_specular_intensity));			
		stream.write((char*)&m_specular_index_of_refraction, sizeof(m_specular_index_of_refraction));
		stream.write((char*)&m_specular_slope, sizeof(m_specular_slope));
		stream.write((char*)&m_translucency, sizeof(m_translucency));		

		return true;
	}

	bool Material::Load(std::istream& stream)
	{
		m_diffuse_map.Load(stream);
		m_normal_map.Load(stream);
		m_diffuse_color.Load(stream);
		m_specular_color.Load(stream);
		m_name.Load(stream);
		stream.read((char*)&m_specular_factor, sizeof(m_specular_factor));		

		stream.read((char*)&m_ambient, sizeof(m_ambient));	
		stream.read((char*)&m_diffuse_intensity, sizeof(m_diffuse_intensity));	
		stream.read((char*)&m_darkness, sizeof(m_darkness));	
		stream.read((char*)&m_diffuse_fresnel, sizeof(m_diffuse_fresnel));	
		stream.read((char*)&m_diffuse_fresnel_factor, sizeof(m_diffuse_fresnel_factor));	
		stream.read((char*)&m_emit, sizeof(m_emit));			
		m_mirror_color.Load(stream);
		stream.read((char*)&m_roughness, sizeof(m_roughness));			
		stream.read((char*)&m_specular_intensity, sizeof(m_specular_intensity));			
		stream.read((char*)&m_specular_index_of_refraction, sizeof(m_specular_index_of_refraction));
		stream.read((char*)&m_specular_slope, sizeof(m_specular_slope));
		stream.read((char*)&m_translucency, sizeof(m_translucency));		

		return true;
	}

	Material::~Material()
	{
	}

	Material* Material::CreateFromFile(const System::string& path)
	{
		return nullptr;
	}

	Material* Material::CreateFromStream(std::istream& stream)
	{
		return nullptr;
	}

	void Material::DropCache() 
	{ 
		safe_delete(m_cache.m_diffuse_texture_cache);
		safe_delete(m_cache.m_normal_texture_cache);
		safe_delete(m_cache.m_diffuse_texture_cache_2);
		safe_delete(m_cache.m_height_texture_cache);
	}

}
