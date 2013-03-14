#ifndef _H_PUNK_VIRTUAL_SKIN_GEOMETRY
#define _H_PUNK_VIRTUAL_SKIN_GEOMETRY

#include <vector>
#include <map>

#include "../../string/string.h"
#include "../../math/bounding_box.h"
#include "../../system/aop/aop.h"
#include "geometry.h"

namespace Virtual
{
	class PUNK_ENGINE SkinGeometry : public Geometry, public System::Aspect<SkinGeometry*, System::string>
	{
	public:
		typedef int FaceIndex;
		typedef std::vector<Math::vec3> Vertices;
		typedef std::vector<Math::vec3> Normals;	
		typedef std::vector<Math::ivec3> Faces;
		typedef std::map<int, std::map<System::string, float>> BoneWeights;
		typedef std::map<System::string, std::vector<Math::Vector4<Math::vec2>>> TextureMeshes;

	public:

		SkinGeometry();

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
		void SetBoneWeights(const BoneWeights& value) { m_bone_weights = value; }

		const Vertices& GetVertices() const { return m_vertices; }
		const Normals& GetNormals() const { return m_normals; }
		const Faces& GetFaces() const { return m_faces; }
		const TextureMeshes& GetTextureMeshes() const { return m_tex_coords; }
		const BoneWeights& GetBoneWeights() const { return m_bone_weights; }

		const Math::BoundingBox& GetBoundingBox() const { return m_bbox; }

		static SkinGeometry* CreateFromFile(const System::string& path);
		static SkinGeometry* CreateFromStream(std::istream& stream);

		void DropCache();
		bool IsCacheValid();
		void SetGPUBufferCache(Object* value);
		System::Object* GetGPUBufferCache() { return m_cache.m_gpu_buffer; }

		void SetWorldOffset(const Math::mat4& value) { m_world_offset = value; }
		const Math::mat4& GetWorldOffset() const { return m_world_offset; }

	private:
		Math::BoundingBox m_bbox;
		Vertices m_vertices;
		Normals m_normals;
		Faces m_faces;				
		TextureMeshes m_tex_coords;		
		BoneWeights m_bone_weights;		
		Math::mat4 m_world_offset;

		/**
		*	when cache is dropped data should be removed
		*/
		struct Cache
		{
			System::Object* m_gpu_buffer;

			Cache() 
				: m_gpu_buffer(nullptr) 
			{}
		};

		Cache m_cache;
	};
}

#endif	//	_H_PUNK_VIRTUAL_SKIN_GEOMETRY