#ifndef _H_PUNK_TERRAIN_RENDER
#define _H_PUNK_TERRAIN_RENDER

#include <memory>

#include "config.h"
#include "abstract_render.h"

namespace Utility { class Terrain; class Camera; }
namespace ImageModule { class Image; }

namespace Render
{
	class LIB_RENDER TerrainRender 
	{
	public:
		
		TerrainRender();
		TerrainRender(const TerrainRender& render);
		TerrainRender& operator = (const TerrainRender& render);
		virtual ~TerrainRender();

		void SetTerrain(Utility::Terrain* terrain);
		void SetDiffuseMap1(const ImageModule::Image& image);
		void SetDiffuseMap2(const ImageModule::Image& image);
		void Render(Utility::Camera* camera);
		void Init();
	private:
		struct TerrainRenderImpl;
		std::auto_ptr<TerrainRenderImpl> impl_terrain_render;
	};
}

#endif
