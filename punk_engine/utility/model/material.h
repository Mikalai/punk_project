#ifndef _H_PUNK_MATERIAL
#define _H_PUNK_MATERIAL

#include "../config.h"
#include "../../math/vec4.h"
#include "../../system/string.h"

namespace Utility
{
	class LIB_UTILITY Material
	{
		System::string m_diffuse_map;
		System::string m_normal_map;
		Math::vec4 m_diffuse_color;
		Math::vec4 m_specular_color;
		float m_specular_factor;

	public:
		void SetDiffuseMap(const System::string& map);
		void SetNormalMap(const System::string& map);
		void SetDiffuseColor(const Math::vec4& color);
		void SetSpecularColor(const Math::vec4& color);
		void SetSpecularFactor(float value);

		const System::string& GetDiffuseMap() const;
		const System::string& GetNormalMap() const;
		const Math::vec4& GetDiffuseColor() const;
		const Math::vec4& GetSpecularColor() const;
		float GetSpecularFactor() const;
	};
}

#endif