#ifndef _H_PUNK_OPENGL_RENDERABLE
#define _H_PUNK_OPENGL_RENDERABLE

#include "../../system/smart_pointers/module.h"
#include "../error/module.h"
#include "vertex_component.h"

namespace GPU
{
	class PUNK_ENGINE Renderable 
	{
	public:

		Renderable();

		virtual ~Renderable() {}

		virtual void Bind(VertexAttributes supported_by_context)
		{
			throw GPUException(L"Bind() not implemented");
		}

		virtual void Unbind()
		{
			throw GPUException(L"Unbind() not implemented");
		}

		virtual void Render()
		{
			throw GPUException(L"Load() not implemented");
		}

		/*virtual bool Save(std::ostream& stream) const;

		virtual bool Load(std::istream& stream);*/

		/*static System::Proxy<Renderable> CreateFromStream(std::istream& stream) = 0;
		static System::Proxy<Renderable> CreateFromFile(const System::string& path) = 0;*/

	protected:

		int m_primitive_type;
	};
}

#endif	//	_H_PUNK_OPENGL_RENDERABLE