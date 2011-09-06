#ifndef _H_PUNK_TEXTURE_CONTEXT
#define _H_PUNK_TEXTURE_CONTEXT

#include "config.h"

namespace OpenGL
{
	class Texture2D;

	class LIB_OPENGL TextureContext
	{
		Texture2D* m_diffuse_map;
		Texture2D* m_normal_map;

	public:
		TextureContext();
		void SetDiffuseMap(Texture2D* map);
		void SetNormalMap(Texture2D* map);
		void Apply();
	};
}

#endif