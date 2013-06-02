#include <iostream>
#include <fstream>
#include <functional>
#include <algorithm>

#include "../../PUNK_ENGINE_API.h"

#define STATIC_VAO 1
#define SKINNED_VAO 2

bool ExportArmatures(Utility::WorldDesc& world_desc)
{
	std::function<bool(Utility::ObjectDesc*)> a = [&a](Utility::ObjectDesc* o) -> bool 
	{
		if (o->m_armature_desc.get())
		{
			std::unique_ptr<Virtual::Armature> armature(new Virtual::Armature(*o->m_armature_desc.get()));
			std::ofstream stream((System::Environment::Instance()->GetArmatureFolder() + o->m_name + L".armature").Data(), std::ios_base::binary);
			armature->Save(stream);
			stream.close();
		}

		for (auto object : o->m_children)
		{
			if (!a(object))
				return false;
		}	
		return true;
	};

	for (auto o : world_desc.m_objects)
	{
		a(o);
	}
	return true;
}

bool ExportMeshes(Utility::WorldDesc& world_desc)
{
	std::function<bool(Utility::ObjectDesc*)> a = [&a, &world_desc](Utility::ObjectDesc* o) -> bool 
	{
		if (o->m_mesh_desc.get())
		{
			if (o->m_mesh_desc->m_bone_weights.empty())
			{
				std::unique_ptr<OpenGL::StaticMesh> mesh(new OpenGL::StaticMesh);
				if (mesh->Cook(o->m_mesh_desc.get()))
				{
					std::ofstream stream((System::Environment::Instance()->GetModelFolder() + o->m_name + L".static_vao").Data(), std::ios_base::binary);
					mesh->Save(stream);
					stream.close();
				}
				else
					return (out_error() << "Error occured while cooking static mesh " << o->m_name << std::endl, false);
			}
			else
			{
				//	suppose that it is skinned mesh
				//	find for armature
				auto armature_it = std::find_if(world_desc.m_objects.begin(), world_desc.m_objects.end(), [&o](Utility::ObjectDesc* parent) { return o->m_parent == parent->m_name; });
				if (armature_it == world_desc.m_objects.end())
					return (out_error() << "Can't create skinned mesh, because no armature found with name " << o->m_parent << std::endl, false);

				const Utility::ArmatureDesc* armature = (*armature_it)->m_armature_desc.get();
				if (!armature)
					return (out_error() << "Can't create skinned mesh, because parent object is not an armature " << o->m_parent << std::endl, false);

				std::unique_ptr<OpenGL::SkinnedMesh> mesh(new OpenGL::SkinnedMesh);
				if (mesh->Cook(o->m_mesh_desc.get(), armature))
				{									
					std::ofstream stream((System::Environment::Instance()->GetModelFolder() + o->m_name + L".skinned_vao").Data(), std::ios_base::binary);
					mesh->Save(stream);
					stream.close();
				}
				else
					return (out_error() << "Error occured while cooking skinned mesh " << o->m_name << std::endl, false);
			}
		}

		for (auto object : o->m_children)
		{
			if (!a(object))
				return false;
		}	
		return true;
	};

	for (auto o : world_desc.m_objects)
	{
		a(o);
	}
	return true;
}

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

		Utility::WorldDesc world_desc;
		if (!Utility::Parser::LoadWorld(System::Environment::Instance()->GetModelFolder() + System::string(filename), world_desc))
		{
			out_error() << "Unable to load a world from " << filename << std::endl;
			return;
		}

		if (!ExportArmatures(world_desc))
			out_error() << "Can't export armatures" << std::endl;

		if (!ExportMeshes(world_desc))
			out_error() << "Can't export meshes" << std::endl;

		OpenGL::Driver::Destroy();		
	}
};


	//	for (int i = 0; i < scene.GetObjectsCount(); ++i)
	//	{
	//		Utility::Object* obj = scene.FindObjectByName(scene.GetObjectName(i));
	//		
	//		//	save object file
	//		{
	//			std::ofstream stream;
	//			if (output)
	//			{
	//				System::string ff= System::Environment::Instance()->GetModelFolder() + System::string(output) + obj->GetName() + L".object";
	//				stream.open(ff.Data(), std::ios_base::binary);
	//			}
	//			else
	//				stream.open((System::Environment::Instance()->GetModelFolder() + obj->GetName() + L".object").Data(), std::ios_base::binary);
	//			obj->Save(stream);
	//			stream.close();
	//		}

	//		int type = 0;
	//		std::wcout << L"Exporting vao to " << (System::Environment::Instance()->GetModelFolder() + System::string(obj->GetName().Data()) + L".vao").Data() << std::endl;
	//		if (!strcmp(flag, "--skinned"))
	//		{
	//			bool cooked = false;
	//			if (scene.GetArmatureCount())
	//			{
	//				Utility::Armature* arm = scene.GetArmature(scene.GetArmatureName(0));
	//				if (arm)		
	//				{
	//					cooked = obj->CookAsSkinnedMesh(*arm);						 
	//					type = SKINNED_VAO;
	//				}
	//			}

	//			if (!cooked)
	//			{
	//				obj->CookAsStaticMesh();
	//				type = STATIC_VAO;
	//			}
	//		}
	//		else if (!strcmp(flag, "--static"))
	//		{
	//			obj->CookAsStaticMesh();
	//			type = STATIC_VAO;
	//		}
	//		else 
	//		{
	//			std::cout << "Bad flag " << flag << std::endl;
	//			return;
	//		}

	//		ExportVAO(obj, type);
	//	}
	//}

	//void ExportVAO(Utility::Object* obj, int type)
	//{
	//	std::auto_ptr<OpenGL::StaticObject> gpu_mesh(new OpenGL::StaticObject());	
	//	bool has_geom = true;
	//	if (obj->GetSkinnedMesh())
	//	{
	//		gpu_mesh->Cook(obj->GetSkinnedMesh());				
	//	}
	//	else if (obj->GetStaticMesh())
	//	{
	//		gpu_mesh->Cook(obj->GetStaticMesh());
	//	}
	//	else
	//	{
	//		out_warning() << L"No geometry data in " + obj->GetName() << std::endl;
	//		has_geom = false;
	//	}

	//	if (has_geom)
	//	{	
	//		System::string ext;
	//		if (type == STATIC_VAO)
	//			ext = L".static_vao";
	//		else if (type == SKINNED_VAO)
	//			ext = L".skinned_vao";
	//		else
	//		{
	//			out_error() << "Can't export vao, don't know type" << std::endl;
	//			return;
	//		}
	//		std::ofstream output((System::Environment::Instance()->GetModelFolder() + System::string(obj->GetName().Data()) + ext).Data(), std::ios_base::binary);

	//		if (!output.is_open())
	//		{
	//			std::cout << "Unable to openg a file" << std::endl;
	//			return;
	//		}
	//		gpu_mesh->Save(output);
	//		output.close();
	//	}
	//	for each (auto child in obj->GetChildren())
	//	{
	//		ExportVAO(child.get(), type);
	//	}
	//}
//};

int main(int argc, char** argv)
{	
//	_CrtSetBreakAlloc(372);
	if (argc == 1)
	{
		out_error() << System::string("Not enough parameters. Should be provided a list of pmd files. They will be converted to vao. vao_cooker.exe --skinned|--static file.pmd") << std::endl;
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