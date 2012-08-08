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

	ToVaoConverter(const char* flag, const char* filename)
	{
		m_driver.Start(System::Window::Instance());

		Utility::Scene scene;
		scene.Load(System::Environment::Instance()->GetModelFolder() + System::string(filename));

		for (int i = 0; i < scene.GetArmatureCount(); ++i)
		{
			Utility::Armature* arm = scene.GetArmature(scene.GetArmatureName(i));
			std::ofstream stream((System::Environment::Instance()->GetArmatureFolder() + arm->GetName() + L".armature").Data(), std::ios_base::binary);
			arm->Save(stream);
			stream.close();
		}

		for (int i = 0; i < scene.GetObjectsCount(); ++i)
		{
			Utility::Object* obj = scene.FindObjectByName(scene.GetObjectName(i));
			
			//	save object file
			{
				std::ofstream stream((System::Environment::Instance()->GetModelFolder() + obj->GetName() + L".object").Data(), std::ios_base::binary);
				obj->Save(stream);
				stream.close();
			}

			std::wcout << L"Exporting vao to " << (System::Environment::Instance()->GetModelFolder() + System::string(obj->GetName().Data()) + L".vao").Data() << std::endl;
			if (!strcmp(flag, "--skinned"))
			{
				bool cooked = false;
				if (scene.GetArmatureCount())
				{
					Utility::Armature* arm = scene.GetArmature(scene.GetArmatureName(0));
					if (arm)		
					{
						cooked = obj->CookAsSkinnedMesh(*arm);						 
					}
				}

				if (!cooked)
					obj->CookAsStaticMesh();
			}
			else if (!strcmp(flag, "--static"))
			{
				obj->CookAsStaticMesh();
			}
			else 
			{
				std::cout << "Bad flag " << flag << std::endl;
				return;
			}

			ExportVAO(obj);
		}
	}

	void ExportVAO(Utility::Object* obj)
	{
		std::auto_ptr<OpenGL::StaticObject> gpu_mesh(new OpenGL::StaticObject());	
		bool has_geom = true;
		if (obj->GetSkinnedMesh())
		{
			gpu_mesh->SetStaticObject(obj->GetSkinnedMesh());				
		}
		else if (obj->GetStaticMesh())
		{
			gpu_mesh->SetStaticObject(obj->GetStaticMesh());
		}
		else
		{
			System::Logger::Instance()->WriteWarning(L"No geometry data in " + obj->GetName());
			has_geom = false;
		}

		if (has_geom)
		{
			gpu_mesh->Init();			

			std::ofstream output((System::Environment::Instance()->GetModelFolder() + System::string(obj->GetName().Data()) + L".vao").Data(), std::ios_base::binary);

			if (!output.is_open())
			{
				std::cout << "Unable to openg a file" << std::endl;
				return;
			}
			gpu_mesh->Save(output);
			output.close();
		}
		for each (auto child in obj->GetChildren())
		{
			ExportVAO(child.get());
		}
	}
};

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		System::Logger::Instance()->WriteError(System::string::Format(L"Not enough parameters. Should be provided a list of pmd files. They will be converted to vao. vao_cooker.exe --skinned|--static file.pmd"));
		return 0;
	}

	System::Window::Instance()->SetTitle(L"VAO cooker");
	System::Mouse::Instance()->LockInWindow(false);
	OpenGL::Module module;
	module.Init();
	for (int i = 2; i < argc; ++i)
	{
		ToVaoConverter converter(argv[1], argv[i]);	
	}
	module.Destroy();
	return 0;
}