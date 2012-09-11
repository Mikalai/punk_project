#include <iostream>
#include <fstream>

#include "../../punk_engine.h"

#define STATIC_VAO 1
#define SKINNED_VAO 2

class ToVaoConverter
{
public:

	ToVaoConverter(const char* flag, const char* filename, const char* output)
	{
		if (!OpenGL::Driver::Instance()->Start())
		{
			out_error() << "Can't make vao cook without OpenGL" << std::endl;
			return;
		}

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
				std::ofstream stream;
				if (output)
				{
					System::string ff= System::Environment::Instance()->GetModelFolder() + System::string(output) + obj->GetName() + L".object";
					stream.open(ff.Data(), std::ios_base::binary);
				}
				else
					stream.open((System::Environment::Instance()->GetModelFolder() + obj->GetName() + L".object").Data(), std::ios_base::binary);
				obj->Save(stream);
				stream.close();
			}

			int type = 0;
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
						type = SKINNED_VAO;
					}
				}

				if (!cooked)
				{
					obj->CookAsStaticMesh();
					type = STATIC_VAO;
				}
			}
			else if (!strcmp(flag, "--static"))
			{
				obj->CookAsStaticMesh();
				type = STATIC_VAO;
			}
			else 
			{
				std::cout << "Bad flag " << flag << std::endl;
				return;
			}

			ExportVAO(obj, type);
		}
	}

	void ExportVAO(Utility::Object* obj, int type)
	{
		std::auto_ptr<OpenGL::StaticObject> gpu_mesh(new OpenGL::StaticObject());	
		bool has_geom = true;
		if (obj->GetSkinnedMesh())
		{
			gpu_mesh->Cook(obj->GetSkinnedMesh());				
		}
		else if (obj->GetStaticMesh())
		{
			gpu_mesh->Cook(obj->GetStaticMesh());
		}
		else
		{
			out_warning() << L"No geometry data in " + obj->GetName() << std::endl;
			has_geom = false;
		}

		if (has_geom)
		{	
			System::string ext;
			if (type == STATIC_VAO)
				ext = L".static_vao";
			else if (type == SKINNED_VAO)
				ext = L".skinned_vao";
			else
			{
				out_error() << "Can't export vao, don't know type" << std::endl;
				return;
			}
			std::ofstream output((System::Environment::Instance()->GetModelFolder() + System::string(obj->GetName().Data()) + ext).Data(), std::ios_base::binary);

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
			ExportVAO(child.get(), type);
		}
	}
};

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		out_error() << System::string::Format(L"Not enough parameters. Should be provided a list of pmd files. They will be converted to vao. vao_cooker.exe --skinned|--static file.pmd") << std::endl;
		return 0;
	}

	System::Window::Instance()->SetTitle(L"VAO cooker");
	System::Mouse::Instance()->LockInWindow(false);

	int i = 2;
	if (strcmp(argv[2], "--o") == 0)			
		i = 4;
	for (; i < argc; ++i)
	{		
		if (strcmp(argv[2], "--o") == 0)			
			ToVaoConverter converter(argv[1], argv[i], argv[3]);	
		else
			ToVaoConverter converter(argv[1], argv[i], 0);	
	}
	
	return 0;
}