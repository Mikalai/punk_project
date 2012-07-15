#include <iostream>
#include <fstream>

#include "../punk_engine/system/string.h"
#include "../punk_engine/system/system.h"
#include "../punk_engine/math/math.h"
#include "../punk_engine/images/images.h"
#include "../punk_engine/utility/utility.h"
#include "../punk_engine/system/driver/video/driver.h"
#include "../punk_engine/gui/gui.h"
#include "../punk_engine/logic/logic.h"
#include "../punk_engine/render/render.h"

class ToVaoConverter
{
	OpenGL::Driver m_driver;
public:

	ToVaoConverter(const char* filename, const char* flag)
	{
		m_driver.Start(System::Window::Instance());

		Utility::Scene scene;
		// Load scene
		scene.Load(System::string(filename));		

		int objects_count = scene.GetObjectsCount();
		
		for (int i = 0; i < objects_count; ++i)
		{
			char ansi_name[2048];
			char ansi_path[2048];
			char output_filename[2048];
			const System::string& name = scene.GetObjectName(i);
			name.ToANSI(ansi_name, 2048);
			System::Environment::Instance()->GetModelFolder().ToANSI(ansi_path, 2048);			
			sprintf(output_filename, "%s%s.vao", ansi_path, ansi_name);
			std::cout << "Exporting vao to " << output_filename << std::endl;
			std::auto_ptr<Utility::StaticMesh> cpu_mesh;
			if (!strcmp(flag, "--skinned"))
				cpu_mesh.reset(scene.CookSkinnedMesh(name));
			else if (!strcmp(flag, "--static"))
				cpu_mesh.reset(scene.CookStaticMesh(name));
			else 
			{
				std::cout << "Bad flag " << flag << std::endl;
				return;
			}
			std::auto_ptr<OpenGL::StaticObject> gpu_mesh(new OpenGL::StaticObject());
			gpu_mesh->SetStaticObject(cpu_mesh.get());				
			gpu_mesh->Init();			
			std::ofstream output(output_filename, std::ios_base::binary);
			if (!output.is_open())
			{
				std::cout << "Unable to openg a file" << std::endl;
				continue;
			}
			gpu_mesh->Save(output);
			output.close();
		}
		if (!strcmp(flag, "--skinned"))
		{
			int armature_count = scene.GetArmature()
		}
	}
};

int main(int argc, char** argv)
{
	if (argc == 2)
	{
		System::Logger::Instance()->WriteError(System::string::Format(L"Not enough parameters. Should be provided a list of pmd files. They will be converted to vao. vao_cooker.exe --skinned|--static file.pmd ..."));
		return 0;
	}

	System::Window::Instance()->SetTitle(L"VAO cooker");
	System::Mouse::Instance()->LockInWindow(false);
	OpenGL::Module module;
	module.Init();
	for (int i = 2; i < argc; ++i)
	{
		ToVaoConverter converter(argv[i], argv[1]);	
	}
	module.Destroy();
	return 0;
}