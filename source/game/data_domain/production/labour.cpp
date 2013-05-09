#ifdef USE_PRODUCTION

#include "labour.h"
#include "human.h"

Labour::Labour(Human& human)
    : m_human(human)
{
}

bool Labour::Ok()
{
    bool flag = true;

    flag &= m_human.m_alive;
    flag &= m_human.m_sleep;

    return flag;
}

#endif  //    USE_PRODUCTION
