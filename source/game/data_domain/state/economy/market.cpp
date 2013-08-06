#if defined(USE_STATE) && defined(USE_ECONOMY)

#include "market.h"

Market::Market(MarketClass* c)
    : Entity(c)
{
}

void Trade(Market *market, Entity *from, Entity *what, int count, Entity *to)
{

}

#endif  //  #if defined(USE_STATE) && defined(USE_ECONOMY)
