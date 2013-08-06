#include "action.h"
#include "../../system/logger.h"
#include "../../utility/descriptors/action_desc.h"
#include "animation.h"

namespace Virtual
{
	Action::Action()
	{
//		SetType(System::ObjectType::ACTION);
	}

	Action::~Action() {}

    void Action::Save(System::Buffer* buffer) const
    {
        System::CompoundObject::Save(buffer);
        buffer->WriteSigned32(m_start_frame);
        buffer->WriteSigned32(m_end_frame);
        buffer->WriteString(m_name);
    }

    void Action::Load(System::Buffer* buffer)
    {
        System::CompoundObject::Load(buffer);
        m_start_frame = buffer->ReadSigned32();
        m_end_frame = buffer->ReadSigned32();
        m_name = buffer->ReadString();
    }

    void Action::SetName(System::string &value)
    {
        m_name = value;
    }

    const System::string& Action::GetName() const
    {
        return m_name;
    }
}
