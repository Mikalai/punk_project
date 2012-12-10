//#ifndef _H_TEXTURE_2D_MANAGER
//#define _H_TEXTURE_2D_MANAGER
//
//#include "../../config.h"
//#include "../../system/resource_manager_2.h"
//#include "../../system/environment.h"
//
//#include "texture2d.h"
//
//namespace System
//{
//	template<>
//	class Policy<OpenGL::Texture2D>
//	{
//	public:
//		static const System::string GetResourceFile() { return L"resource"; }
//		static const System::string GetExtension() { return L"*.png"; }
//		static const System::string GetFolder() { return System::Environment::Instance()->GetTextureFolder(); }	
//		static System::ObjectType GetResourceType() { return System::ObjectType::TEXTURE_2D; }
//		static void OnInit() {}
//		static void OnDestroy() {}
//	};
//}
//
//namespace OpenGL
//{
//	class PUNK_ENGINE Texture2DManager : public System::ResourceManager2<Texture2D, System::Policy>
//	{
//		Texture2DManager(const Texture2DManager&);
//		Texture2DManager& operator = (const Texture2DManager&);
//	};
//
//	//{
//	//public:
//	//	typedef std::vector<std::shared_ptr<Texture2D>> Collection;
//	//public:
//
//	//	Texture2DManager();
//	//	~Texture2DManager();
//
//	//	void Init();
//	//	void Clear();
//
//	//	Texture2D* GetTexture(int index);
//	//	const Texture2D* GetTexture(int index) const
//	//	Texture2D* LoadTexture2D(const System::string& filename);
//	//	int ManageTexture2D(Texture2D* texture2d);
//
//	//	Collectin& GetAllTexture2D();
//	//	const Collectin& GetAllTexture2D() const;
//
//	//	static Texture2DManager* Instance();
//	//	static void Destroy();
//
//	//private:
//
//	//	Collection m_item;
//
//	//};
//}
//
//#endif