#ifndef _H_PUNK_RENDER_BBOX
#define _H_PUNK_RENDER_BBOX

#include "config.h"
#include "../system/driver/video/driver.h"
#include "../system/system.h"

namespace Render
{
	class LIB_RENDER BBoxRender
	{		
		OpenGL::Line line;
	public:	
		void Render(const Math::BoundingBox& bbox, const Math::mat4& worl, const Math::mat4& view, const Math::mat4& proj);
		void RenderAABB(const Math::BoundingBox& bbox, const Math::mat4& worl, const Math::mat4& view, const Math::mat4& proj);
	};
}

#endif
