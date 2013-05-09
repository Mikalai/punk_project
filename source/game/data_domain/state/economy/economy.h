#if defined(USE_STATE) && defined(USE_ECONOMY)

#ifndef ECONOMY_H
#define ECONOMY_H

#include <map>
#include "era.h"

class Money;
class Economy;

class EconomyClass : public EntityClass
{
public:

    EconomyClass(const std::string& name);

    const std::string GetName() const { return m_name; }

    Economy* Create(const std::string& name);

    virtual void Destroy(Entity* value) = 0;

    virtual void Register(Entity* e);
    virtual void Unregister(Entity* e);

private:
    std::string m_name;
    static std::vector<Entity*> m_all_entities;

};

class EconomyStatistics
{
public:

    void RegisterPurchase(Entity* item, int count, int price);
    void RegisterMoneyTransfer(Entity* from, Entity* to, int count);
    void RegisterMoneyExchange(Money* from, int from_count, Money* to, int to_count, double ratio);

    int GetTotalPurchaseQuantity(const std::string& item_name);
    int GetTotalPurchaseQuantity(int item_code);
    double GetAveragePurchasePrice(const std::string& item_name);
    double GetAveragePurchasePrice(int item_code);

private:

    struct Transfer
    {
        Entity* item;
        int count;
        int price;
    };

    //  Items sold
    std::vector<Transfer> m_produced;
};

class Economy : public Entity
{
public:
    Economy(EconomyClass* c);

    void SetTargetInflationRate();
    int GetTargetInflationRate() const;
    void SetMoneyQuantity(int q);
    int GetMoneyQuantity(int q) const;
    int GetMonthInflationRate(int year, int month) const;
    int GetYearInflationRate(int year) const;
    int GetNominalGDP(int year) const;
    int GetRealGDP(int base_year, int year) const;
    int GetGDPDeflator(int year) const;


    //  Statistics begin
    void RegisterPurchase(int year, Entity* item, int count, int price);
    void RegisterMoneyTransfer(int year, Entity* from, Entity* to, int count);
    void RegisterMoneyExchange(int year, Money* from, int from_count, Money* to, int to_count, double ratio);

    int GetTotalPurchaseQuantity(int year, const std::string& item_name);
    int GetTotalPurchaseQuantity(int year, int item_code);
    double GetAveragePurchasePrice(int year, const std::string& item_name);
    double GetAveragePurchasePrice(int year, int item_code);
    //  Statistics end

private:
    std::map<int, EconomyStatistics> m_statistics;
    Money* m_money;
    int m_money_quantity;

    typedef int Year;
    typedef int Month;

};


Money* SelectEconomyMoney(Economy* e);
Economy* FindEconomy(Entity* e);
bool HasEconomy(Entity* e);
void SetEconomy(Entity* entity, Economy* economy);

#endif // ECONOMY_H

#endif  //  #if defined(USE_STATE) && defined(USE_ECONOMY)
