#include <algorithm>
#include "skin_animation.h"
#include "../../system/system.h"
#include "../../math/math.h"

namespace Utility
{
	Math::mat4 SkinAnimation::GetGlobal(int frame_index, int index)
	{
		Math::mat4 m = m_animation.At(frame_index, index);
	//	m[12] = 0;
	//	m[13] = 0;
	//	m[14] = 0;
		return m;
	}

	int SkinAnimation::GetFramesCount() const
	{
		return m_frame_values.ColumnCount();
	}
}