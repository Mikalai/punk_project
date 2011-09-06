#include "driver.h"
#include "texture_context.h"
#include "../../../../system/logger.h"
#include "texture2d_object.h"

namespace OpenGL
{
	TextureContext::TextureContext() : m_diffuse_map(0), m_normal_map(0)
	{
	}

	void TextureContext::Apply()
	{
		if (m_diffuse_map)
		{
			glActiveTexture(GL_TEXTURE0);
			m_diffuse_map->Bind();
		}
		else
		{
			System::Logger::GetInstance()->WriteError(L"Can't apply diffuse map", LOG_LOCATION);
		}

		if (m_normal_map)
		{
			glActiveTexture(GL_TEXTURE1);
			m_normal_map->Bind();
		}
		else
		{
			System::Logger::GetInstance()->WriteError(L"Can't apply normal map", LOG_LOCATION);
		}
	}

	void TextureContext::SetDiffuseMap(Texture2D* map)
	{
		m_diffuse_map = map;
	}

	void TextureContext::SetNormalMap(Texture2D* map)
	{
		m_normal_map = map;
	}
}