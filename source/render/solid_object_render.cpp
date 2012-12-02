#include <memory>
#include "solid_object_render.h"
#include "bbox_render.h"

#include "../opengl/render_context/render_contexts.h"
#include "../opengl/textures/texture_context.h"
#include "../opengl/textures/texture_2d_manager.h"
#include "../opengl/renderable/renderable_data.h"
#include "../opengl/render/render.h"

#include "../utility/model/object.h"
#include "../utility/model/object_manager.h"
#include "../utility/model/armature.h"
#include "../utility/camera.h"


namespace Render
{
	struct SolidObjectRender::SolidObjectRenderImpl
	{
		std::auto_ptr<OpenGL::RenderContextBumpMapping> m_rc;
		std::auto_ptr<OpenGL::TextureContext> m_tc;
	//	std::auto_ptr<BBoxRender> m_bbox_render;
		SolidObjectRenderImpl()
			: m_rc(new OpenGL::RenderContextBumpMapping())
			, m_tc(new OpenGL::TextureContext())
//			, m_bbox_render(new BBoxRender())
		{}
	};

	SolidObjectRender::Parameters::Parameters(
		Utility::Entity* object, 
		Utility::Camera* camera, 
		OpenGL::RenderPass* render_pass,
		Math::Matrix4x4<float>* location,
		bool render_production, 
		bool use_diffuse_map, 
		bool use_normal_map,
		bool show_only_texture_coords, 
		bool show_only_normals,
		bool show_only_bitangents,
		bool show_only_tangents,
		bool show_only_diffuse_map,
		bool show_only_normal_map,
		bool show_bbox,
		bool show_aabb)
		: m_object(object)
		, m_camera(camera)
		, m_render_pass(render_pass)
		, m_location(location)
		, m_render_production(render_production)
		, m_use_diffuse_map(use_diffuse_map)
		, m_use_normal_map(use_normal_map)
		, m_show_only_texture_coords(show_only_texture_coords)
		, m_show_only_normals(show_only_normals)
		, m_show_only_bitangets(show_only_bitangents)
		, m_show_only_tangents(show_only_tangents)
		, m_show_only_diffuse_map(show_only_diffuse_map)
		, m_show_only_normal_map(show_only_normal_map)
		, m_show_bbox(show_bbox)
		, m_show_aabb(show_aabb)
	{}

	void SolidObjectRender::Render(const SolidObjectRender::Parameters* parameters)
	{
		const Utility::Entity* object = parameters->m_object;
		const Utility::Material& material = object->GetMaterial();		
		const Utility::Camera* camera = parameters->m_camera;
		const Math::Matrix4x4<float>* location = parameters->m_location;

		Render(object, location, parameters);
	}

	void SolidObjectRender::Render(const Utility::Entity* object, const Math::Matrix4x4<float>* parent, const SolidObjectRender::Parameters* params)
	{
		const Math::Matrix4x4<float>* location = &object->GetLocalMatrix();
		const Utility::Camera* camera = params->m_camera;		
		OpenGL::RenderPass* pass = params->m_render_pass;

		if (!object->IsCollisionVolume())
		{						
			if (object->IsProxy())
			{				
				const Utility::Entity* proxy = object->GetReferenceObject();
				if (proxy)
				{
					const Utility::Material& material = proxy->GetMaterial();
					OpenGL::StaticMesh* vao = static_cast<OpenGL::StaticMesh*>(*OpenGL::StaticMeshManager::Instance()->Load(proxy->GetName() + L".static_vao"));
					if (vao)
					{
						Math::BoundingBox bbox = vao->GetBoundingBox().TransformNode(*parent**location);
						if (camera->BoxInFrustum(bbox))
						{
							std::auto_ptr<OpenGL::RenderContextBumpMapping::PolicyParameters> p(new OpenGL::RenderContextBumpMapping::PolicyParameters);
							p->m_ambient = Math::vec4(1,1,1,1);//Math::vec4(material.GetAmbient(), material.GetAmbient(), material.GetAmbient(), 1));	
							p->m_diffuse = material.GetDiffuseColor();
							p->m_diffuse_texture = 0;
							p->m_light_position = Math::vec3(990, 1010, 1010);		
							p->m_normal_matrix = (camera->GetViewMatrix()**location).RotationPart().Inversed().Transposed();
							p->m_normal_texture = 1;
							p->m_proj = camera->GetProjectionMatrix();
							p->m_view = camera->GetViewMatrix();	
							p->m_world = *parent**location;		
							p->m_specular = material.GetSpecularColor();		
							p->m_specular_power = material.GetSpecularFactor();

							std::auto_ptr<OpenGL::Batch> batch(new OpenGL::Batch);
							batch->m_parameters = p.release();
							batch->m_renderable = vao;
							batch->m_textures.push_back(static_cast<OpenGL::Texture2D*>(*OpenGL::Texture2DManager::Instance()->Load(proxy->GetMaterial().GetDiffuseMap())));
							batch->m_textures.push_back(static_cast<OpenGL::Texture2D*>(*OpenGL::Texture2DManager::Instance()->Load(proxy->GetMaterial().GetNormalMap())));

							pass->AddBatch(impl->m_tc.get(), impl->m_rc.get(), batch.release());
						}
					}
				}
			}

			Math::BoundingBox bbox = object->AsBoundingBox().TransformNode(*parent**location);
			if (object->IsMesh() && camera->BoxInFrustum(bbox))
			{
				const Utility::Material& material = object->GetMaterial();
				OpenGL::StaticMesh* vao = static_cast<OpenGL::StaticMesh*>(*OpenGL::StaticMeshManager::Instance()->Load(object->GetName() + L".static_vao"));
				if (vao)
				{
					std::auto_ptr<OpenGL::RenderContextBumpMapping::PolicyParameters> p(new OpenGL::RenderContextBumpMapping::PolicyParameters);
					p->m_ambient = Math::vec4(1,1,1,1);//Math::vec4(material.GetAmbient(), material.GetAmbient(), material.GetAmbient(), 1));	
					p->m_diffuse = material.GetDiffuseColor();
					p->m_diffuse_texture = 0;
					p->m_light_position = Math::vec3(990, 1010, 1010);		
					p->m_normal_matrix = (camera->GetViewMatrix()**location).RotationPart().Inversed().Transposed();
					p->m_normal_texture = 1;
					p->m_proj = camera->GetProjectionMatrix();
					p->m_view = camera->GetViewMatrix();	
					p->m_world = *parent**location;		
					p->m_specular = material.GetSpecularColor();		
					p->m_specular_power = material.GetSpecularFactor();
					
					std::auto_ptr<OpenGL::Batch> batch(new OpenGL::Batch);
					batch->m_parameters = p.release();
					batch->m_renderable = vao;
					batch->m_textures.push_back(static_cast<OpenGL::Texture2D*>(*OpenGL::Texture2DManager::Instance()->Load(object->GetMaterial().GetDiffuseMap())));
					batch->m_textures.push_back(static_cast<OpenGL::Texture2D*>(*OpenGL::Texture2DManager::Instance()->Load(object->GetMaterial().GetNormalMap())));
					
					pass->AddBatch(impl->m_tc.get(), impl->m_rc.get(), batch.release());

				}

				//if (params->m_show_bbox)
				//{
				//	impl->m_bbox_render->Render(object->AsBoundingBox(), *parent*object->GetLocalMatrix(), camera->GetViewMatrix(), camera->GetProjectionMatrix());
				//}				
				//if (params->m_show_aabb)
				//	impl->m_bbox_render->RenderAABB(object->AsBoundingBox(), *parent*object->GetLocalMatrix(), camera->GetViewMatrix(), camera->GetProjectionMatrix());
			}
		}
		else
		{
			//if (params->m_show_bbox)
			//{
			//	impl->m_bbox_render->Render(object->AsBoundingBox(), *parent*object->GetLocalMatrix(), camera->GetViewMatrix(), camera->GetProjectionMatrix());
			//}
			//if (params->m_show_aabb)
			//	impl->m_bbox_render->RenderAABB(object->AsBoundingBox(), *parent*object->GetLocalMatrix(), camera->GetViewMatrix(), camera->GetProjectionMatrix());
		}

		for each (auto child in object->GetChildren())
		{
			Math::mat4 temp = *parent*object->GetLocalMatrix();
			Render(child.get(), &temp, params);
		}
	}


	SolidObjectRender::SolidObjectRender()
		: impl(new SolidObjectRender::SolidObjectRenderImpl())
	{}

	SolidObjectRender::~SolidObjectRender()
	{
		impl.reset(0);
	}
}