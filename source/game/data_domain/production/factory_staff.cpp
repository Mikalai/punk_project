#ifdef USE_PRODUCTION

#include "factory_staff.h"

FactoryStaff::FactoryStaff()
{

}

bool FactoryStaff::IsSatisfied() const
{
    for (auto it : m_required)
    {
        if (m_presents.at(it.first) < it.second)
            return false;
    }
    return true;
}

int FactoryStaff::GetPresent(const std::string &job) const
{
    auto it = m_presents.find(job);
    if (it == m_presents.end())
        return 0;
    return it->second;
}

int FactoryStaff::GetRequired(const std::string &job) const
{
    auto it = m_required.find(job);
    if (it == m_required.end())
        return 0;
    return it->second;
}

#endif  //  USE_PRODUCTION
