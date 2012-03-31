#include "vertex_array_object.h"
#include "vertext_array_object_impl.h"

namespace OpenGL
{
	VertexArrayObject::VertexArrayObject()
		: impl_vao(new VertexArrayObjectImpl())
	{		
	}

	VertexArrayObject::VertexArrayObject(const VertexArrayObject& vao)
		: impl_vao(new VertexArrayObjectImpl(*vao.impl_vao))
	{
	}

	VertexArrayObject& VertexArrayObject::operator = (const VertexArrayObject& vao)
	{
		VertexArrayObject temp(vao);
		std::swap(impl_vao, temp.impl_vao);
		return *this;
	}

	VertexArrayObject::~VertexArrayObject()
	{
	}

	void VertexArrayObject::Bind() const
	{
		impl_vao->Bind();
	}

	void VertexArrayObject::Unbind() const
	{
		impl_vao->Unbind();
	}
	
	void VertexArrayObject::Render()
	{		
		impl_vao->Bind();
		//glDrawElements(GL_TRIANGLES, 600, GL_UNSIGNED_INT, 0);
		glDrawElementsInstanced(impl_vao->m_primitive_type, impl_vao->m_index_count, GL_UNSIGNED_INT, 0, 1);
		//glDrawElements(GL_TRIANGLES, impl_vao->m_index_count, GL_UNSIGNED_INT, 0);			
		impl_vao->Unbind();
	}

	void VertexArrayObject::Init()
	{
		Cook();
		impl_vao->m_was_modified = false;
	}

	void VertexArrayObject::Cook()
	{
		throw System::SystemError(L"Not implemented");
	}
}
