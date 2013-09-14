#ifndef H_PUNK_MATH_SPHERICAL_H
#define H_PUNK_MATH_SPHERICAL_H

#include <array>

namespace Math
{
    class SphericalCoordinate
    {
    public:
        using real = float;
        SphericalCoordinate();
        SphericalCoordinate(real phi, real theta);
        SphericalCoordinate(real phi, real theta, real r);

        real Phi() const;
        void Phi(real value);

        real  Theta() const;
        void Theta(real value);

        real R() const;
        void R(real value);

    private:
        std::array<real, 3> m_v;
    };

    inline SphericalCoordinate::real SphericalCoordinate::Phi() const
    {
        return m_v[0];
    }

    inline void SphericalCoordinate::Phi(real value)
    {
        m_v[0] = value;
    }

    inline SphericalCoordinate::real  SphericalCoordinate::Theta() const
    {
        return m_v[1];
    }

    inline void SphericalCoordinate::Theta(real value)
    {
        m_v[1] = value;
    }

    inline SphericalCoordinate::real SphericalCoordinate::R() const
    {
        return m_v[2];
    }

    inline void SphericalCoordinate::R(SphericalCoordinate::real value)
    {
        m_v[2] = value;
    }

}

#endif // H_PUNK_MATH_SPHERICAL_H
