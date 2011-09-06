#ifndef _H_PUNK_TERRAIN
#define _H_PUNK_TERRAIN

#include "../driver/video/driver.h"

namespace Render
{
	class Terrain
	{
		Driver::Texture2D m_height_map;
		VertexArrayObject m_vao;
	public:
	};
}

#endif