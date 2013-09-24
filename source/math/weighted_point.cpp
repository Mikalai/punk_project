#include "../system/buffer.h"
#include "weighted_point.h"

namespace Math
{
    WeightedPoint::WeightedPoint()
        : m_weight(1.0)
    {
    }

    WeightedPoint::WeightedPoint(const vec4 &value, float weight)
        : m_weight(weight)
        , m_point(value)
    {}

    WeightedPoint& WeightedPoint::operator += (const WeightedPoint& value)
    {
        m_point += value.m_point;
        m_weight += value.m_weight;
        return *this;
    }

    WeightedPoint& WeightedPoint::operator -= (const WeightedPoint& value)
    {
        m_point -= value.m_point;
        m_weight -= value.m_weight;
        return *this;
    }

    WeightedPoint& WeightedPoint::operator *= (float value)
    {
        m_point *= value;
        m_weight *= value;
        return *this;
    }

    WeightedPoint& WeightedPoint::operator /= (float value)
    {
        m_point /= value;
        m_weight /= value;
        return *this;
    }

    const WeightedPoint operator + (const WeightedPoint& l, const WeightedPoint& r)
    {
        WeightedPoint res(l);
        res += r;
        return res;
    }

    float WeightedPoint::Length() const
    {
        return m_point.Length();
    }

    void WeightedPoint::SetWeight(float value)
    {
        m_weight = value;
    }

    float WeightedPoint::GetWeight() const
    {
        return m_weight;
    }

    void WeightedPoint::SetPoint(const vec4& value)
    {
        m_point = value;
    }

    const vec4& WeightedPoint::GetPoint() const
    {
        return m_point;
    }


    PUNK_ENGINE_API const WeightedPoint operator - (const WeightedPoint& l, const WeightedPoint& r)
    {
        WeightedPoint res(l);
        res -= r;
        return res;
    }

    PUNK_ENGINE_API const WeightedPoint operator * (const WeightedPoint& l, float r)
    {
        WeightedPoint res(l);
        res *= r;
        return res;
    }

    PUNK_ENGINE_API const WeightedPoint operator * (float l, const WeightedPoint& r)
    {
        WeightedPoint res(r);
        res *= l;
        return res;
    }

    PUNK_ENGINE_API const WeightedPoint operator / (const WeightedPoint& l, float r)
    {
        WeightedPoint res(l);
        res /= r;
        return res;
    }

    PUNK_ENGINE_API const WeightedPoint operator / (float l, const WeightedPoint& r)
    {
        WeightedPoint res(r);
        res /= l;
        return res;
    }       

    void SaveWeightedPoint(System::Buffer* buffer, const WeightedPoint& value)
    {
        buffer->WriteReal32(value.m_weight);
        SaveVector4f(buffer, value.m_point);
    }

    void LoadWeightedPoint(System::Buffer* buffer, WeightedPoint& value)
    {
        value.m_weight = buffer->ReadReal32();
        LoadVector4f(buffer, value.m_point);
    }
}
