#ifndef _H_PUNK_VIRTUAL_CAMERA_MANAGER
#define _H_PUNK_VIRTUAL_CAMERA_MANAGER

#include "../../system/resource_manager_2.h"
#include "../../system/environment.h"

namespace Virtual
{		
	class Camera;
}

namespace System
{
	template<> class PUNK_ENGINE Policy<Virtual::Camera>
	{
	public:
		static const System::string GetResourceFile() { return L"resource"; }
		static const System::string GetExtension() { return L"*.camera"; }
		static const System::string GetFolder() { return System::Environment::Instance()->GetSoundFolder(); }	
		static const int GetResourceType() { return System::PERMANENT_RESOURCE_AUDIO_BUFFER; }
		static void OnInit();
		static void OnDestroy();
	};
}

namespace Virtual
{
	class PUNK_ENGINE CameraManager : public System::ResourceManager2<Camera, System::Policy>
	{
		CameraManager(const CameraManager&);
		CameraManager& operator = (const CameraManager&);		
	public:
		CameraManager();
	};
}

#endif	//	_H_PUNK_VIRTUAL_CAMERA_MANAGER