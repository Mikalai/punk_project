#ifndef _H_PUNK_VIRTUAL_MATERIAL_MANAGER
#define _H_PUNK_VIRTUAL_MATERIAL_MANAGER

#include "../../system/environment.h"
#include "../data/material.h"

//namespace Virtual
//{
//	class Material;
//};
//
//namespace System
//{
//	template<> class PUNK_ENGINE_PUBLIC Policy<Virtual::Material>
//	{
//	public:
//		static const System::string GetResourceFile() { return L"resource"; }
//		static const System::string GetExtension() { return L"*.material"; }
//		static const System::string GetFolder() { return System::Environment::Instance()->GetTextureFolder(); }	
//		static System::ObjectType GetResourceType() { return System::ObjectType::MATERIAL; }
//		static void OnInit() {}
//		static void OnDestroy() {}
//	};
//}
//
//namespace Virtual
//{
//	class PUNK_ENGINE_PUBLIC MaterialManager : public System::ResourceManager2<Material, System::Policy>
//	{
//		MaterialManager(const MaterialManager&);
//		MaterialManager& operator = (const MaterialManager&);		
//	public:
//		MaterialManager() {}
//	};
//}

#endif	//	_H_PUNK_VIRTUAL_MATERIAL_MANAGER