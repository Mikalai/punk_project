#ifndef _H_PUNK_VIRTUAL_STATIC_MOTION_STRATEGY
#define _H_PUNK_VIRTUAL_STATIC_MOTION_STRATEGY

#include "motion_strategy.h"
#include "../../math/mat4.h"
#include "../../math/vec3.h"

namespace Virtual
{
	class PUNK_ENGINE StaticMotionStrategy : public MotionStrategy
	{
	public:
		StaticMotionStrategy();
		void SetAffineMatrix(const Math::mat4& matrix);
		const Math::mat4& GetAffineMatrix() const;
		Math::mat4& GetAffineMatrix();
		virtual bool Update(__int64 current_time_us, __int64 delta_us) { return true; }
		virtual ~StaticMotionStrategy();
	private:
	};
}

#endif	//	_H_PUNK_VIRTUAL_STATIC_MOTION_STRATEGY