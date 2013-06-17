#ifndef PUNK_AI_CURVEPATH_H
#define PUNK_AI_CURVEPATH_H

#include "../system/aop/aop.h"
#include "../system/object.h"
#include "../math/spline.h"
#include "../math/curve.h"

namespace AI
{
    class PUNK_ENGINE_API CurvePath : public Math::Curve, public System::Object, public System::Aspect<CurvePath*, System::string>
    {
    public:
        CurvePath();
    };
}

#endif // CURVEPATH_H
