#include "logger.h"

int Tab::m_offset = 0;

namespace System
{
	std::auto_ptr<Streamer> Streamer::m_instance;

	Streamer& Streamer::Instance()
	{
		if (!m_instance.get())
			m_instance.reset(new Streamer);
		return *m_instance.get();
	}

	void Streamer::Destroy()
	{
		m_instance.reset(0);
	}
}

PUNK_ENGINE System::Logger<System::LOG_MESSAGE> out_message;
PUNK_ENGINE System::Logger<System::LOG_WARNING> out_warning;
PUNK_ENGINE System::Logger<System::LOG_ERROR> out_error;
