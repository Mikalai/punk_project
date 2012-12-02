#ifndef _H_PUNK_OPENGL_RENDERABLE
#define _H_PUNK_OPENGL_RENDERABLE

#include "../../../config.h"
#include "../../../system/logger.h"
#include "../../../system/smart_pointers/proxy.h"
#include "../../../utility/model/vertex_component.h"

namespace OpenGL
{
	class PUNK_ENGINE Renderable 
	{
	public:

		Renderable();

		virtual ~Renderable() {}

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

		virtual bool Save(std::ostream& stream) const;

		virtual bool Load(std::istream& stream);

		static System::Proxy<Renderable> CreateFromStream(std::istream& stream);
		static System::Proxy<Renderable> CreateFromFile(const System::string& path);

	protected:

		int m_primitive_type;
	};
}

#endif	//	_H_PUNK_OPENGL_RENDERABLE