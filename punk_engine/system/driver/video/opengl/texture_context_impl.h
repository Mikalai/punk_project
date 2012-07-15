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
		const Texture2D* m_diffuse_map_1;
		const Texture2D* m_diffuse_map_2;
		const Texture2D* m_normal_map;

		TextureContextImpl()
			: m_diffuse_map_1(nullptr)
			, m_diffuse_map_2(nullptr)
			, m_normal_map(nullptr)
		{}

		TextureContextImpl(const TextureContextImpl& c)
			: m_diffuse_map_1(c.m_diffuse_map_1)
			, m_diffuse_map_2(c.m_diffuse_map_2)
			, m_normal_map(c.m_normal_map)
		{}

		void Bind()
		{
			if (m_diffuse_map_1)
			{
				glActiveTexture(GL_TEXTURE0);
				CHECK_GL_ERROR(L"Unable to activate GL_TEXTURE0");
				m_diffuse_map_1->Bind();
			}

			if (m_diffuse_map_2)
			{
				glActiveTexture(GL_TEXTURE1);
				CHECK_GL_ERROR(L"Unable to activate GL_TEXTURE1");
				m_diffuse_map_2->Bind();
			}

			if (m_normal_map)
			{
				glActiveTexture(GL_TEXTURE2);
				CHECK_GL_ERROR(L"Unable to activate GL_TEXTURE2");
				m_normal_map->Bind();
			}
		}

		void Unbind()
		{
			for (int i = 0; i < 4; ++i)
			{
				glActiveTexture(GL_TEXTURE0 + i);// place some usefull code here
				CHECK_GL_ERROR(L"Unable to activate GL_TEXTUREi");
				glBindTexture(GL_TEXTURE_2D, 0);
				CHECK_GL_ERROR(L"Unable to unbind");
			}
		}
	};
}

#endif