#ifndef SUPER_POSITION_H
#define SUPER_POSITION_H

#include "../era.h"
#include "../math/vec3.h"

namespace Common
{

class Location : public Attribute
{
public:
    Location();

    void SetPosition(const Math::vec3& value);
    const Math::vec3& GetPosition() const;

private:   
    Math::vec3 m_position;
    float q, rx, ry, rz;
    float sx, sy, sz;
};

bool HasLocation(Entity* p);

}

#endif // POSITION_H
