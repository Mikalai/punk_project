#include "frustum_plane.h"

namespace Math
{
    const System::string AsString(const FrustumPlane& value)
    {
        switch(value)
        {
        case FrustumPlane::Bottom:
        return L"Bottom";
        case FrustumPlane::Far:
        return L"Far";
        case FrustumPlane::Left:
        return L"Left";
        case FrustumPlane::Near:
        return L"Near";
        case FrustumPlane::Right:
        return L"Right";
        case FrustumPlane::Top:
        return L"Top";
        default:
        return L"Error";
        }
    }
}
