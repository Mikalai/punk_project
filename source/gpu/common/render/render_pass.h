#ifndef _H_PUNK_RENDER_PASS
#define _H_PUNK_RENDER_PASS

#include "../../../config.h"
#include <map>
#include <vector>

namespace Gpu
{
	class Batch;    
	class VideoDriver;
	class Texture2D;
	class Renderable;
	class CoreState;

	class RenderPass
	{
	public:
		RenderPass(VideoDriver* driver, std::vector<Batch*> batches);
		~RenderPass();
		void Run();

	private:
		VideoDriver* m_driver;
		std::vector<Batch*> m_batches;
		Texture2D* m_shadow_map;

		void SetUpShadowMap();
		void GenerateShadowMap(std::vector<Batch*>& batches);
		void OnePass(Renderable* renderable, CoreState* state);
	};

}

#endif	//	_H_PUNK_OPENGL_RENDEER
