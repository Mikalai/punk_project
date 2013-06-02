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

//		void DropGPUCache();
//		bool IsGPUCacheValid();
//		void SetGPUBufferCache(GPU::Renderable* value);
//		GPU::Renderable* GetGPUBufferCache();

//		void DropPhysicsCache();
//		bool IsPhysicsCacheValid();
//		void SetPhysicsCache(System::Object* value);
//		System::Object* GetPhysicsCache();

//	private:

//		/**
//		*	When cache is dropped data should be completely deleted
//		*	It means that cache is the only storage of runtime data,
//		*	thus when geometry is destroyed it means no one will try
//		*	to use data stored here
//		*	Should be deleted in destructor
//		*/
//		struct Cache
//		{
//			GPU::Renderable* m_gpu_buffer;
//			System::Object* m_physics_buffer;

//			Cache()
//				: m_gpu_buffer(nullptr)
//				, m_physics_buffer(nullptr)
//			{}
//		};

//		Cache m_cache;
	};
}

#endif // _H_PUNK_VIRTUAL_GEOMETRY
