#ifndef _H_PUNK_TERRAIN_RENDER
#define _H_PUNK_TERRAIN_RENDER

#include <memory>

#include "config.h"
#include "abstract_render.h"
#include "../system/driver/video/driver.h"

namespace Utility { class Terrain; class Camera; }
namespace ImageModule { class Image; }

namespace OpenGL { class Texture2D; }
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
		void SetDiffuseMap1(OpenGL::Texture2D* image);
		void SetDiffuseMap2(OpenGL::Texture2D* image);
		void Render(Utility::Camera* camera);
		OpenGL::Texture2D* GetHeightMap();
		void Init();

	private:
		struct TerrainRenderImpl;
		std::auto_ptr<TerrainRenderImpl> impl_terrain_render;
	};
}

#endif
