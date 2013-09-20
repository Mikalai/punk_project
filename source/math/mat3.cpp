#include "../system/buffer.h"
#include "quat.h"
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

    const mat3 mat3::CreateFromQuaternion(const quat& q)
    {
        float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
        x2 = q[0] + q[0];
        y2 = q[1] + q[1];
        z2 = q[2] + q[2];
        xx = q[0] * x2;   xy = q[0] * y2;   xz = q[0] * z2;
        yy = q[1] * y2;   yz = q[1] * z2;   zz = q[2] * z2;
        wx = q[3] * x2;   wy = q[3] * y2;   wz = q[3] * z2;
        mat3 mat;
        float* m = &mat[0];
        m[0*3 + 0]=1.0f-(yy+zz); m[0*3 + 1]=xy-wz;        m[0*2 + 2]=xz+wy;
        m[1*3 + 0]=xy+wz;        m[1*3 + 1]=1.0f-(xx+zz); m[1*2 + 2]=yz-wx;
        m[2*3 + 0]=xz-wy;        m[2*3 + 1]=yz+wx;        m[2*2 + 2]=1.0f-(xx+yy);
        return mat;
    }
}

