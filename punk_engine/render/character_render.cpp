#include "character_render.h"
#include "bbox_render.h"

#include "../system/driver/video/opengl/render_context/rc_skinning.h"
#include "../system/driver/video/opengl/texture_context.h"
#include "../system/driver/video/opengl/texture_2d_manager.h"
#include "../system/driver/video/opengl/vao_manager.h"

#include "../utility/model/object.h"
#include "../utility/model/armature.h"
#include "../utility/camera.h"

namespace Render
{
	struct CharacterRender::CharacterRenderImpl
	{
		std::auto_ptr<OpenGL::RenderContextSkinning> m_rc;
		std::auto_ptr<OpenGL::TextureContext> m_tc;
		std::auto_ptr<Render::BBoxRender> m_bbox_render;
		CharacterRenderImpl()
			: m_rc(new OpenGL::RenderContextSkinning())
			, m_tc(new OpenGL::TextureContext())
			, m_bbox_render(new BBoxRender())
		{}
	};

	CharacterRender::Parameters::Parameters(
		Utility::Object* object, 
		Utility::Camera* camera, 
		Utility::Armature* armature,
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
		, m_armature(armature)
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

	void CharacterRender::Render(const CharacterRender::Parameters* parameters)
	{
		const Utility::Object* object = parameters->m_object;
		const Utility::Material& material = object->GetMaterial();
		const Utility::Armature* armature = parameters->m_armature;
		const Utility::Camera* camera = parameters->m_camera;
		const Math::Matrix4x4<float>* location = parameters->m_location;

		impl->m_rc->SetProjectionMatrix(camera->GetProjectionMatrix());
		impl->m_rc->SetViewMatrix(camera->GetViewMatrix());	
		impl->m_rc->SetWorldMatrix(*location);
		impl->m_rc->SetLightPosition(Math::vec3(990, 1010, 1010));
		impl->m_rc->SetAmbientColor(Math::vec4(1,1,1,1));//Math::vec4(material.GetAmbient(), material.GetAmbient(), material.GetAmbient(), 1));
		impl->m_rc->SetSpecularColor(material.GetSpecularColor());
		impl->m_rc->SetDiffuseColor(material.GetDiffuseColor());
		impl->m_rc->SetSpecularPower(material.GetSpecularFactor());

		for (int j = 0; j < armature->GetBonesCount(); ++j)
		{			
			//const Math::mat4 m = meshes[i]->GetMeshTransform().Inversed()*m_armature->GetBoneByIndex(j)->GetAnimatedGlobalMatrix()*meshes[i]->GetMeshTransform();
			const Math::mat4 m = armature->GetBoneByIndex(j)->GetAnimatedGlobalMatrix(Math::mat4());
			impl->m_rc->SetBoneMatrix(j, m);
		}

		Render(object, location, parameters);
	}

	void CharacterRender::Render(const Utility::Object* object, const Math::Matrix4x4<float>* parent, const CharacterRender::Parameters* params)
	{
		const Math::Matrix4x4<float>* location = params->m_location;
		const Utility::Camera* camera = params->m_camera;
		const Utility::Material& material = object->GetMaterial();

		impl->m_rc->SetAmbientColor(Math::vec4(1,1,1,1));//Math::vec4(material.GetAmbient(), material.GetAmbient(), material.GetAmbient(), 1));
		impl->m_rc->SetSpecularColor(material.GetSpecularColor());
		impl->m_rc->SetDiffuseColor(material.GetDiffuseColor());
		impl->m_rc->SetSpecularPower(material.GetSpecularFactor());

		if (!object->IsCollisionVolume())
		{
			if (object->GetMesh())
			{
				OpenGL::VertexArrayObject* vao = OpenGL::VaoManager::Instance()->Load(object->GetName() + L".vao");
				if (vao)
				{
					impl->m_rc->SetMeshMatrix(vao->GetMeshTransform());				
					impl->m_rc->SetWorldMatrix(*location*vao->GetMeshTransform()*Math::mat4::CreateRotation(1, 0, 0, -Math::PI/2));
					
					impl->m_tc->SetTexture0(OpenGL::Texture2DManager::Instance()->Load(object->GetMaterial().GetDiffuseMap()));
					impl->m_tc->SetTexture1(OpenGL::Texture2DManager::Instance()->Load(object->GetMaterial().GetNormalMap()));

					impl->m_tc->Bind();
					impl->m_rc->Begin();
					vao->Bind(impl->m_rc->GetSupportedVertexAttributes());
					vao->Render();
					vao->Unbind();

					impl->m_rc->End();
					impl->m_tc->Unbind();
				}

				if (params->m_show_bbox)
				{
					impl->m_bbox_render->Render(object->AsBoundingBox(), *parent*object->GetLocalMatrix(), camera->GetViewMatrix(), camera->GetProjectionMatrix());
				}				
				if (params->m_show_aabb)
					impl->m_bbox_render->RenderAABB(object->AsBoundingBox(), *parent*object->GetLocalMatrix(), camera->GetViewMatrix(), camera->GetProjectionMatrix());
			}
		}
		else
		{
			if (params->m_show_bbox)
			{
				Math::BoundingBox bbox;
				bbox.Min().Set(-1,-1,-1);
				bbox.Max().Set(1,1,1);
				impl->m_bbox_render->Render(bbox, *parent*object->GetLocalMatrix(), camera->GetViewMatrix(), camera->GetProjectionMatrix());
			}
			if (params->m_show_aabb)
				impl->m_bbox_render->RenderAABB(object->AsBoundingBox(), *parent*object->GetLocalMatrix(), camera->GetViewMatrix(), camera->GetProjectionMatrix());
		}

		for each (auto child in object->GetChildren())
		{
			Math::mat4 temp = *parent*object->GetLocalMatrix();
			Render(child.get(), &temp, params);
		}
	}


	CharacterRender::CharacterRender()
		: impl(new CharacterRender::CharacterRenderImpl())
	{}

	CharacterRender::~CharacterRender()
	{
		impl.reset(0);
	}
}