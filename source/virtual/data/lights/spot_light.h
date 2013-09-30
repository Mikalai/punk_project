#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "../light.h"

namespace Virtual
{
    class SpotLight : public Light
    {
    public:
        SpotLight();
        SpotLight(const SpotLight&) = delete;
        SpotLight& operator = (const SpotLight&) = delete;
        virtual ~SpotLight();

    private:

        PUNK_OBJECT(SpotLight)
    };

    PUNK_OBJECT_UTIL(SpotLight)
}

#endif // SPOT_LIGHT_H
