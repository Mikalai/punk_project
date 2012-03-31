#ifndef _H_PUNK_VERTEX_ARRAY_OBJECT
#define _H_PUNK_VERTEX_ARRAY_OBJECT

#include <memory>
#include "config.h"

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
		void Bind() const;
		void Unbind() const;
		int GetIndexCount() const;		
		void Render();		
		void Init();
	protected:
		virtual void Cook();		
	};
}

#endif