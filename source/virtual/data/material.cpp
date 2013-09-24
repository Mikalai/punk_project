#include <memory>
#include <istream>
#include <ostream>
#include "material.h"
#include "../../utility/descriptors/material_desc.h"
#include "../../system/buffer.h"
#include "texture_slot.h"
#include "../../engine_objects.h"

namespace Virtual
{
    PUNK_OBJECT_REG(Material, "Virtual.Material", PUNK_MATERIAL, SaveMaterial, LoadMaterial, &System::Object::Info.Type);

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
        Info.Add(this);
	}

	Material::Material(const Utility::MaterialDesc& desc)
	{
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

        Info.Add(this);
	}

    Material::~Material()
    {
        while (!m_texture_slots.empty())
        {
            delete m_texture_slots.back();
            m_texture_slots.pop_back();
        }

        Info.Remove(this);
    }


    void Material::SetDiffuseMap(const System::string& map)
	{
		m_diffuse_map = map;
	}

    void Material::SetNormalMap(const System::string& map)
	{
		m_normal_map = map;
	}

    void Material::SetSpecularMap(const System::string &map)
    {
        m_specular_map = map;
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

    PUNK_ENGINE_API void SaveMaterial(System::Buffer* buffer, const System::Object* o)
	{
        System::SaveObject(buffer, o);
        const Material* m = Cast<const Material*>(o);
        System::SaveString(buffer, m->m_diffuse_map);
        System::SaveString(buffer, m->m_normal_map);
        System::SaveString(buffer, m->m_name);
        Math::SaveVector4f(buffer, m->m_diffuse_color);
        Math::SaveVector4f(buffer, m->m_specular_color);
        Math::SaveVector4f(buffer, m->m_mirror_color);
        buffer->WriteReal32(m->m_specular_factor);
        buffer->WriteReal32(m->m_ambient);
        buffer->WriteReal32(m->m_diffuse_intensity);
        buffer->WriteReal32(m->m_darkness);
        buffer->WriteReal32(m->m_diffuse_fresnel);
        buffer->WriteReal32(m->m_diffuse_fresnel_factor);
        buffer->WriteReal32(m->m_emit);
        buffer->WriteReal32(m->m_roughness);
        buffer->WriteReal32(m->m_specular_intensity);
        buffer->WriteReal32(m->m_specular_index_of_refraction);
        buffer->WriteReal32(m->m_specular_slope);
        buffer->WriteReal32(m->m_translucency);
	}

    void LoadMaterial(System::Buffer* buffer, System::Object* o)
	{
        System::LoadObject(buffer, o);
        Material* m = Cast<Material*>(o);
        System::LoadString(buffer, m->m_diffuse_map);
        System::LoadString(buffer, m->m_normal_map);
        System::LoadString(buffer, m->m_name);
        Math::LoadVector4f(buffer, m->m_diffuse_color);
        Math::LoadVector4f(buffer, m->m_specular_color);
        Math::LoadVector4f(buffer, m->m_mirror_color);
        m->m_specular_factor = buffer->ReadReal32();
        m->m_ambient = buffer->ReadReal32();
        m->m_diffuse_intensity = buffer->ReadReal32();
        m->m_darkness = buffer->ReadReal32();
        m->m_diffuse_fresnel = buffer->ReadReal32();
        m->m_diffuse_fresnel_factor = buffer->ReadReal32();
        m->m_emit = buffer->ReadReal32();
        m->m_roughness = buffer->ReadReal32();
        m->m_specular_intensity = buffer->ReadReal32();
        m->m_specular_index_of_refraction = buffer->ReadReal32();
        m->m_specular_slope = buffer->ReadReal32();
        m->m_translucency = buffer->ReadReal32();
	}

	Material* Material::CreateFromFile(const System::string& path)
	{
		return nullptr;
	}

	Material* Material::CreateFromStream(std::istream& stream)
	{
		return nullptr;
	}

    void Material::AddTextureSlot(TextureSlot* value)
    {
        m_texture_slots.push_back(value);
    }

    TextureSlot* Material::GetTextureSlot(size_t index)
    {
        return m_texture_slots.at(index);
    }

    const TextureSlot* Material::GetTextureSlot(size_t index) const
    {
        return m_texture_slots.at(index);
    }

    size_t Material::GetTextureSlotCount() const
    {
        return m_texture_slots.size();
    }
}
