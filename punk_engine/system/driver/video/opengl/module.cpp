#include "module.h"
#include "../../../window.h"
#include "../../../config_file.h"

namespace OpenGL
{
	static const wchar_t MODULE_NAME[] = L"opengl_driver";
	void Module::Init()
	{
		System::ConfigFile file;
		file.Open(System::Window::GetInstance()->GetTitle());
		if (!file.IsExistOption(L"shaders"))
			file.WriteOptionString(L"shaders", L"d:\\project\\punk_project\\punk_engine\\system\\driver\\video\\opengl\\glsl\\");
		if (!file.IsExistOption(L"textures"))
			file.WriteOptionString(L"textures", L"d:\\project\\data\\textures\\");
		if (!file.IsExistOption(L"data"))
			file.WriteOptionString(L"data", L"d:\\project\\data\\");	
		if (!file.IsExistOption(L"data"))
			file.WriteOptionString(L"data", L"d:\\project\\data\\");	
		if (!file.IsExistOption(L"fonts"))
			file.WriteOptionString(L"fonts", L"d:\\project\\data\\font\\");	
		file.Close();
	}

	void Module::Destroy()
	{
	}

	unsigned short Module::TEXTURE_2D_RESOURCE_TYPE()
	{
		return 0;
	}

	Module::~Module()
	{}

	const wchar_t* Module::NAME()
	{
		return MODULE_NAME;
	}
}