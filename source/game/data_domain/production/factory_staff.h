#ifdef USE_PRODUCTION

#ifndef FACTORYREQUIRENMENTS_H
#define FACTORYREQUIRENMENTS_H

#include <string>
#include <map>

class FactoryStaff
{
public:
    FactoryStaff();

    bool IsSatisfied() const;

    void Add(const std::string job, int count);

    int GetPresent(const std::string& job) const;
    int GetRequired(const std::string& job) const;

private:

    std::map<std::string, int> m_required;
    std::map<std::string, int> m_presents;

};

#endif // FACTORYREQUIRENMENTS_H

#endif  //  USE_PRODUCTION
