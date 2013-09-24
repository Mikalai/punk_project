#include "perspective_decoder.h"
#include "vec3.h"
#include "mat4.h"
#include "plane.h"
#include "frustum_plane.h"

namespace Math
{
    PerspectiveDecoder::PerspectiveDecoder(const mat4 &value)
        : m_value(value)
    {
    }

    float PerspectiveDecoder::GetFovX() const
    {
        float fovx = atan(1.0 / m_value[0]) * 2.0f; //  TODO: Not sure
        return fovx;
    }

    float PerspectiveDecoder::GetFovY() const
    {
        float fovy = atan(1.0 / m_value[5]) * 2.0f;
        return fovy;
    }

    float PerspectiveDecoder::GetNearZ() const
    {
        float n = m_value[14] / (m_value[10] - 1.0f);
        return n;
    }

    float PerspectiveDecoder::GetFarZ() const
    {
        float f = m_value[14] / (1.0f + m_value[10]);
        return f;
    }

    float PerspectiveDecoder::GetWidthToHeightAspectRatio() const
    {
        float a = m_value[5] / m_value[0];
        return a;
    }

    const Plane PerspectiveDecoder::GetPlane(FrustumPlane value)
    {
        Math::vec4 v;
        switch (value)
        {
        case FrustumPlane::Bottom:
            v = m_value.GetRow(3) + m_value.GetRow(1);
            break;
        case FrustumPlane::Far:
            v = m_value.GetRow(3) - m_value.GetRow(2);
            break;
        case FrustumPlane::Left:
            v = m_value.GetRow(3) + m_value.GetRow(0);
            break;
        case FrustumPlane::Near:
            v = m_value.GetRow(3) + m_value.GetRow(2);
            break;
        case FrustumPlane::Right:
            v = m_value.GetRow(3) - m_value.GetRow(0);
            break;
        case FrustumPlane::Top:
            v = m_value.GetRow(3) - m_value.GetRow(1);
            break;
        default:
            return Plane();
        }
        Plane result;
        float l = vec3(v.XYZ()).Length();
        vec3 n = v.XYZ() / l;
        float dst = v.W() / l;
        result.Set(n, dst);
        return result;
    }


}
