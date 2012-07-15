#include <assert.h>
#include "static_object.h"
#include "static_object_impl.h"
#include "../../../../utility/model/static_mesh.h"

namespace OpenGL
{
	StaticObject::StaticObject()
	{
		impl_vao.reset(new StaticObjectImpl());
	}

	StaticObject::StaticObject(const StaticObject& quad)
	{
		impl_vao.reset(new StaticObjectImpl(static_cast<const StaticObjectImpl&>(*quad.impl_vao)));
	}

	StaticObject& StaticObject::operator = (const StaticObject& quad)
	{
		StaticObject temp(quad);
		std::swap(impl_vao, temp.impl_vao);
		return *this;
	}

	void StaticObject::SetStaticObject(Utility::StaticMesh* mesh)
	{
		assert(mesh != 0 && "Can't work when mesh is null"__FUNCSIG__);

		impl_vao->SetMeshTransform(mesh->GetMeshOffset());
		static_cast<StaticObjectImpl&>(*impl_vao).m_object = mesh;
	}

	void StaticObject::Cook()
	{
		StaticObjectImpl& impl = static_cast<StaticObjectImpl&>(*impl_vao);
		Utility::StaticMesh* mesh = impl.m_object;		
		impl_vao->SetVertexBuffer(mesh->GetVertexBuffer(), mesh->GetVertexBufferSize(), mesh->GetOneVertexSize());
		impl_vao->SetIndexBuffer(mesh->GetIndexBuffer(), mesh->GetIndexBufferSize());
		int components = VERTEX_NONE;
		int code = mesh->GetVertexComponentCode();
		if (code & Utility::COMPONENT_POSITION)
			components |= VERTEX_POSITION;
		if (code & Utility::COMPONENT_TANGENT)
			components |= VERTEX_TANGENT;
		if (code & Utility::COMPONENT_BITANGENT)
			components |= VERTEX_BITANGENT;
		if ((code & Utility::COMPONENT_BONE_ID) && (code & Utility::COMPONENT_BONE_WEIGHT))
			components |= VERTEX_BONE;
		if (code & Utility::COMPONENT_NORMAL)
			components |= VERTEX_NORMAL;
		if (code & Utility::COMPONENT_TEXTURE)
			components |= VERTEX_TEXTURE_0;		
		impl_vao->Cook(components, GL_TRIANGLES);/**/
	}
}