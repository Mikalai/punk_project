#include "animation_desc.h"
#include "../../system/logger.h"

namespace Utility
{
	std::wostream& AnimationDesc::out_formatted(std::wostream& stream)
	{
		stream << Tab() << typeid(*this).name() << std::endl;
		Tab::Inc();
		stream << Tab() << "Is bone: " << m_is_bone_anim << std::endl;
		if (m_is_bone_anim)
			stream << Tab() << "Bone name: " << m_bone_name.Data() << std::endl;
		stream << Tab() << "Position track: " << std::endl;
		m_pos_track.out_formatted(stream) << std::endl;
		stream << Tab() << "Rotation track: " << std::endl;
		m_rot_track.out_formatted(stream) << std::endl;
		stream << Tab::Dec() << typeid(*this).name();
		return stream;
	}
}