#if defined(USE_STATE) && defined(USE_ECONOMY)

#ifndef FINANCIALSYSTEM_H
#define FINANCIALSYSTEM_H

#include "entity.h"
#include "entityclass.h"

class Money;
class FinancialSystem;

class FinancialSystemClass : public EntityClass
{
public:

    FinancialSystem* Create(const std::string, Money* money);

    void Destroy(Entity *value) override;
};

class FinancialSystem : public Entity
{
public:
    void SetReserveRatio(int value);
    int GetReserveRatio() const;

    void ModifyReserveRatio(int value);

    int GetMoneyQuantity() const;
    void ModifyMoneyQuantity(int value);

    void Update(float dt);

private:
        FinancialSystem(FinancialSystemClass* c);

private:
    //  total amount of available money. Amount of moved to public sector.
    int m_public_sector;
    //  1 .. 100
    int m_reserve_ratio;
};

#endif // FINANCIALSYSTEM_H

#endif //  #if defined(USE_STATE) && defined(USE_ECONOMY)
