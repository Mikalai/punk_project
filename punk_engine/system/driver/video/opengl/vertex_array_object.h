#ifndef _H_PUNK_VERTEX_ARRAY_OBJECT
#define _H_PUNK_VERTEX_ARRAY_OBJECT

#include <memory>
#include "config.h"
#include "vertex_attributes.h"
#include "../../../serializable.h"
#include "../../../../math/bounding_box.h"

namespace OpenGL
{
	struct VertexArrayObjectImpl;

	class MODULE_OPENGL VertexArrayObject : public System::Serializable
	{						
	protected:
		std::auto_ptr<VertexArrayObjectImpl> impl_vao;
	public:
		VertexArrayObject();
		VertexArrayObject(const VertexArrayObject& vao);
		VertexArrayObject& operator = (const VertexArrayObject& vao);
		virtual ~VertexArrayObject();
		virtual void Save(std::ostream& stream);
		virtual void Load(std::istream& stream);
		void Bind(VertexAttributes m_supported_by_context) const;
		void Unbind() const;
		int GetIndexCount() const;		
		void Render();		
		void RenderInstanced(int count);		
		void Init();
		void* MapVertexBuffer();
		void UnmapVertexBuffer();

		void SetPrimitiveType(int type);
		void SetVertexBuffer(const void* vbuffer, unsigned buffer_size, unsigned vertex_size);
		void SetUpAttributes(VertexAttributes supported_by_context);
		void SetIndexBuffer(const void* ibuffer, unsigned size);
		void SetMeshTransform(const Math::mat4& value);
		const Math::mat4& GetMeshTransform() const;
		void Cook(VertexAttributes components, GLenum primitive_type);
		
		void FromFileVAO(const System::string& filename);

		Math::BoundingBox& GetBoundingBox();
		const Math::BoundingBox& GetBoundingBox() const;

		void SetIndex(int index);
		int GetIndex() const;
		void SetSourceFile(const System::string& filename);
		const System::string& GetSourceFile() const;
	protected:
		virtual void Cook();
	};

	typedef VertexArrayObject* VertexArrayObjectRef;
}

#endif
