#ifndef _H_PUNK_TEXTURE_CONTEXT
#define _H_PUNK_TEXTURE_CONTEXT

#include "../../../config.h"
#include "../../../system/poolable.h"

#include <memory>

namespace GPU
{
	namespace OpenGL
	{
		class Texture2D;
		struct TextureContextImpl;

		class PUNK_ENGINE TextureContext : public System::Poolable<TextureContext>
		{
		public:
			TextureContext();
			~TextureContext();

			void SetTexture(int slot, const Texture2D* map);
			void Clear();

			void Bind();	
			void Unbind();
		private:
			static const int MAX_TEXTURES = 32;
			//	this pointers should not be deleted in destructor
			const Texture2D* m_textures[MAX_TEXTURES];
		private:
			TextureContext(const TextureContext& tc);
			TextureContext& operator = (const TextureContext& tc);
		};
	}
}

#endif