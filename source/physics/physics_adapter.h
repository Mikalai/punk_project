#ifndef _H_PUNK_PHYSICS_ADAPTER
#define _H_PUNK_PHYSICS_ADAPTER

namespace Math { class mat4; }

namespace Physics
{
    class Simulator;

	class Adapter
	{
	public:
		virtual void EnterPhysicalSimulator(Simulator* value) = 0;
		virtual void LeavePhysicalSimulator() = 0;
		virtual void SetTransform(const Math::mat4& value) = 0;
		virtual void GetTransform(Math::mat4& value) = 0;
	};
}

#endif // _H_PUNK_PHYSICS_ADAPTER
