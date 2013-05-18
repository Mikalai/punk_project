#ifndef _H_PUNK_OPENGL_BATCH
#define _H_PUNK_OPENGL_BATCH

#include <list>
#include "../../../system/poolable.h"

namespace GPU
{
	class CoreState;
	class Renderable;

	namespace OpenGL
	{			
		class PUNK_ENGINE Batch : public System::Poolable<Batch>
		{		
		public:
			~Batch();
			CoreState* m_state;
			Renderable* m_renderable;
		};
	}
}

#endif	//	_H_PUNK_OPENGL_BATCH
