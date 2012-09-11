#include "texture_context.h"
#include "../extensions.h"
#include "texture2d.h"

namespace OpenGL
{
	TextureContext::TextureContext() 
	{
		memset(m_textures, 0, sizeof(m_textures));
	}

	TextureContext::TextureContext(const TextureContext& tc)
	{
		memcpy(m_textures, tc.m_textures, sizeof(m_textures));
	}

	TextureContext& TextureContext::operator= (const TextureContext& tc)
	{
		memcpy(m_textures, tc.m_textures, sizeof(m_textures));
		return *this;
	}

	TextureContext::~TextureContext()
	{

	}

	void TextureContext::Bind()
	{
		for (int i = 0; i < MAX_TEXTURES; ++i)
		{
			if (m_textures[i])
			{
				glActiveTexture(GL_TEXTURE0 + i);
				CHECK_GL_ERROR(L"Unable to activate GL_TEXTURE0+i");
				m_textures[i]->Bind();
			}
		}
	}

	void TextureContext::Unbind()
	{
		for (int i = 0; i < MAX_TEXTURES; ++i)
		{
			if (m_textures[i])
			{
				glActiveTexture(GL_TEXTURE0 + i);// place some usefull code here
				CHECK_GL_ERROR(L"Unable to activate GL_TEXTUREi");
				glBindTexture(GL_TEXTURE_2D, 0);
				CHECK_GL_ERROR(L"Unable to unbind");
			}
		}
	}

	void TextureContext::SetTexture(int slot, const Texture2D* map)
	{
		m_textures[slot] = map;
	}
}