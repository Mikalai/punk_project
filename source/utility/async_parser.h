#ifndef PUNK_UTILIT_ASYNC_PARSER_H
#define PUNK_UTILIT_ASYNC_PARSER_H

#include "../config.h"
#include "../string/string.h"
#include "../system/concurrency/module.h"

namespace System { class Object; }

namespace Utility
{
    class PUNK_ENGINE_API AsyncParserTask
    {
    public:
        enum StateType { AsyncLoading, AsyncFailed, AsyncSuccess };

    public:
        AsyncParserTask(const System::string& path);
        ~AsyncParserTask();

        StateType State();
        void State(StateType state);
        System::Object* Release();
        const System::string& Path() const;
        void SetResult(System::Object* value);
    private:
        System::ThreadMutex m_mutex;
        StateType m_state;
        System::Object* m_object;
        System::string m_path;
    };

    class PUNK_ENGINE_API AsyncParser
    {
    public:
        AsyncParser();
        ~AsyncParser();

        AsyncParserTask* Next();
        void Add(AsyncParserTask* task);
    private:
        void Terminate();
    private:
        System::Thread m_parse_thread;
        System::Monitor m_parse_tasks_monitor;
        std::deque<AsyncParserTask*> m_tasks;
    };
}

#endif // PUNK_UTILIT_ASYNC_PARSER_H
