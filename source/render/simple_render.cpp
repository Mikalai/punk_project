#include "simple_render.h"
#include "../virtual/data/data.h"
#include "../scene/scene_graph.h"
#include "../opengl/driver.h"
#include "../opengl/render/render_state.h"

#include <stack>

namespace Render
{
	//class PUNK_ENGINE RenderTraverse : public Scene::NodeVisitor
	//{
	//	OpenGL::Frame& m_frame;

	//public:

	//	OpenGL::StateManager m_states;

	//	RenderTraverse(OpenGL::Frame& frame) : m_frame(frame) 
	//	{
	//	}

	//	virtual void PreEnter()
	//	{
	//		m_states.Push();
	//	}

	//	virtual void PostEnter()
	//	{
	//		if (!m_states.Pop())
	//			out_error() << "Error occured while traversing the render tree" << std::endl;
	//	}

	//	bool RenderStaticMesh(System::Proxy<System::Object> data)
	//	{
	//		auto state = m_states.CurrentState();
	//		if (!state->m_camera.IsValid())
	//			return (out_error() << "Can't render static mesh because camera is not set" << std::endl, false);
	//		if (!state->m_current_material.IsValid())
	//			return (out_error() << "Can't render static mesh because material is not set" << std::endl, false);
	//		if (!state->m_current_light_set.IsValid())
	//			return (out_error() << "Can't render static mesh because lights is not set" << std::endl, false);					

	//		state->m_tc->SetTexture(0, OpenGL::Texture2DManager::Instance()->Load(state->m_current_material->GetDiffuseMap()));
	//		state->m_tc->SetTexture(1, OpenGL::Texture2DManager::Instance()->Load(state->m_current_material->GetNormalMap()));

	//		OpenGL::Batch* batch = new OpenGL::Batch();
	//		batch->m_state = state;
	//		batch->m_renderable = data;
	//		state.m_pass->AddBatch(batch);
	//	}

	//	virtual bool operator () (Scene::Node* value)
	//	{
	//		System::Object* data = value->GetData();
	//		if (data)
	//		{
	//			auto type = value->GetData()->GetType();
	//			if (type == System::DYNAMIC_RESOURCE_PROXY)
	//			{
	//				data = static_cast<Virtual::Proxy*>(value->GetData())->AsObject();
	//				type = data->GetType();
	//			}
	//			switch (type)
	//			{
	//			case System::RESOURCE_NONE:
	//				break;
	//			case System::ObjectType::STATIC_MESH:
	//				RenderStaticMesh(data);
	//				break;
	//			case System::ObjectType::SKINNED_MESH:
	//				break;
	//			case System::PERMANENT_RESOURCE_POINT_LIGHT:
	//				break;
	//			case System::ObjectType::AUDIO_BUFFER:
	//				break;
	//			case System::PERMANENT_RESOURCE_COLLISION_SHAPE:
	//				break;
	//			case System::ObjectType::TEXTURE_2D:
	//				break;
	//			case System::PERMANENT_RESOURCE_SCENE:
	//				break;
	//			case System::PERMANENT_RESOURCE_ARMATURE:
	//				break;
	//			case System::PERMANENT_RESOURCE_WEAPON_TYPE:
	//				break;
	//			case System::DYNAMIC_RESOURCE_START:
	//				break;
	//			case System::ObjectType::FPS_CAMERA:
	//				break;
	//			case System::DYNAMIC_RESOURCE_CAMERA_1:
	//				break;
	//			case System::DYNAMIC_RESOURCE_CAMERA_2:
	//				break;
	//			case System::DYNAMIC_RESOURCE_PROXY:
	//				{
	//					out_error() << "Proxy should be preprocessed early" << std::endl;
	//				}
	//				break;
	//			case System::DYNAMIC_RESOURCE_TRANSFORM:
	//				m_state.m_local = m_state.m_local * ((Virtual::TransformNode*)data)->Get();
	//					break;
	//			case System::DYNAMIC_RESOURCE_POINT_LIGHT:
	//				break;
	//			case System::DYNAMIC_RESOURCE_SPOT_LIGHT:
	//				break;
	//			case System::ObjectType::MATERIAL:
	//					m_state.m_current_material = (Virtual::Material*)data;
	//				break;
	//			case System::DYNAMIC_RESOURCE_ARMATURE_ANIMATION_MIXER:
	//				break;
	//			case System::DYNAMIC_RESOURCE_OBJECT_ANIMATION_MIXER:
	//				break;
	//			default:
	//				break;
	//			}
	//		}
	//		return true;
	//	}
	//};

	//class FindLights : public Scene::NodeVisitor
	//{
	//public:

	//	std::vector<Virtual::Light*> m_lights;

	//	virtual void PreEnter()
	//	{
	//	}

	//	virtual void PostEnter()
	//	{
	//	}

	//	virtual bool operator () (Scene::Node* value)
	//	{
	//		System::Object* data = value->GetData();
	//		if (data)
	//		{
	//			auto type = value->GetData()->GetType();
	//			switch (type)
	//			{
	//			case System::DYNAMIC_RESOURCE_POINT_LIGHT:
	//				m_lights.push_back((Virtual::Light*)value->GetData());
	//				break;
	//			}
	//		}
	//		return true;
	//	}
	//};

	//bool SimpleRender::Render(const Virtual::World& world, OpenGL::Frame& frame)
	//{		
	//	//
	//	//	first find all lights in the scene
	//	//
	//	FindLights light_finder;
	//	world.Traverse(&light_finder);

	//	std::unique_ptr<RenderTraverse> traverse(new RenderTraverse(frame));
	//	RenderTraverse::State start_state;		
	//	start_state.m_pass = new OpenGL::RenderPass;
	//	start_state.m_pass->SetRenderTarget(m_target);
	//	start_state.m_context = new OpenGL::RenderContextBumpMapping();
	//	start_state.m_tc = new OpenGL::TextureContext;
	//	start_state.m_camera = m_active_camera;		
	//	start_state.m_lights = light_finder.m_lights;
	//	start_state.m_current_material = Virtual::Material::DefaultMaterial.get();

	//	traverse->m_state = start_state;

	//	world.Traverse(traverse.get());
	//	
	//	frame.AddRenderPass(start_state.m_pass);

	//	return true;
	//}
}
