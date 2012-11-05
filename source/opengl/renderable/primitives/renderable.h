#ifndef _H_PUNK_OPENGL_RENDERABLE
#define _H_PUNK_OPENGL_RENDERABLE

#include "../../../config.h"
#include "../../../system/logger.h"
//#include "../../../system/object.h"
#include "../../../utility/model/vertex_component.h"

namespace OpenGL
{
	class PUNK_ENGINE Renderable 
	{
	public:

		virtual void Bind(Utility::VertexAttributes supported_by_context)
		{
			out_warning() << "Bind() not implemented" << std::endl;
		}

		virtual void Unbind()
		{
			out_warning() << "Unbind() not implemented" << std::endl;
		}

		virtual void Render()
		{
			out_warning() << "Load() not implemented" << std::endl;
		}

		virtual ~Renderable()
		{
		}
	};
}

#endif	//	_H_PUNK_OPENGL_RENDERABLE