#ifdef USE_FOOD

#ifndef FOODCLASS_H
#define FOODCLASS_H

#include "../era.h"

class FoodClass : public EntityClass
{
public:
    FoodClass(const std::string& name = "FoodClass");
};

#endif // FOODCLASS_H

#endif      // USE_FOOD
