#include "../system/buffer.h"
#include "quat.h"

namespace Math
{
    void quat::Save(System::Buffer* buffer) const
    {
        buffer->WriteReal32(Scalar());
        for (int i = 0; i != 3; ++i)
        {
            buffer->WriteReal32(Vector()[0]);
        }
    }

    void quat::Load(System::Buffer* buffer)
    {
        Scalar() = buffer->ReadReal32();
        for (int i = 0; i != 3; ++i)
        {
            Vector()[0] = buffer->ReadReal32();
        }
    }
}
