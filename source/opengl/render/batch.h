#ifndef _H_PUNK_OPENGL_BATCH
#define _H_PUNK_OPENGL_BATCH

#include <list>
#include "../render_context/render_context_policy.h"
#include "../renderable/primitives/renderable.h"
#include "../../system/poolable.h"
#include "../../system/smart_pointers/handle.h"

namespace OpenGL
{	
	class TextureContext;
	class Texture2D;

	class PUNK_ENGINE Batch : public System::Poolable<Batch>
	{		
	public:
		~Batch();
		std::list<System::Handle<Texture2D>> m_textures;
		DummyRenderPolicy::DummyParameters* m_parameters;
		Renderable* m_renderable;
	};
}

#endif	//	_H_PUNK_OPENGL_BATCH