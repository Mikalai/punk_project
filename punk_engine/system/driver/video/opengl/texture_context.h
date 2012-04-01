#ifndef _H_PUNK_TEXTURE_CONTEXT
#define _H_PUNK_TEXTURE_CONTEXT

#include "config.h"
#include <memory>

namespace OpenGL
{
	class Texture2D;
	struct TextureContextImpl;

	class MODULE_OPENGL TextureContext
	{
		std::auto_ptr<TextureContextImpl> impl_tc;		
	public:
		TextureContext();
		TextureContext(const TextureContext& tc);
		TextureContext& operator = (const TextureContext& tc);
		~TextureContext();

		void SetDiffuseMap(Texture2D* map);
		void SetNormalMap(Texture2D* map);

		void Bind();	
		void Unbind();
	};
}

#endif