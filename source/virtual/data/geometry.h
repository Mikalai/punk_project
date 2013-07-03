#ifndef _H_PUNK_VIRTUAL_GEOMETRY
#define _H_PUNK_VIRTUAL_GEOMETRY

#include "../../config.h"
#include "../../system/object.h"
#include "../../math/module.h"

namespace GPU { class Renderable; }

namespace Physics
{
	class BulletShapeBody;
}

namespace Virtual
{
	class PUNK_ENGINE_API Geometry : public System::Object
	{
	public:
		typedef int FaceIndex;
		typedef std::vector<Math::vec3> Vertices;
		typedef std::vector<Math::vec3> Normals;
		typedef std::vector<Math::ivec3> Faces;

	public:
		virtual ~Geometry();
		virtual Vertices& GetVertexArray() = 0;
		virtual Normals& GetNormalArray() = 0;
		virtual Faces& GetFaceArray() = 0;
		virtual const Vertices& GetVertexArray() const = 0;
		virtual const Normals& GetNormalArray() const = 0;
		virtual const Faces& GetFaceArray() const = 0;

        Math::BoundingBox& GetBoundingBox();
        const Math::BoundingBox& GetBoundingBox() const;
        Math::BoundingSphere& GetBoundingSphere();
        const Math::BoundingSphere& GetBoundingSphere() const;

    protected:

        Math::BoundingBox m_bbox;
        Math::BoundingSphere m_sphere;
	};
}

#endif // _H_PUNK_VIRTUAL_GEOMETRY
