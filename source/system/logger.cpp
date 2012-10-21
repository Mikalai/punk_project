#include "logger.h"

int Tab::m_offset = 0;

PUNK_ENGINE System::Logger<System::LOG_MESSAGE> out_message;
PUNK_ENGINE System::Logger<System::LOG_WARNING> out_warning;
PUNK_ENGINE System::Logger<System::LOG_ERROR> out_error;
