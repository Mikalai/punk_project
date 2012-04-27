#ifndef _H_PUNK_OPENGL_MODULE_TEXTURE_CONTEXT_IMPL
#define _H_PUNK_OPENGL_MODULE_TEXTURE_CONTEXT_IMPL

#include "texture_bind_target.h"
#include "texture2d.h"
#include "extensions.h"

#include <memory>


namespace OpenGL
{
	struct TextureContextImpl
	{
		const Texture2D* m_diffuse_map;
		const Texture2D* m_normal_map;

		TextureContextImpl()
			: m_diffuse_map(nullptr)
			, m_normal_map(nullptr)
		{}

		TextureContextImpl(const TextureContextImpl& c)
			: m_diffuse_map(c.m_diffuse_map)
			, m_normal_map(c.m_normal_map)
		{}

		void Bind()
		{
			if (m_diffuse_map)
			{
				glActiveTexture(GL_TEXTURE1);
				m_diffuse_map->Bind();
			}

			if (m_normal_map)
			{
				glActiveTexture(GL_TEXTURE0);
				m_normal_map->Bind();
			}
		}

		void Unbind()
		{
			for (int i = 0; i < 4; ++i)
			{
				glActiveTexture(GL_TEXTURE0 + i);// place some usefull code here
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}
	};
}

#endif