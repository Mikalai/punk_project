#if defined(USE_STATE) && defined(USE_ECONOMY)

#ifndef MONEY_H
#define MONEY_H

#include <map>
#include <string>
#include "entity.h"
#include "entityclass.h"

class Money;

class MoneyClass : public EntityClass
{
public:

    const std::string GetName() const;
    Money* Create(const std::string& name);
    void Destroy(Entity* value) override;

private:
    std::vector<Money*> m_items;
};

class Money : public Entity
{
public:

    const std::string& GetName() const;
    void SetName(const std::string& name);

private:
    Money(MoneyClass* c);
    friend class MoneyClass;

private:

    std::string m_money_name;
};

#endif // MONEY_H

#endif //   (USE_STATE && USE_ECONOMY)
