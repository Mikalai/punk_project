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
	class State;
	class PUNK_ENGINE Batch : public System::Poolable<Batch>
	{		
	public:
		~Batch();
		//System::Proxy<State> m_state;
		System::Proxy<Renderable> m_renderable;
	};
}

#endif	//	_H_PUNK_OPENGL_BATCH
