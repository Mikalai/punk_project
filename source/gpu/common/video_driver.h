#ifndef _H_PUNK_VIDEO_DRIVER
#define _H_PUNK_VIDEO_DRIVER

#include "../../config.h"
#include "../gpu_config.h"
#include "../../system/window/module.h"
#include "../../system/event_manager.h"

namespace GPU
{
	struct VideoDriverDesc
	{
		Config config;
		System::Window* window;
		System::EventManager* event_manager;
	};

	class Frame;

	class PUNK_ENGINE VideoDriver
	{
	public:

		VideoDriver();
		~VideoDriver();

		void SetFullScreen(bool flag);
		bool Start(const VideoDriverDesc& desc);
		void Restart();
		void Shutdown();
		System::Window* GetWindow();
		Frame* BeginFrame();
		void EndFrame(Frame* value);

		struct VideoDriverImpl;
		VideoDriverImpl* impl;

	private:
		VideoDriver(const VideoDriver&);
		VideoDriver& operator = (const VideoDriver&);
	};
}

#endif	//	_H_PUNK_VIDEO_DRIVER