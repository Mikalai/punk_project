#include <algorithm>
#include "monitor_scope.h"
#include "event_manager.h"
#include "error.h"
#include "logger.h"
#include "singletone.h"

namespace System
{
	SingletoneImplementation(EventManager);

	EventManager::EventManager()
	{
		m_events_mask[0] = false;
		for (int i = 1; i < MAX_EVENTS_COUNT; i++)
			m_events_mask[i] = true;
		eventHandlers.resize(MAX_EVENTS_COUNT);
	}

	void EventManager::ExcludeFromMonitoring(long message)
	{
		m_events_mask[message] = false;
	}

	void EventManager::IncludeInMinutoring(long message)
	{
		m_events_mask[message] = true;
	}

	void EventManager::SubscribeHandler(long event, Handler handler)
	{
		MonitorScope lock(monitor);
		eventHandlers[event].push_back(handler);
	}

	void EventManager::UnsubscribeHandler(long event, Handler handler)
	{
		MonitorScope lock(monitor);
		std::vector<Handler>::const_iterator i = std::find(eventHandlers[event].begin(), eventHandlers[event].end(), handler);
		if ( i == eventHandlers[event].end())
		{
			System::Logger::GetInstance()->WriteWarning(string::Format(L"There is no handler to unsubscribe with code %d", event), LOG_LOCATION);
			return;
		}
		eventHandlers[event].erase(i);
	}

	void EventManager::FixEvent(Event* event)
	{
		//
		//	to add:
		//		events filtering and displaying to log only interesting events
		//
		static long prev_event_code = event->eventCode;
		if (prev_event_code != event->eventCode && m_events_mask[event->eventCode])
		{
			Logger::GetInstance()->WriteMessage(event->ToString());
			prev_event_code = event->eventCode;
		}

		MonitorScope lock(monitor);
		events.push(event);
		monitor.Pulse();
	}

	void EventManager::Process()
	{
		MonitorScope lock(monitor);
		while (events.empty())
			monitor.Wait();

		try
		{
			while (!events.empty())
			{
				Event* event = events.front();

				for (std::vector<Handler>::iterator i = eventHandlers[event->eventCode].begin(); i != eventHandlers[event->eventCode].end(); ++i)
				{
					(*i)(event);
				}

				events.pop();
				event->Release();
			}
		}
		catch (System::SystemError& err)
		{
			System::Logger::GetInstance()->WriteError(err.Message());
			throw;
		}
		catch (...)
		{
			System::Logger::GetInstance()->WriteError(L"Defenetly unexpected error in main loop");
			throw;
		}
	}
}
