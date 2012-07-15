#ifndef _H_TEXTURE_2D_MANAGER
#define _H_TEXTURE_2D_MANAGER

#include "config.h"
#include "../../../resource_manager_2.h"

namespace OpenGL
{
	class Texture2D;
}

namespace System
{
	template<>
	class Policy<Texture2D>
	{
		static const System::string GetResourceFile() { return L"resource"; }
		static const System::string GetExtension() { return L"*.png"; }
		static const System::string GetFolder() { return System::Environment::Instance()->GetTextureFolder(); }	
		static void OnInit();
		static void OnDestroy();
	};
}

namespace OpenGL
{
	class MODULE_OPENGL Texture2DManager : public System::ResourceManager2<Texture2D, System::Policy>
	{
		Texture2DManager(const Texture2DManager&);
		Texture2DManager& operator = (const Texture2DManager&);
	};

	//{
	//public:
	//	typedef std::vector<std::shared_ptr<Texture2D>> Collection;
	//public:

	//	Texture2DManager();
	//	~Texture2DManager();

	//	void Init();
	//	void Clear();

	//	Texture2D* GetTexture(int index);
	//	const Texture2D* GetTexture(int index) const
	//	Texture2D* LoadTexture2D(const System::string& filename);
	//	int ManageTexture2D(Texture2D* texture2d);

	//	Collectin& GetAllTexture2D();
	//	const Collectin& GetAllTexture2D() const;

	//	static Texture2DManager* Instance();
	//	static void Destroy();

	//private:

	//	Collection m_item;

	//};
}

#endif