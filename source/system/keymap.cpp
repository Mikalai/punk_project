#include "keymap.h"

namespace System
{
    void KeyMap::Add(int type, int key, Handler h)
    {
        m_actions[type][key].insert(h);
    }

    void KeyMap::Remove(int type, int key, Handler h)
    {
        std::set<Handler>& s = m_actions[type][key];
        auto it = s.find(h);
        if (it == s.end())
            return;
        s.erase(it);
    }

    KeyMap::ActionsCollection& KeyMap::Actions(int value)
    {
        return m_actions[value];
    }

    const KeyMap::ActionsCollection& KeyMap::Actions(int value) const
    {
        return m_actions[value];
    }
}
