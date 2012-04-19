#ifndef _H_PUNK_VERTEX_ARRAY_OBJECT
#define _H_PUNK_VERTEX_ARRAY_OBJECT

#include <memory>
#include "config.h"
#include "vertex_attributes.h"

namespace OpenGL
{
	struct VertexArrayObjectImpl;

	class MODULE_OPENGL VertexArrayObject
	{						
	protected:
		std::auto_ptr<VertexArrayObjectImpl> impl_vao;
	public:
		VertexArrayObject();
		VertexArrayObject(const VertexArrayObject& vao);
		VertexArrayObject& operator = (const VertexArrayObject& vao);
		virtual ~VertexArrayObject();
		void Bind(VertexAttributes m_supported_by_context) const;
		void Unbind() const;
		int GetIndexCount() const;		
		void Render();		
		void Init();
		void* MapVertexBuffer();
		void UnmapVertexBuffer();
	protected:
		virtual void Cook();		
	};
}

#endif
