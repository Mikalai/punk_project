#include "action.h"
#include "../../system/logger.h"
#include "../../utility/descriptors/action_desc.h"
#include "animation.h"

namespace Virtual
{
	Action::Action()
	{
		SetType(System::ObjectType::ACTION);
	}

	Action::~Action() {}

	bool Action::Save(std::ostream& stream) const
	{
		System::CompoundObject::Save(stream);

		stream.write((char*)&m_start_frame, sizeof(m_start_frame));
		stream.write((char*)&m_end_frame, sizeof(m_end_frame));
		return true;
	}

	bool Action::Load(std::istream& stream) 
	{
		System::CompoundObject::Load(stream);

		stream.read((char*)&m_start_frame, sizeof(m_start_frame));
		stream.read((char*)&m_end_frame, sizeof(m_end_frame));
		return true;
	}
}