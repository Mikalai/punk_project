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

    private:
        Splines m_splines;
        float m_total_length;
    };
}

#endif // CURVE_H
