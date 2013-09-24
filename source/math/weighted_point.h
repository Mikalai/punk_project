#ifndef WEIGHTED_POINT_H
#define WEIGHTED_POINT_H

#include "vec4.h"

namespace Math
{
    class PUNK_ENGINE_API WeightedPoint
    {
    public:
        WeightedPoint();
        WeightedPoint(const vec4& value, float weight = 1);

        WeightedPoint& operator += (const WeightedPoint& value);
        WeightedPoint& operator -= (const WeightedPoint& value);
        WeightedPoint& operator *= (float value);
        WeightedPoint& operator /= (float value);

        //  TODO: implementation requires refinment
        float Length() const;

        void SetWeight(float value);
        float GetWeight() const;

        void SetPoint(const vec4& value);
        const vec4& GetPoint() const;

    private:
        float m_weight;
        vec4 m_point;

        friend void SaveWeightedPoint(System::Buffer* buffer, const WeightedPoint& value);
        friend void LoadWeightedPoint(System::Buffer* buffer, WeightedPoint& value);
    };

    PUNK_ENGINE_API const WeightedPoint operator + (const WeightedPoint& l, const WeightedPoint& r);
    PUNK_ENGINE_API const WeightedPoint operator - (const WeightedPoint& l, const WeightedPoint& r);
    PUNK_ENGINE_API const WeightedPoint operator * (const WeightedPoint& l, float r);
    PUNK_ENGINE_API const WeightedPoint operator * (float l, const WeightedPoint& r);
    PUNK_ENGINE_API const WeightedPoint operator / (const WeightedPoint& l, float r);
    PUNK_ENGINE_API const WeightedPoint operator / (float l, const WeightedPoint& r);

    PUNK_ENGINE_API void SaveWeightedPoint(System::Buffer* buffer, const WeightedPoint& value);
    PUNK_ENGINE_API void LoadWeightedPoint(System::Buffer* buffer, WeightedPoint& value);
}

#endif // WEIGHTED_POINT_H
