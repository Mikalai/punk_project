#ifndef _H_PUNK_SKIN
#define _H_PUNK_SKIN

#include "../config.h"
#include <vector>
#include <map>
#include "../../math/smart_matrix.h"
#include "../../math/mat4.h"

namespace System
{
	class Buffer;
}

namespace Utility
{
	class Model;

	class LIB_UTILITY SkinAnimation
	{		
		Math::Matrix<float>			m_frame_values;
		Math::Matrix<Math::mat4>	m_animation;

	public:

		Math::mat4 GetGlobal(int frame, int index);
		void Save(System::Buffer& buffer);
		void Load(System::Buffer& buffer);

		int GetFramesCount() const;

		friend class Model;
	};
}

#endif