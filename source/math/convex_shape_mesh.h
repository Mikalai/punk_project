#ifndef _H_PUNK_MATH_SHAPE_MESH
#define _H_PUNK_MATH_SHAPE_MESH

#include <vector>

#include "../config.h"
#include "vec3.h"
#include "bounding_box.h"
#include "bounding_shere.h"

namespace Math
{
	class PUNK_ENGINE_API ConvexShapeMesh
	{
	public:
		typedef std::vector<Math::vec3> PointsCollection;
		typedef std::vector<Math::ivec3> FacesCollection;
		typedef std::vector<Math::vec3> NormalsCollection;

	public:

		void SetPoints(const PointsCollection& value);
		void SetFaces(const FacesCollection& value) { m_faces = value; }
		void SetNormals(const NormalsCollection& value) { m_normals = value; }

		const PointsCollection& GetPoints() const { return m_points; }		
		PointsCollection& GetPoints() { return m_points; }		
		const FacesCollection& GetFaces() const { return m_faces; }
		FacesCollection& GetFaces() { return m_faces; }
		const NormalsCollection& GetNormals() const { return m_normals; }
		NormalsCollection& GetNormals() { return m_normals; }

		void Save(System::Buffer* buffer) const;
		void Load(System::Buffer* buffer);

		bool UpdateBoundingVolumes();

		const Math::BoundingBox& GetBoundingBox() const { return m_bbox; }
		const Math::BoundingSphere& GetBoundingSphere() const { return m_bsphere; }

	private:
		Math::BoundingBox m_bbox;
		Math::BoundingSphere m_bsphere;

		PointsCollection m_points;
		FacesCollection m_faces;
		NormalsCollection m_normals;
	};
}

#endif	//	_H_PUNK_MATH_SHAPE_MESH