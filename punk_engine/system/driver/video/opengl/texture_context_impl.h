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
		std::auto_ptr<Texture2D> m_diffuse_map;
		std::auto_ptr<Texture2D> m_normal_map;

		TextureContextImpl()
			: m_diffuse_map(0)
			, m_normal_map(0)
		{}

		TextureContextImpl(const TextureContextImpl& c)
			: m_diffuse_map(new Texture2D(*c.m_diffuse_map))
			, m_normal_map(new Texture2D(*c.m_normal_map))
		{}

		void Bind()
		{
			if (m_diffuse_map.get())
			{
				glActiveTexture(GL_TEXTURE0);
				m_diffuse_map->Bind();
			}

			if (m_normal_map.get())
			{
				glActiveTexture(GL_TEXTURE1);
				m_normal_map->Bind();
			}
		}

		void Unbind()
		{
			// place some usefull code here
		}
	};
}

#endif