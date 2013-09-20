#ifndef STATIC_INFORMATION_H
#define STATIC_INFORMATION_H

#include <vector>
#include "../string/string.h"
#include "rtti.h"

namespace System
{
    class Object;

    class Factory
    {
    public:
        static Object* Create(unsigned id) { return m_creator[id](); }
        static void Add(unsigned id, Object* (*F)())
        {
            if (id == 0)
                return;
            if (id >= m_creator.size())
                m_creator.resize(id);
            m_creator[id-1] = F;
        }

    private:
        static std::vector<Object*(*)()> m_creator;
    };

    template<class T>
    struct StaticInormation
    {
        typedef std::vector<T*> InstanceCollection;
        StaticInormation<T>(const string& name, unsigned uid, const Rtti* parent)
            : Type(name, uid, parent)
        {
            Factory::Add(Type.GetId(), T::Create);
        }

        void Add(T* value)
        {
            value->SetLocalIndex(Instances.size());
            Instances.push_back(value);
        }

        void Remove(T* value)
        {
            T* o = Instances.back();
            Instances[value->GetLocalIndex()] = o;
            o->SetLocalIndex(value->GetLocalIndex());
            Instances.pop_back();
        }

        void DestroyAllInstances()
        {
            while (!Instances.empty())
            {
                delete Instances.back();
                // Instances.pop_back(); not required, because when
                //  destructor will be called, object will be popped automatically
            }
        }

        Rtti Type;
        InstanceCollection Instances;
    };    

    template<class T>
    T* HasInstance(const string& name)
    {
        for (auto o : T::Info.Instances)
        {
            if (o->Name() == name)
                return o;
        }
        return nullptr;
    }
}

#endif // STATIC_INFORMATION_H
