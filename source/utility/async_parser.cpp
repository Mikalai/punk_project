#include <deque>
#include "../system/object.h"
#include "parser/parser.h"
#include "async_parser.h"

namespace Utility
{
    static AsyncParserTask g_termination_task("");

#ifdef _WIN32
    unsigned ParseThread(void* data)
#elif defined __gnu_linux__
    void* ParseThread(void* data)
#endif
    {
        AsyncParser* parser = (AsyncParser*)data;
        while (1)
        {
            AsyncParserTask* task = parser->Next();
            if (task == &g_termination_task)
                return 0;

            try
            {
                System::Object* object = ParsePunkFile(task->Path());
                task->SetResult(object);
                task->State(AsyncParserTask::AsyncSuccess);
            }
            catch (...)
            {
                task->State(AsyncParserTask::AsyncFailed);
            }
        }
    }

    AsyncParserTask::AsyncParserTask(const System::string& path)
        : m_object(nullptr)
        , m_state(AsyncLoading)
        , m_path(path)
    {
    }

    AsyncParserTask::~AsyncParserTask()
    {
        delete m_object;
    }

    AsyncParserTask::StateType AsyncParserTask::State()
    {
        System::ThreadMutexLock lock(m_mutex);
        return m_state;
    }

    void AsyncParserTask::State(StateType state)
    {
        System::ThreadMutexLock lock(m_mutex);
        m_state = state;
    }

    System::Object* AsyncParserTask::Release()
    {
        auto res = m_object;
        m_object = nullptr;
        return res;
    }

    void AsyncParserTask::SetResult(System::Object *value)
    {
        m_object = value;
    }

    const System::string& AsyncParserTask::Path() const
    {
        return m_path;
    }

    AsyncParser::AsyncParser()
    {
        m_parse_thread.Create(ParseThread, this);
        m_parse_thread.Resume();
    }

    AsyncParser::~AsyncParser()
    {
        Terminate();
        m_parse_thread.Join();
    }

    void AsyncParser::Add(AsyncParserTask* task)
    {
        m_parse_tasks_monitor.Lock();
        m_tasks.push_back(task);
        m_parse_tasks_monitor.Pulse();
        m_parse_tasks_monitor.Unlock();
    }

    AsyncParserTask* AsyncParser::Next()
    {
        m_parse_tasks_monitor.Lock();
        while (m_tasks.empty())
            m_parse_tasks_monitor.Wait();
        AsyncParserTask* task = m_tasks.front();
        m_tasks.pop_front();
        m_parse_tasks_monitor.Unlock();
        return task;
    }

    void AsyncParser::Terminate()
    {
        m_parse_tasks_monitor.Lock();
        m_tasks.push_front(&g_termination_task);
        m_parse_tasks_monitor.Unlock();
        m_parse_tasks_monitor.Pulse();
    }
}
