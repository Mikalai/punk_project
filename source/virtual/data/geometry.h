#ifndef _H_PUNK_VIRTUAL_GEOMETRY
#define _H_PUNK_VIRTUAL_GEOMETRY

#include "../../config.h"
#include "../../system/object.h"
#include "../../math/module.h"

namespace Gpu { class Renderable; }

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
        Geometry();
        Geometry(const Geometry&) = delete;
        Geometry& operator = (const Geometry&) = delete;
		virtual ~Geometry();
        virtual Vertices& GetVertexArray() { throw; }
        virtual Normals& GetNormalArray() { throw; }
        virtual Faces& GetFaceArray() { throw; }
        virtual const Vertices& GetVertexArray() const { throw; }
        virtual const Normals& GetNormalArray() const { throw; }
        virtual const Faces& GetFaceArray() const { throw; }

        Math::BoundingBox& GetBoundingBox();
        const Math::BoundingBox& GetBoundingBox() const;
        Math::BoundingSphere& GetBoundingSphere();
        const Math::BoundingSphere& GetBoundingSphere() const;

    protected:

        Math::BoundingBox m_bbox;
        Math::BoundingSphere m_sphere;    

        PUNK_OBJECT(Geometry)

        friend void SaveGeometry(System::Buffer* buffer, const Object* o);
        friend void LoadGeometry(System::Buffer* buffer, Object* o);
	};

    PUNK_ENGINE_API void SaveGeometry(System::Buffer* buffer, const System::Object* o);
    PUNK_ENGINE_API void LoadGeometry(System::Buffer* buffer, System::Object* o);
}

#endif // _H_PUNK_VIRTUAL_GEOMETRY
