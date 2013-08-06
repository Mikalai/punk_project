#include <iostream>
#include <string.h>
#include "pool_manager.h"
#include "pool.h"

namespace System
{
    Pool::Pool()
    {
    }

    Pool::~Pool()
    {
        Clear();
    }

    void* Pool::Alloc(size_t size)
    {
        if (m_free.empty())
        {
            std::cout << "Allocation requested for " << size << " bytes" << std::endl;
            void* result = malloc(size);
            memset(result, 0, size);
            return result;
        }
        void* result = m_free.front();
        memset(result, 0, size);
        m_free.pop_front();
        return result;
    }

    void Pool::Free(void* value)
    {
        //out_message() << "Free requested" << std::endl;
        m_free.push_back(value);
    }

    void Pool::Clear()
    {
        std::cout << "Clear pool" << std::endl;
        for (typename std::deque<void*>::iterator it = m_free.begin(); it != m_free.end(); ++it)
        {
            free(*it);
        }
        m_free.clear();
    }
}

