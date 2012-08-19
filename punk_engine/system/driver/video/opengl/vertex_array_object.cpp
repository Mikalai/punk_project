#include <fstream>
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

	void VertexArrayObject::Bind(VertexAttributes attribs) const
	{
		impl_vao->Bind(attribs);
	}

	void VertexArrayObject::Unbind() const
	{
		impl_vao->Unbind();
	}

	void VertexArrayObject::Render()
	{		
		glDrawElements(impl_vao->m_primitive_type, impl_vao->m_index_count, GL_UNSIGNED_INT, 0);			
	}

	void VertexArrayObject::RenderInstanced(int count)
	{		
		glDrawElementsInstanced(impl_vao->m_primitive_type, impl_vao->m_index_count, GL_UNSIGNED_INT, 0, count);			
	}

	void VertexArrayObject::Init()
	{
		Cook();
		impl_vao->m_was_modified = false;
	}

	void VertexArrayObject::Cook()
	{
		//throw System::SystemError(L"Not implemented");
	}

	void* VertexArrayObject::MapVertexBuffer()
	{
		return impl_vao->MapVertexBuffer();
	}

	void VertexArrayObject::UnmapVertexBuffer()
	{
		impl_vao->UnmapVertexBuffer();
	}

	void VertexArrayObject::Save(std::ostream& stream)
	{
		impl_vao->Save(stream);
	}

	void VertexArrayObject::Load(std::istream& stream)
	{
		impl_vao->Load(stream);
	}

	void VertexArrayObject::SetVertexBuffer(const void* vbuffer, unsigned buffer_size, unsigned vertex_size)
	{
		impl_vao->SetVertexBuffer(vbuffer, buffer_size, vertex_size);
	}

	void VertexArrayObject::SetUpAttributes(VertexAttributes supported_by_context)
	{
		impl_vao->SetUpAttributes(supported_by_context);
	}

	void VertexArrayObject::SetPrimitiveType(int type)
	{
		impl_vao->SetPrimitiveType(type);
	}

	void VertexArrayObject::SetIndexBuffer(const void* ibuffer, unsigned size)
	{
		impl_vao->SetIndexBuffer(ibuffer, size);
	}

	void VertexArrayObject::SetMeshTransform(const Math::mat4& value)
	{
		impl_vao->SetMeshTransform(value);
	}

	const Math::mat4& VertexArrayObject::GetMeshTransform() const
	{
		return impl_vao->GetMeshTransform();
	}

	void VertexArrayObject::Cook(VertexAttributes components, GLenum primitive_type)
	{
		impl_vao->Cook(components, primitive_type);
	}

	void VertexArrayObject::FromFileVAO(const System::string& filename)
	{
		char file[1024];
		filename.ToANSI(file, 1024);
		std::ifstream stream(file, std::ios_base::binary);
		if (!stream.is_open())
			throw System::SystemError(L"File " + filename + L" was not opened");
		impl_vao.reset(new VertexArrayObjectImpl);
		impl_vao->Load(stream);
	}

	Math::BoundingBox& VertexArrayObject::GetBoundingBox()
	{
		return impl_vao->GetBoundingBox();
	}

	const Math::BoundingBox& VertexArrayObject::GetBoundingBox() const
	{
		return impl_vao->GetBoundingBox();
	}

	void VertexArrayObject::SetIndex(int index)
	{
		impl_vao->SetIndex(index);
	}

	int VertexArrayObject::GetIndex() const
	{
		return impl_vao->GetIndex();
	}

	void VertexArrayObject::SetSourceFile(const System::string& filename)
	{
		impl_vao->SetSourceFile(filename);
	}

	const System::string& VertexArrayObject::GetSourceFile() const
	{
		return impl_vao->GetSourceFile();
	}

}
