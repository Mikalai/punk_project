#ifndef PUNK_AI_CURVEPATH_H
#define PUNK_AI_CURVEPATH_H

#include "../system/aop/aop.h"
#include "../system/object.h"
#include "../math/spline.h"
#include "../math/curve.h"

namespace AI
{
    class PUNK_ENGINE_API CurvePath : public Math::Curve, public System::Object
    {
    public:
        CurvePath();
        CurvePath(const CurvePath&) = delete;
        CurvePath& operator = (const CurvePath&) = delete;
        virtual ~CurvePath();

        void SetName(const System::string& value);
        const System::string& GetName() const;
    private:
        System::string m_name;
    private:
        PUNK_OBJECT(CurvePath);
    };
}

#endif // CURVEPATH_H
