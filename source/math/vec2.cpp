#include "vec2.h"
#include "../system/buffer.h"

namespace Math
{
    void vec2::Save(System::Buffer* buffer) const
    {
        for (int i = 0; i != 2; ++i)
        {
            buffer->WriteReal32(m_v[i]);
        }
    }

    void vec2::Load(System::Buffer* buffer)
    {
        for (int i = 0; i != 2; ++i)
        {
            m_v[i] = buffer->ReadReal32();
        }
    }

    void ivec2::Save(System::Buffer* buffer) const
    {
        for (int i = 0; i != 2; ++i)
        {
            buffer->WriteSigned32(m_v[i]);
        }
    }

    void ivec2::Load(System::Buffer* buffer)
    {
        for (int i = 0; i != 2; ++i)
        {
            m_v[i] = buffer->ReadSigned32();
        }
    }
}
