#ifndef PERSPECTIVE_DECODER_H
#define PERSPECTIVE_DECODER_H

#include <cstdint>
#include "../config.h"

namespace Math
{
    class mat4;
    class Plane;

    enum class FrustumPlane : uint8_t;

    class PUNK_ENGINE_API PerspectiveDecoder
    {
    public:
        PerspectiveDecoder(const mat4& value);


        float GetFovX() const;
        float GetFovY() const;
        float GetNearZ() const;
        float GetFarZ() const;
        float GetWidthToHeightAspectRatio() const;

        const Plane GetPlane(FrustumPlane value);

    private:
        const mat4& m_value;
    };

}

#endif // PERSPECTIVE_DECODER_H
