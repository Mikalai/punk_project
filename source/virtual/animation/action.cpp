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
		if (!System::CompoundObject::Save(stream))
			return (out_error() << "Can't save action entity" << std::endl, false);

		stream.write((char*)&m_start_frame, sizeof(m_start_frame));
		stream.write((char*)&m_end_frame, sizeof(m_end_frame));
		return true;
	}

	bool Action::Load(std::istream& stream) 
	{
		if (!System::CompoundObject::Load(stream))
			return (out_error() << "Can't load action entity" << std::endl, false);

		stream.read((char*)&m_start_frame, sizeof(m_start_frame));
		stream.read((char*)&m_end_frame, sizeof(m_end_frame));
		return true;
	}

	System::Proxy<Action> Action::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios::binary);
		if (!stream.is_open())
			return (out_error() << "Can't open file " << path << std::endl, System::Proxy<Action>(nullptr));
		return CreateFromStream(stream);
	}

	System::Proxy<Action> Action::CreateFromStream(std::istream& stream)
	{
		System::Proxy<Action> node(new Action);
		if (!node->Load(stream))
			return (out_error() << "Can't load node from file" << std::endl, System::Proxy<Action>(nullptr));
		return node;
	}
}