//#ifndef _H_PUNK_VIRTUAL_CAMERA_MANAGER
//#define _H_PUNK_VIRTUAL_CAMERA_MANAGER
//
//#include "../../system/resource_manager.h"
//#include "../../system/environment.h"
//#include "../data/cameras/fps_camera.h"
//
//namespace Virtual
//{		
//	namespace Cameras
//	{
//		class FirstPersonCamera;
//	}
//}
//
//namespace System
//{
//	template<> class PUNK_ENGINE Policy<Virtual::FirstPersonCamera>
//	{
//	public:
//		static const System::string GetResourceFile() { return L"resource"; }
//		static const System::string GetExtension() { return L"*.fps_camera"; }
//		static const System::string GetFolder() { return System::Environment::Instance()->GetSoundFolder(); }	
//		static System::ObjectType GetResourceType() { return System::ObjectType::FPS_CAMERA; }
//		static void OnInit() {}
//		static void OnDestroy() {}
//	};
//}
//
//namespace Virtual
//{
//	class PUNK_ENGINE FirstPersonCameraManager : public System::ResourceManager2<Cameras::FirstPersonCamera, System::Policy>
//	{
//		FirstPersonCameraManager(const FirstPersonCameraManager&);
//		FirstPersonCameraManager& operator = (const FirstPersonCameraManager&);		
//	public:
//		FirstPersonCameraManager() {}
//	};
//}
//
//#endif	//	_H_PUNK_VIRTUAL_CAMERA_MANAGER