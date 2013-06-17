#ifndef _H_PUNK_VIRTUAL_STATIC_GEOMETRY
#define _H_PUNK_VIRTUAL_STATIC_GEOMETRY

#include <vector>
#include <map>

#include "../../math/bounding_box.h"
#include "../../system/aop/aop.h"
#include "geometry.h"

namespace Virtual
{
    class PUNK_ENGINE_API StaticGeometry : public Geometry, public System::Aspect<StaticGeometry*, System::string>
	{
	public:
		typedef std::map<System::string, std::vector<Math::Vector4<Math::vec2>>> TextureMeshes;

	public:

		StaticGeometry();

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

		virtual Vertices& GetVertexArray() override { return m_vertices; }
		virtual Normals& GetNormalArray() override { return m_normals; }
		virtual Faces& GetFaceArray() override { return m_faces; }
		virtual const Vertices& GetVertexArray() const override { return m_vertices; }
		virtual const Normals& GetNormalArray() const override { return m_normals; }
		virtual const Faces& GetFaceArray() const override { return m_faces; }

		void SetVertices(const Vertices& value) { m_vertices = value; }
		void SetNormals(const Normals& value) { m_normals = value; }
		void SetFaces(const Faces& value) { m_faces = value; }
		void SetTextureMeshes(const TextureMeshes& value) { m_tex_coords = value; }

		const Vertices& GetVertices() const { return m_vertices; }
		const Normals& GetNormals() const { return m_normals; }
		const Faces& GetFaces() const { return m_faces; }
		const TextureMeshes& GetTextureMeshes() const { return m_tex_coords; }

		const Math::BoundingBox& GetBoundingBox() const { return m_bbox; }

		static StaticGeometry* CreateFromFile(const System::string& path);
		static StaticGeometry* CreateFromStream(std::istream& stream);

		void SetWorldOffset(const Math::mat4& value) { m_world_offset = value; }
		const Math::mat4& GetWorldOffset() const { return m_world_offset; }

	private:
		Math::BoundingBox m_bbox;
		Vertices m_vertices;
		Normals m_normals;
		Faces m_faces;		
		TextureMeshes m_tex_coords;		
		Math::mat4 m_world_offset;
	};
}

#endif
