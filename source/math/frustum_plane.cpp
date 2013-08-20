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

    bool IsAdjacent(FrustumPlane a, FrustumPlane b)
    {
        switch (a)
        {
        case FrustumPlane::Top:
            if (b == FrustumPlane::Bottom)
                return false;
            else
                return true;
        case FrustumPlane::Far:
            if (b == FrustumPlane::Near)
                return false;
            else
                return true;
        case FrustumPlane::Left:
            if (b == FrustumPlane::Right)
                return false;
            else
                return true;
        case FrustumPlane::Near:
            if (b == FrustumPlane::Far)
                return false;
            else
                return true;
        case FrustumPlane::Right:
            if (b == FrustumPlane::Left)
                return false;
            else
                return true;
        case FrustumPlane::Bottom:
            if (b == FrustumPlane::Top)
                return false;
            else
                return true;
        }
        return false;
    }
}
