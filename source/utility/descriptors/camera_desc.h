#ifndef _H_PUNK_UTILITY_CAMERA_DESC
#define _H_PUNK_UTILITY_CAMERA_DESC

#include "../../string/string.h"

namespace Utility
{
	class CameraDesc
	{
	public:
		System::string m_name;
		System::string m_type;
		float m_fov;
		float m_near;
		float m_far;
		float m_focus;
		float m_scale;

		std::wostream& out_formatted(std::wostream& stream);
	};
}

#endif	//	_H_PUNK_UTILITY_CAMERA_DESC