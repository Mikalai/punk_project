#ifndef _H_PUNK_TEXTURE_CONTEXT
#define _H_PUNK_TEXTURE_CONTEXT

#include "../../config.h"
#include <memory>

namespace OpenGL
{
	class Texture2D;
	struct TextureContextImpl;

	class PUNK_ENGINE TextureContext
	{
		static const int MAX_TEXTURES = 32;
		const Texture2D* m_textures[MAX_TEXTURES];
	public:
		TextureContext();
		TextureContext(const TextureContext& tc);
		TextureContext& operator = (const TextureContext& tc);
		~TextureContext();

		void SetTexture(int slot, const Texture2D* map);

		void Bind();	
		void Unbind();
	};
}

#endif