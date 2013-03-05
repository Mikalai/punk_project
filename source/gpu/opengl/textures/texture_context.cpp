#include "texture_context.h"
#include "../gl/module.h"
#include "../../common/texture2d.h"

namespace GPU
{
	namespace OpenGL
	{
		TextureContext::TextureContext() 
		{
			memset(m_textures, 0, sizeof(m_textures));
		}

		TextureContext::~TextureContext()
		{

		}

		void TextureContext::Clear()
		{
			memset(m_textures, 0, sizeof(m_textures));
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
					m_textures[i] = nullptr;
				}
			}
		}

		void TextureContext::SetTexture(int slot, const Texture2D* map)
		{
			m_textures[slot] = map;
		}
	}
}