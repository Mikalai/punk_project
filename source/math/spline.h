#ifndef SPLINE_H
#define SPLINE_H

#include <vector>
#include "weighted_point.h"

namespace Math
{
    class PUNK_ENGINE_API Spline
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

        friend void SaveSpline(System::Buffer* buffer, const Spline& spline);
        friend void LoadSpline(System::Buffer* buffer, Spline& spline);
    };

    PUNK_ENGINE_API void SaveSpline(System::Buffer* buffer, const Spline& spline);
    PUNK_ENGINE_API void LoadSpline(System::Buffer* buffer, Spline& spline);
}

#endif // SPLINE_H
