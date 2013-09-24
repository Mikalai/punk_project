#ifndef CURVE_H
#define CURVE_H

#include "../config.h"
#include <vector>
#include "spline.h"

namespace Math
{
    class PUNK_ENGINE_API Curve
    {
    public:
        typedef std::vector<Spline> Splines;
    public:        
        Curve();

        void AddSpline(const Spline& value);
        float GetTotalLength() const;
        const Math::vec3 At(float t);

    private:
        Splines m_splines;
        float m_total_length;

        friend void SaveCurve(System::Buffer*, const Curve& o);
        friend void LoadCurve(System::Buffer*, Curve& o);
    };

    PUNK_ENGINE_API void SaveCurve(System::Buffer*, const Curve& o);
    PUNK_ENGINE_API void LoadCurve(System::Buffer*, Curve& o);
}

#endif // CURVE_H
