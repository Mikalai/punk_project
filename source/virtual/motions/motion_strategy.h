#ifndef _H_PUNK_VIRTUAL_MOTION_STRATEGY
#define _H_PUNK_VIRTUAL_MOTION_STRATEGY

#include "../../config.h"
#include "../../system/object.h"

namespace Math
{
	template<class T> class Matrix4x4;
}

namespace Virtual
{
	class Transform;

	enum MotionStrategyType : char { MOTION_STRATEGY_TYPE_NONE, MOTION_STRATEGY_TYPE_STATIC };

	class PUNK_ENGINE MotionStrategy : public System::Object
	{
	public:
		MotionStrategy();
		void SetTargetTransform(Transform* value) { m_transform = value; }
		Transform* GetTargetTransform() { return m_transform; }
		const Transform* GetTargetTransform() const { return m_transform; }
		MotionStrategyType GetMotionStrategyType() const { return m_motion_type; }

		virtual bool Save(std::ostream& stream);
		virtual bool Load(std::istream& stream);
		virtual bool Update(__int64 current_time_us, __int64 delta_us) = 0;
		virtual ~MotionStrategy();

	protected:
		Transform* GetTransform() { return m_transform; }		
		const Transform* GetTransform() const { return m_transform; }
		void SetMotionStrategyType(MotionStrategyType value) { m_motion_type = value; }
	private:
		MotionStrategyType m_motion_type;
		Transform* m_transform;
	};	
}

#endif