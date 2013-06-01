#include "world.h"
#include "../../utility/descriptors/descriptors.h"
#include "../../scene/node.h"
#include "proxy.h"
#include "module.h"

namespace Virtual
{
	Scene::Node* CreateNode(const Utility::WorldDesc& world_desc, Scene::Node* parent, const Utility::ObjectDesc* value)
	{
		//std::unique_ptr<Scene::Node> node(new Scene::Node());
		//node->SetName(value->m_name);		
		//if (parent != nullptr)
		//{
		//	if (parent->GetName() != value->m_parent)
		//		return (out_error() << "Parent name is not equal to the name that is stored in descriptor" << std::endl, nullptr);
		//	node->SetParentName(value->m_parent);
		//	node->SetParent(parent);
		//}

		//if (value->m_camera_desc.get())
		//{
		//	out_message() << "Adding camera to the scene grahp" << std::endl;
		//	//	found a camera
		//	node->SetData(Cameras::Camera::CreateCamera(*value->m_camera_desc));
		//}
		//else if (value->m_mesh_collision_desc.get())
		//{
		//	out_message() << "Adding collision mesh to the scene graph" << std::endl;
		//	//	found mesh collision
		//	//node->SetData(Mesh
		//	;
		//}
		//else if (value->m_mesh_desc.get())
		//{
		//	out_message() << "Adding mesh to the scene graph" << std::endl;
		//	//	found mesh
		//	node->SetData(new Proxy(world_desc, *value));
		//	if (!value->m_mesh_desc->m_material_ref.empty())
		//	{
		//		std::unique_ptr<Scene::Node> mat_node(new Scene::Node);
		//		try
		//		{
		//			out_message() << "Adding material to the scene graph" << std::endl;
		//			const Utility::MaterialDesc* mat_desc = world_desc.m_materials.at(value->m_mesh_desc->m_material_ref.front());
		//			std::unique_ptr<Material> mat(new Material(*mat_desc));
		//			mat_node->SetData(mat.release());
		//			//	swap current node with material node. thus we wrapped node with material one
		//			node->SetParent(mat_node.get());
		//			mat_node->AddChild(node.release());
		//			node.reset(mat_node.release());
		//		}
		//		catch(...)
		//		{
		//			out_error() << "Can't cook material node" << std::endl;
		//			throw;
		//		}
		//	}
		//}
		//else if (value->m_reference.Length())
		//{
		//	out_message() << "Adding reference to the scene graph" << std::endl;
		//	if (parent == nullptr)
		//		return (out_error() << "Can't create reference object because there is no parent to look for the reference" << std::endl, nullptr);
		//	Scene::Node* n = parent->GetChild(value->m_reference);
		//	if (!n)
		//		return (out_error() << "Can't create reference object because node " << value->m_reference << " has got no data stored in" << std::endl, nullptr);
		//	node->SetData(n->GetData());
		//}
		//else if (value->m_light_desc.get())
		//{
		//	out_message() << "Adding point light to the scene grahp" << std::endl;
		//	node->SetData(Virtual::Light::CreateLight(*value->m_light_desc));			
		//}
		//else //	suppose that it is a matrix node
		//{
		//	out_message() << "Adding transform to the scene graph" << std::endl;
		//	node->SetData(new TransformNode(*value));
		//}

		//for (auto child_desc : value->m_children)
		//{
		//	auto child = CreateNode(world_desc, node.get(), child_desc);
		//	if (!child)
		//		return (out_error() << "One of the child nodes was not build. Can't build node" << std::endl, nullptr);
		//	child->SetParent(node.get());
		//	node->AddChild(child);
		//}
		//return node.release();
		return nullptr;
	}

	bool World::Traverse(Scene::NodeVisitor* value) const
	{
		//value->PreEnter();
		//auto res = m_root->Apply(value);
		//value->PostEnter();
		//return res;
		return false;
	}

	World::World(const Utility::WorldDesc& value)
	{
		/*m_root.reset(new Scene::Node);
		
		for (auto object : value.m_children)
		{
			auto node = CreateNode(value, nullptr, object);
			if (!node)
			{
				out_error() << "Can't create world" << std::endl;
				return;
			}
			node->SetParent(m_root.get());
			m_root->AddChild(node);
		}*/
	}

	World::~World()
	{
		m_root.reset(nullptr);
	}
}
