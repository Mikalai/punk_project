#if defined(USE_STATE) && defined(USE_ECONOMY)

#ifndef MARKET_H
#define MARKET_H

#include "era.h"

class Money;

class MarketClass : public EntityClass
{

};

class Market : public Entity
{
public:
    Market(MarketClass* c);
    int GetPrice(Entity* e);
};

void ExchangeCurreny(Market* market, Entity* who, Money* from, int count);
void Trade(Market* market, Entity* from, Entity* what, int count, Entity* to);

#endif // MARKET_H

#endif  //  #if defined(USE_STATE) && defined(USE_ECONOMY)
