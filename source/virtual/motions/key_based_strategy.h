#ifndef _H_PUNK_VIRTUAL_KEY_BASED_MOTION_STRATEGY
#define _H_PUNK_VIRTUAL_KEY_BASED_MOTION_STRATEGY

#include "motion_strategy.h"

namespace Virtual
{
	class AnimationMixer;
}

namespace Virtual
{
	class KeyBasedMotionStrategy : public MotionStrategy
	{
		std::auto_ptr<AnimationMixer> m_Mixer;
		__int64 m_current_time_us;
	public:		
		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);
		virtual bool GetLocalTransform(Math::Matrix4x4<float>& value);
		virtual bool SetLocalTransform(const Math::Matrix4x4<float>& value);
		virtual bool Update(__int64 current_time_us, __int64 delta_us);
		virtual ~KeyBasedMotionStrategy();
	};
}

#endif	//	_H_PUNK_VIRTUAL_KEY_BASED_MOTION_STRATEGY