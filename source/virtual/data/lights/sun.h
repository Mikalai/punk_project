#ifndef PUNK_VIRTUAL_SUN_H
#define PUNK_VIRTUAL_SUN_H

#include "../../../config.h"
#include "../../../system/object.h"
#include "../../../math/vec3.h"
#include "../../../system/aop/aop.h"

namespace Virtual
{
    class PUNK_ENGINE_API Sun : public System::Object
    {
    public:
        Sun();
        Sun(const Sun&) = delete;
        Sun& operator = (const Sun&) = delete;
        virtual ~Sun();

        void SetEnergy(float value);
        float GetEnergy() const;
        void SetColor(const Math::vec3& value);
        const Math::vec3& GetColor() const;

        void SetName(const System::string& value);
        const System::string& GetName() const;

    private:
        float m_energy;
        Math::vec3 m_color;
        System::string m_name;

        PUNK_OBJECT(Sun)
    };

    PUNK_OBJECT_UTIL(Sun)
}

#endif // PUNK_VIRTUAL_SUN_H
