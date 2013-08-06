#ifndef _H_PUNK_OPENGL_RENDEER
#define _H_PUNK_OPENGL_RENDEER

#include "../../../config.h"
#include <map>
#include <vector>

namespace GPU
{
	namespace OpenGL
	{
		class Batch;

		class RenderPass
		{			
		public:

			RenderPass(std::vector<Batch*> batches);
			~RenderPass();
			void Run();

		private:
			std::vector<Batch*> m_batches;
		};
	}
}

#endif	//	_H_PUNK_OPENGL_RENDEER