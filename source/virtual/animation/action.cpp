#include "action.h"
#include "../../engine_objects.h"
#include "../../system/logger.h"
#include "../../utility/descriptors/action_desc.h"
#include "animation.h"

namespace Virtual
{
    PUNK_OBJECT_REG(Action, "Virtual.Action", PUNK_ACTION, SaveAction, LoadAction, &System::CompoundObject::Info.Type);

	Action::Action()
	{
        Info.Add(this);
	}

    Action::~Action()
    {
        Info.Remove(this);
    }

    void SaveAction(System::Buffer *buffer, const System::Object *o)
    {
        System::SaveCompoundObject(buffer, o);
        const Action* a = Cast<const Action*>(o);
        buffer->WriteSigned32(a->m_start_frame);
        buffer->WriteSigned32(a->m_end_frame);
        System::SaveString(buffer, a->m_name);
    }

    void LoadAction(System::Buffer *buffer, System::Object *o)
    {
        System::LoadCompoundObject(buffer, o);
        Action* a = Cast<Action*>(o);
        a->m_start_frame = buffer->ReadSigned32();
        a->m_end_frame = buffer->ReadSigned32();
        System::SaveString(buffer, a->m_name);    }

    void Action::SetName(System::string &value)
    {
        m_name = value;
    }

    const System::string& Action::GetName() const
    {
        return m_name;
    }
}
