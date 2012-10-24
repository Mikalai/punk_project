#include "simple_render.h"
#include "../virtual/data/data.h"
#include "../scene/scene.h"
#include "../opengl/driver.h"

#include <stack>

namespace Render
{
	class PUNK_ENGINE RenderTraverse : public Scene::NodeVisitor
	{
		OpenGL::Frame& m_frame;

	public:

		struct State
		{
			Virtual::Cameras::Camera* m_camera;
			Math::mat4 m_local;
			OpenGL::RenderPass* m_pass;
			OpenGL::TextureContext* m_tc;
			Virtual::Material* m_current_material;
			OpenGL::RenderContextBumpMapping* m_context;
			std::vector<Virtual::Light*> m_lights;
		};

		std::stack<State> m_state_stack;
		State m_state;

		RenderTraverse(OpenGL::Frame& frame) : m_frame(frame) 
		{
		}

		virtual void PreEnter()
		{
			m_state_stack.push(State(m_state));
		}

		virtual void PostEnter()
		{
			m_state = m_state_stack.top();
			m_state_stack.pop();
		}

		virtual bool operator () (Scene::Node* value)
		{
			System::Object* data = value->GetData();
			if (data)
			{
				auto type = value->GetData()->GetType();
				if (type == System::DYNAMIC_RESOURCE_PROXY)
				{
					data = static_cast<Virtual::Proxy*>(value->GetData())->AsObject();
					type = data->GetType();
				}
				switch (type)
				{
				case System::RESOURCE_NONE:
					break;
				case System::PERMANENT_RESOURCE_STATIC_MESH:
					{
						if (!m_state.m_camera)
							return (out_error() << "Can't render static mesh because camera is not set" << std::endl, false);
						if (!m_state.m_current_material)
							return (out_error() << "Can't render static mesh because material is not set" << std::endl, false);
						if (m_state.m_lights.empty())
							return (out_error() << "Can't render static mesh because lights is not set" << std::endl, false);					
						OpenGL::RenderContextBumpMapping::PolicyParameters* param = new OpenGL::RenderContextBumpMapping::PolicyParameters();
						param->m_ambient.Set(m_state.m_current_material->GetAmbient(),m_state.m_current_material->GetAmbient(),m_state.m_current_material->GetAmbient(),m_state.m_current_material->GetAmbient());
						param->m_diffuse = m_state.m_current_material->GetDiffuseColor();
						param->m_diffuse_texture = 0;
						param->m_light_position = m_state.m_lights.front()->GetPosition();
						param->m_normal_matrix = (m_state.m_camera->GetViewMatrix()*m_state.m_local).RotationPart().Inversed().Transposed();
						param->m_normal_texture = 1;
						param->m_proj = m_state.m_camera->GetProjectionMatrix();
						param->m_specular = m_state.m_current_material->GetSpecularColor();
						param->m_specular_power = m_state.m_current_material->GetSpecularFactor();
						param->m_view = m_state.m_camera->GetViewMatrix();
						param->m_world = m_state.m_local;

						OpenGL::Batch* batch = new OpenGL::Batch();
						batch->m_parameters = param;
						batch->m_renderable = dynamic_cast<OpenGL::StaticMesh*>(data);
						batch->m_textures.push_back(OpenGL::Texture2DManager::Instance()->Load(m_state.m_current_material->GetDiffuseMap()));
						batch->m_textures.push_back(OpenGL::Texture2DManager::Instance()->Load(m_state.m_current_material->GetNormalMap()));

						m_state.m_pass->AddBatch(m_state.m_tc, m_state.m_context, batch);
					}
					break;
				case System::PERMANENT_RESOURCE_SKINNED_MESH:
					break;
				case System::PERMANENT_RESOURCE_POINT_LIGHT:
					break;
				case System::PERMANENT_RESOURCE_AUDIO_BUFFER:
					break;
				case System::PERMANENT_RESOURCE_COLLISION_SHAPE:
					break;
				case System::PERMANENT_RESOURCE_TEXTURE2D:
					break;
				case System::PERMANENT_RESOURCE_SCENE:
					break;
				case System::PERMANENT_RESOURCE_ARMATURE:
					break;
				case System::PERMANENT_RESOURCE_WEAPON_TYPE:
					break;
				case System::DYNAMIC_RESOURCE_START:
					break;
				case System::DYNAMIC_RESOURCE_CAMERA_FPS:
					break;
				case System::DYNAMIC_RESOURCE_CAMERA_1:
					break;
				case System::DYNAMIC_RESOURCE_CAMERA_2:
					break;
				case System::DYNAMIC_RESOURCE_PROXY:
					{
						out_error() << "Proxy should be preprocessed early" << std::endl;
					}
					break;
				case System::DYNAMIC_RESOURCE_TRANSFORM:
					m_state.m_local = m_state.m_local * ((Virtual::Transform*)data)->Get();
						break;
				case System::DYNAMIC_RESOURCE_POINT_LIGHT:
					break;
				case System::DYNAMIC_RESOURCE_SPOT_LIGHT:
					break;
				case System::DYNAMIC_RESOURCE_MATERIAL:
						m_state.m_current_material = (Virtual::Material*)data;
					break;
				case System::DYNAMIC_RESOURCE_ARMATURE_ANIMATION_MIXER:
					break;
				case System::DYNAMIC_RESOURCE_OBJECT_ANIMATION_MIXER:
					break;
				default:
					break;
				}
			}
			return true;
		}
	};

	class FindLights : public Scene::NodeVisitor
	{
	public:

		std::vector<Virtual::Light*> m_lights;

		virtual void PreEnter()
		{
		}

		virtual void PostEnter()
		{
		}

		virtual bool operator () (Scene::Node* value)
		{
			System::Object* data = value->GetData();
			if (data)
			{
				auto type = value->GetData()->GetType();
				switch (type)
				{
				case System::DYNAMIC_RESOURCE_POINT_LIGHT:
					m_lights.push_back((Virtual::Light*)value->GetData());
					break;
				}
			}
			return true;
		}
	};

	bool SimpleRender::Render(const Virtual::World& world, OpenGL::Frame& frame)
	{		
		//
		//	first find all lights in the scene
		//
		FindLights light_finder;
		world.Traverse(&light_finder);

		std::unique_ptr<RenderTraverse> traverse(new RenderTraverse(frame));
		RenderTraverse::State start_state;		
		start_state.m_pass = new OpenGL::RenderPass;
		start_state.m_pass->SetRenderTarget(m_target);
		start_state.m_context = new OpenGL::RenderContextBumpMapping();
		start_state.m_tc = new OpenGL::TextureContext;
		start_state.m_camera = m_active_camera;		
		start_state.m_lights = light_finder.m_lights;
		start_state.m_current_material = Virtual::Material::DefaultMaterial.get();

		traverse->m_state = start_state;

		world.Traverse(traverse.get());
		
		frame.AddRenderPass(start_state.m_pass);

		return true;
	}
}
