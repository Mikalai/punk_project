#ifndef STATIC_INFORMATION_H
#define STATIC_INFORMATION_H

#include <vector>
#include "../string/string.h"
#include "rtti.h"

namespace System
{
    class Buffer;
    class Object;

    class Factory
    {
    public:
        static Object* Create(unsigned id);
        static void Save(Buffer* buffer, const Object* o);
        static Object* Load(Buffer* buffer);
        static void Add(unsigned id, Object* (*F)());
        static void Add(unsigned id, void (*F)(Buffer*, const Object*));
        static void Add(unsigned id, void (*F)(Buffer*, Object*));
    private:
        static std::vector<Object*(*)()> m_creator;
        static std::vector<void (*)(Buffer*, const Object*)> m_saver;
        static std::vector<void (*)(Buffer*, Object*)> m_loader;
    };

    template<class T>
    struct StaticInormation
    {
        typedef std::vector<T*> InstanceCollection;
        StaticInormation<T>(const string& name, unsigned uid, void (*Save)(Buffer*, const Object*), void (*Load)(Buffer*, Object*), const Rtti* parent)
            : Type(name, uid, parent)
        {
            Factory::Add(Type.GetId(), T::Create);
            Factory::Add(Type.GetId(), Save);
            Factory::Add(Type.GetId(), Load);
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
