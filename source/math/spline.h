#ifndef SPLINE_H
#define SPLINE_H

#include "weighted_point.h"

namespace Math
{
    class Spline
    {
    public:
        Spline();
        void AddPoint(const WeightedPoint& value);
        void AddPoints(const std::vector<WeightedPoint>& value);
        float GetTotalLength() const;

        /**
         * @brief At return interpolated point
         * @param t From 0 to 1
         * @return
         */
        const WeightedPoint At(float t);

    private:
        void UpdateTotalLength();
    private:
        std::vector<WeightedPoint> m_points;
        float m_total_length;
    };
}

#endif // SPLINE_H
