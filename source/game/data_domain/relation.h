#ifndef RELATION_H
#define RELATION_H

#include <set>

class Entity;

class Relation
{
public:

    Relation();
    virtual ~Relation();

    void SetA(Entity* value);
    void SetB(Entity* value);

    Entity* GetA();
    const Entity* GetA() const;

    Entity* GetB();
    const Entity* GetB() const;

    void SetPower(int power);
    int GetPower() const;

private:
    int m_power;
    Entity* m_a;
    Entity* m_b;
};

#endif // RELATION_H
