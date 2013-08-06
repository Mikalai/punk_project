#include "../system/buffer.h"
#include "vec3.h"

namespace Math
{
    void vec3::Save(System::Buffer *buffer) const
    {
        for (int i = 0; i != 3; ++i)
        {
            buffer->WriteReal32(m_v[i]);
        }
    }

    void vec3::Load(System::Buffer *buffer)
    {
        for (int i = 0; i != 3; ++i)
        {
            m_v[i] = buffer->ReadReal32();
        }
    }

    void ivec3::Save(System::Buffer* buffer) const
    {
        for (int i = 0; i != 3; ++i)
        {
            buffer->WriteSigned32(m_v[i]);
        }
    }

    void ivec3::Load(System::Buffer* buffer)
    {
        for (int i = 0; i != 3; ++i)
        {
            m_v[i] = buffer->ReadSigned32();
        }
    }
}

