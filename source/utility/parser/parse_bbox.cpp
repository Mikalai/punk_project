#include "../../math/bounding_box.h"
#include "../../system/buffer.h"
#include "parse_functions.h"

namespace Utility
{
    bool ParseBoundingBox(System::Buffer& buffer, Math::BoundingBox& value)
    {
        CHECK_START(buffer);
        Math::vec3 p[8];
        for (int i = 0; i < 8; ++i)
            if (!ParseVector3f(buffer, p[i]))
                throw System::PunkInvalidArgumentException(L"Unable to parse bounding box");
        if (!value.Create(reinterpret_cast<const float*>(p), 8, sizeof(Math::vec3)))
            throw System::PunkInvalidArgumentException(L"Unable to make bounding box from points");
        CHECK_END(buffer);
        return true;
    }
}
