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
	class TransformNode;

	enum MotionStrategyType : char { MOTION_STRATEGY_TYPE_NONE, MOTION_STRATEGY_TYPE_STATIC };

	class PUNK_ENGINE_API MotionStrategy : public System::Object
	{
	public:
		MotionStrategy();
		void SetTargetTransform(TransformNode* value) { m_transform = value; }
		TransformNode* GetTargetTransform() { return m_transform; }
		const TransformNode* GetTargetTransform() const { return m_transform; }
		MotionStrategyType GetMotionStrategyType() const { return m_motion_type; }

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);
		virtual bool Update(int64_t current_time_us, int64_t delta_us) = 0;
		virtual ~MotionStrategy();

	protected:
		TransformNode* GetTransform() { return m_transform; }		
		const TransformNode* GetTransform() const { return m_transform; }
		void SetMotionStrategyType(MotionStrategyType value) { m_motion_type = value; }
	private:
		MotionStrategyType m_motion_type;
		TransformNode* m_transform;
	};	
}

#endif