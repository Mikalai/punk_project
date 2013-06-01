#ifndef _H_PUNK_VIRTUAL_MATERIAL
#define _H_PUNK_VIRTUAL_MATERIAL

#include <iosfwd>
#include <map>

#include "../../config.h"
#include "../../system/object.h"
#include "../../system/aop/aop.h"
#include "../../system/smart_pointers/module.h"
#include "../../math/vec4.h"
#include "../../string/string.h"

namespace Utility
{
	class MaterialDesc;
}

namespace Virtual
{
	class PUNK_ENGINE_PUBLIC Material : public System::Object, public System::Aspect<Material*, System::string>
	{
	public:		
		/**
		*	When cache is droped data should be removed, because
		*	it is considered, that Material is owner of this stuff
		*/
		struct Cache
		{
			System::Object* m_diffuse_texture_cache;
			System::Object* m_normal_texture_cache;
			System::Object* m_diffuse_texture_cache_2;
			System::Object* m_height_texture_cache;
			System::Object* m_specular_texture_cache;

			Cache();
		};
	
	public:

		Material();
		Material(const Utility::MaterialDesc& desc);

		void SetTexture0(const System::string& map);
		void SetTexture1(const System::string& map);
		void SetDiffuseColor(const Math::vec4& color);
		void SetSpecularColor(const Math::vec4& color);
		void SetSpecularFactor(float value);
		void SetName(const System::string& name);

		const System::string& GetDiffuseMap() const;
		const System::string& GetNormalMap() const;
		const Math::vec4& GetDiffuseColor() const;
		const Math::vec4& GetSpecularColor() const;
		float GetSpecularFactor() const;
		const System::string& GetName() const;

		void SetAlpha(float value) { m_diffuse_color[3] = value; }
		float GetAlpha() const { return m_diffuse_color[3]; }

		void SetAmbient(float value) { m_ambient = value; }
		float GetAmbient() const { return m_ambient; }

		void SetDiffuseIntensity(float value) { m_diffuse_intensity = value; }
		float GetDiffuseIntensity() const { return m_diffuse_intensity; }

		void SetDarkness(float value) { m_darkness = value; }
		float GetDarkness() const { return m_darkness; }

		void SetDiffuseFresnel(float value ) { m_diffuse_fresnel = value; }
		float GetDiffuseFresnel() const { return m_diffuse_fresnel; }

		void SetDiffuseFresnelFactor(float value) { m_diffuse_fresnel_factor = value; }
		float GetDiffuseFresnelFactor() const { return m_diffuse_fresnel_factor; }

		void SetEmit(float value) { m_emit = value; }
		float GetEmit() const { return m_emit; }

		void SetMirrorColor(Math::vec4 value) { m_mirror_color = value; }
		const Math::vec4 GetMirrorColor() const { return m_mirror_color; }

		void SetRoughness(float value) { m_roughness = value; }
		float GetRoughness() const { return m_roughness; }

		void SetSpecularAlpha(float value) { m_specular_color[3] = value; }
		float GetSpecularAlpha() const { return m_specular_color[3]; }

		void SetSpecularIntensity(float value) { m_specular_intensity = value; }
		float GetSpecularIntensity() const { return m_specular_intensity; }

		void SetSpecularIndexOfRefraction(float value) { m_specular_index_of_refraction = value; }
		float GetSpecularIndexOfRefraction() const { return m_specular_index_of_refraction; }

		void SetSpecularSlope(float value) { m_specular_slope = value; }
		float GetSpecularSlope() const { return m_specular_slope; }

		void SetTranslucency(float value) { m_translucency = value; }
		float GetTranslucency() const { return m_translucency; }

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);
		virtual ~Material();

		static Material* CreateFromFile(const System::string& path);
		static Material* CreateFromStream(std::istream& stream);

		static Material* DefaultMaterial;

		void DropCache();
		
		void SetDiffuseTextureCache(System::Object* value) { m_cache.m_diffuse_texture_cache = value; }
		void SetNormalTextureCache(System::Object* value) { m_cache.m_normal_texture_cache = value; }
		void SetDiffuseTexture2Cache(System::Object* value) { m_cache.m_diffuse_texture_cache_2 = value; }
		void SetHeightTextureCache(System::Object* value) { m_cache.m_height_texture_cache = value; }

		Cache& GetCache() { return m_cache; }
		//System::Proxy<System::Object> GetDiffuseTextureCache() { return m_cache.m_diffuse_texture_cache; }
		//System::Proxy<System::Object> GetNormalTextureCache() { return m_cache.m_normal_texture_cache; }
		//System::Proxy<System::Object> GetDiffuseTexture2Cache() { return m_cache.m_diffuse_texture_cache_2; }
		//System::Proxy<System::Object> GetHeightTextureCache() { return m_cache.m_height_texture_cache; }

	private:
		
		System::string m_diffuse_map;
		System::string m_normal_map;
		Math::vec4 m_diffuse_color;
		Math::vec4 m_specular_color;
		float m_specular_factor;
		System::string m_name;
		float m_ambient;
		float m_diffuse_intensity;
		float m_darkness;
		float m_diffuse_fresnel;
		float m_diffuse_fresnel_factor;
		float m_emit;
		Math::vec4 m_mirror_color;
		float m_roughness;
		float m_specular_intensity;
		float m_specular_index_of_refraction;
		float m_specular_slope;
		float m_translucency;		

		Cache m_cache;

		Material(const Material&);
		Material& operator = (const Material&);
	};

	typedef std::map<System::string, Material> Materials;
}

#endif	//	_H_PUNK_VIRTUAL_MATERIAL