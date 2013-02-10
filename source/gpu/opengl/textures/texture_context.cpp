#include "texture_context.h"
#include "../gl/module.h"
#include "texture2d.h"

namespace GPU
{
	namespace OpenGL
	{
		TextureContext::TextureContext() 
		{
		}

		TextureContext::~TextureContext()
		{

		}

		void TextureContext::Clear()
		{
			for (int i = 0; i < MAX_TEXTURES; ++i)
			{
				m_textures[i].Release();
			}
		}

		void TextureContext::Bind()
		{
			for (int i = 0; i < MAX_TEXTURES; ++i)
			{
				if (m_textures[i].IsValid())
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
				if (m_textures[i].IsValid())
				{
					glActiveTexture(GL_TEXTURE0 + i);// place some usefull code here
					CHECK_GL_ERROR(L"Unable to activate GL_TEXTUREi");
					glBindTexture(GL_TEXTURE_2D, 0);
					CHECK_GL_ERROR(L"Unable to unbind");
				}
			}
		}

		void TextureContext::SetTexture(int slot, System::Proxy<Texture2D> map)
		{
			m_textures[slot] = map;
		}
	}
}