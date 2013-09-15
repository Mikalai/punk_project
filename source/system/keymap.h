#ifndef KEYMAP_H
#define KEYMAP_H

#include <set>
#include <map>
#include <array>
#include "handler.h"

namespace System
{
    class KeyMap
    {
    public:
        typedef std::map<int, std::set<Handler>> ActionsCollection;

    public:
        void Add(int event, int key, Handler h);
        void Remove(int event, int key, Handler h);

        ActionsCollection& Actions(int value);
        const ActionsCollection& Actions(int value) const;

    private:
        std::array<ActionsCollection, System::EVENT_LAST_EVENT> m_actions;
    };
}

#endif // KEYMAP_H
