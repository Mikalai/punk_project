#ifndef _H_PUNK_SYSTEM_MODULE
#define _H_PUNK_SYSTEM_MODULE

#include "errors/module.h"
#include "concurrency/module.h"
#include "streaming/module.h"
#include "smart_pointers/module.h"
#include "errors/module.h"
#include "window/module.h"
//#include "allocator.h"
#include "clock.h"
#include "event_manager.h"
#include "folder.h"
//#include "monitor.h"
//#include "monitor_scope.h"
#include "timer.h"
#include "types.h"
#include "binary_file.h"
#include "string.h"
#include "buffer.h"
#include "console.h"
#include "keyboard.h"
#include "mouse.h"
#include "process.h"
//#include "thread.h"
#include "environment.h"
#include "singletone.h"
#include "logger.h"
#include "config_file.h"
#include "handle.h"
#include "resource.h"
#include "template_singletone.h"
#include "resource_manager.h"
#include "node.h"
#include "profiler.h"
#include "camera_capture.h"

#include "types\list.h"
#include "types\priority_list.h"


namespace System
{
	class Module
	{
	public:
		virtual void Init() = 0;
		virtual void Destroy() = 0;
		virtual ~Module() {};
	};
};

#endif	//	_H_PUNK_SYSTEM_MODULE