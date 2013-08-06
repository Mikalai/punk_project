#if defined(USE_STATE) && defined(USE_ECONOMY)

#include <algorithm>
#include <memory>
#include "money.h"

const std::string MoneyClass::GetName() const
{
    return "Money";
}

void MoneyClass::Destroy(Entity *value)
{
    auto it = std::find(m_items.begin(), m_items.end(), dynamic_cast<Money*>(value));
    if (it != m_items.end())
        m_items.erase(it);

    Unregister(value);

    delete value;
}

Money* MoneyClass::Create(const std::string &name)
{
    std::auto_ptr<Money> result(new Money(this));
    result->SetName(name);

    Register(result.get());
    return result.release();
}

Money::Money(MoneyClass *c)
    : Entity(c)
{}

void Money::SetName(const std::string &name)
{
    m_money_name = name;
}

#endif//    #if defined(USE_STATE) && defined(USE_ECONOMY)
