#include "../system/buffer.h"
#include "mat2.h"

namespace Math
{
    void mat2::Save(System::Buffer *buffer) const
    {
        for (int i = 0; i != 4; ++i)
        {
            buffer->WriteReal32(m[i]);
        }
    }

    void mat2::Load(System::Buffer *buffer)
    {
        for (int i = 0; i != 4; ++i)
        {
            m[i] = buffer->ReadReal32();
        }
    }
}
