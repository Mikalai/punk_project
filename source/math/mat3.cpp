#include "../system/buffer.h"
#include "mat3.h"

namespace Math
{
    void mat3::Save(System::Buffer* buffer) const
    {
        for (int i = 0; i != 9; ++i)
        {
            buffer->WriteReal32(m[i]);
        }
    }

    void mat3::Load(System::Buffer* buffer)
    {
        for (int i = 0; i != 9; ++i)
        {
            m[i] = buffer->ReadReal32();
        }
    }
}
