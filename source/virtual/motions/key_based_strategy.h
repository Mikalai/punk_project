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
		std::unique_ptr<AnimationMixer> m_Mixer;
		int64_t m_current_time_us;
	public:
		virtual void Save(System::Buffer* buffer) const;
		virtual void Load(System::Buffer* buffer);
		virtual bool GetLocalTransform(Math::Matrix4x4<float>& value);
		virtual bool SetLocalTransform(const Math::Matrix4x4<float>& value);
		virtual bool Update(int64_t current_time_us, int64_t delta_us);
		virtual ~KeyBasedMotionStrategy();
	};
}

#endif	//	_H_PUNK_VIRTUAL_KEY_BASED_MOTION_STRATEGY
