#include "action.h"
#include "../../system/logger.h"
#include "../../utility/descriptors/action_desc.h"
#include "animation.h"

namespace Virtual
{
	bool Action::Save(std::ostream& stream) const
	{
		if (!System::Object::Save(stream))
		{
			out_error() << "Can't save action entity: " << m_name << std::endl;
			return false;
		}

		m_name.Save(stream);
		stream.write((char*)&m_start_frame, sizeof(m_start_frame));
		stream.write((char*)&m_end_frame, sizeof(m_end_frame));

		int flag = m_animations.size();
		stream.write((char*)&flag, sizeof(flag));
		for (auto anim : m_animations)
		{			
			anim->Save(stream);		
		}
		return true;
	}


}