#ifndef _H_PUNK_TEXTURE_CONTEXT
#define _H_PUNK_TEXTURE_CONTEXT

#include "../../config.h"
#include "../../system/poolable.h"
#include "../../system/smart_pointers/handle.h"

#include <memory>

namespace OpenGL
{
	class Texture2D;
	struct TextureContextImpl;

	class PUNK_ENGINE TextureContext : public System::Poolable<TextureContext>
	{
		static const int MAX_TEXTURES = 32;
		System::Handle<Texture2D> m_textures[MAX_TEXTURES];
	public:
		TextureContext();
		TextureContext(const TextureContext& tc);
		TextureContext& operator = (const TextureContext& tc);
		~TextureContext();

		void SetTexture(int slot, System::Proxy<Texture2D> map);

		void Bind();	
		void Unbind();
	};
}

#endif