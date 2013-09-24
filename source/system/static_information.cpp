#include <memory>
#include "object.h"
#include "buffer.h"
#include "static_information.h"

namespace System
{
    std::vector<Object*(*)()> Factory::m_creator;
    std::vector<void (*)(Buffer*, const Object*)> Factory::m_saver;
    std::vector<void (*)(Buffer*, Object*)> Factory::m_loader;

    Object* Factory::Create(unsigned id)
    {
        return m_creator[id]();
    }

    void Factory::Save(Buffer* buffer, const Object* o)
    {
        m_saver[o->GetType()->GetId()](buffer, o);
    }

    Object* Factory::Load(Buffer* buffer)
    {
        unsigned code = buffer->ReadUnsigned32();
        std::unique_ptr<Object> o(m_creator[code]());
        m_loader[code](buffer, o.get());
        return o.release();
    }

    void Factory::Add(unsigned id, Object* (*F)())
    {
        if (id == 0)
            return;
        if (id >= m_creator.size())
            m_creator.resize(id);
        m_creator[id-1] = F;
    }

    void Factory::Add(unsigned id, void (*F)(Buffer*, const Object*))
    {
        if (id == 0)
            return;
        if (id >= m_saver.size())
            m_saver.resize(id);
        m_saver[id-1] = F;
    }

    void Factory::Add(unsigned id, void (*F)(Buffer*, Object*))
    {
        if (id == 0)
            return;
        if (id >= m_loader.size())
            m_loader.resize(id);
        m_loader[id-1] = F;
    }
}
