#ifndef _H_PUNK_PHYSICAL_SIMULATOR
#define _H_PUNK_PHYSICAL_SIMULATOR

#include "../../config.h"

namespace Math
{
	template<class T> class Vector3;
}

namespace Render
{

}

namespace Utility
{
	struct RigidBodyDesc;
	class RigidBody;
	class ShapeBody;
	class Object;
	class Terrain;

	class PUNK_ENGINE PhysicalSimulator	
	{
	public:
		virtual void Update(float delta) = 0;
		virtual RigidBody* CreateRigidBody(RigidBodyDesc& desc) = 0;
		virtual void CreateDynamicShapeBody(Object& object) = 0;
		virtual void SetGravity(const Math::Vector3<float>& g) = 0;
		virtual void SetTerrain(Terrain& terrain) = 0;
		virtual void SetRender(void* drawer) = 0;
		virtual void Draw() = 0;
		virtual ~PhysicalSimulator() {}
		static PhysicalSimulator* Instance();
		static void Destroy();
	protected:
		virtual void Init() = 0;
		virtual void Clear() = 0;
	};
}

#endif