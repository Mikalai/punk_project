#ifndef _H_PUNK_OPENGL_BATCH
#define _H_PUNK_OPENGL_BATCH

#include <list>
#include "../render_context/render_context_policy.h"
#include "../renderable/data/renderable.h"

namespace OpenGL
{	
	class TextureContext;
	class Texture2D;

	class PUNK_ENGINE Batch
	{		
	public:
		~Batch();
		std::list<Texture2D*> m_textures;
		DummyRenderPolicy::DummyParameters* m_parameters;
		Renderable* m_renderable;
	};
}

#endif	//	_H_PUNK_OPENGL_BATCH