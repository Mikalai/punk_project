#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "../../../math/vec3.h"
#include "../light.h"

namespace Virtual
{
    class DirectionalLight : public Light
    {
    public:
        DirectionalLight();
        DirectionalLight(const DirectionalLight&) = delete;
        DirectionalLight& operator = (const DirectionalLight&) = delete;
        virtual ~DirectionalLight();

        virtual const Math::vec3 GetDirection() const { return m_direction; }
        virtual void SetDirection(const Math::vec3& value) { m_direction = value; }

        void SetColor(const Math::vec3& value) { m_color = value; }
        const Math::vec3& GetColor() const { return m_color; }

        void SetDistance(float value) { m_distance = value; }
        float GetDistance() const { return m_distance; }

        void SetEnergy(float value) { m_energy = value; }
        float GetEnergy() const { return m_energy; }

    private:
        Math::vec3 m_direction;
        Math::vec3 m_color;
        float m_distance;
        float m_energy;

        PUNK_OBJECT(DirectionalLight)
    };

    PUNK_OBJECT_UTIL(DirectionalLight)
}

#endif // DIRECTIONAL_LIGHT_H
