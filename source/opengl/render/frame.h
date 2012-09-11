#ifndef _H_PUNK_OPENGL_FRAME
#define _H_PUNK_OPENGL_FRAME

#include "../../config.h"
#include <list>
#include "../../system/profiler.h"

namespace OpenGL
{
	class RenderPass;
	
	class PUNK_ENGINE Frame
	{
		std::list<RenderPass*> m_render_passes;
		System::Profiler m_profiler;
	public:
		//	
		void Begin();
		//	at the end of the frame all passes will be deleted
		void AddRenderPass(RenderPass* pass);
		//	performs actual execution of the passes, e.g. rendering
		void End();		
	private:

		void Clear();
	};
}

#endif