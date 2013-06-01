//#include "character_render.h"
//#include "bbox_render.h"
//
//#include "../opengl/render_context/render_contexts.h"
//#include "../opengl/textures/texture_context.h"
//#include "../opengl/textures/texture_2d_manager.h"
//#include "../opengl/renderable/renderable_data.h"
//#include "../opengl/render/render.h"
//
//#include "../utility/model/object.h"
//#include "../utility/model/armature.h"
//#include "../utility/camera.h"
//
//namespace Render
//{
//	void Render(const Utility::Entity* object, const Math::Matrix4x4<float>* parent, const CharacterRender::Parameters* params, OpenGL::RenderContextSkinning::PolicyParameters& p);
//
//	struct CharacterRender::CharacterRenderImpl
//	{
//		std::unique_ptr<OpenGL::RenderContextSkinning> m_rc;
//		std::unique_ptr<OpenGL::TextureContext> m_tc;
//		std::unique_ptr<BBoxRender> m_bbox_render;
//		CharacterRenderImpl()
//			: m_rc(new OpenGL::RenderContextSkinning())
//			, m_tc(new OpenGL::TextureContext())
//			, m_bbox_render(new BBoxRender())
//		{}
//	};
//
//	CharacterRender::Parameters::Parameters(
//		Utility::Entity* object,
//		Utility::Camera* camera,
//		Utility::Armature* armature,
//		Math::Matrix4x4<float>* location,
//		bool render_production,
//		bool use_diffuse_map,
//		bool use_normal_map,
//		bool show_only_texture_coords,
//		bool show_only_normals,
//		bool show_only_bitangents,
//		bool show_only_tangents,
//		bool show_only_diffuse_map,
//		bool show_only_normal_map,
//		bool show_bbox,
//		bool show_aabb)
//		: m_object(object)
//		, m_camera(camera)
//		, m_armature(armature)
//		, m_location(location)
//		, m_render_production(render_production)
//		, m_use_diffuse_map(use_diffuse_map)
//		, m_use_normal_map(use_normal_map)
//		, m_show_only_texture_coords(show_only_texture_coords)
//		, m_show_only_normals(show_only_normals)
//		, m_show_only_bitangets(show_only_bitangents)
//		, m_show_only_tangents(show_only_tangents)
//		, m_show_only_diffuse_map(show_only_diffuse_map)
//		, m_show_only_normal_map(show_only_normal_map)
//		, m_show_bbox(show_bbox)
//		, m_show_aabb(show_aabb)
//	{}
//
//	void CharacterRender::Render(const CharacterRender::Parameters* parameters)
//	{
//		const Utility::Entity* object = parameters->m_object;
//		const Utility::Material& material = object->GetMaterial();
//		const Utility::Armature* armature = parameters->m_armature;
//		const Utility::Camera* camera = parameters->m_camera;
//		const Math::Matrix4x4<float>* location = parameters->m_location;
//
//		OpenGL::RenderContextSkinning::PolicyParameters p;
//		p.m_ambient = Math::vec4(1,1,1,1);//Math::vec4(material.GetAmbient(), material.GetAmbient(), material.GetAmbient(), 1));
//		for (int j override; j < armature->GetBonesCount(); ++j)
//		{
//			//const Math::mat4 m = meshes[i]->GetMeshTransform().Inversed()*m_armature->GetBoneByIndex(j)->GetAnimatedGlobalMatrix()*meshes[i]->GetMeshTransform();
//			const Math::mat4 m = armature->GetBoneByIndex(j)->GetAnimatedGlobalMatrix(Math::mat4());
//			p.m_bone[j] = m;
//		}
//		p.m_diffuse = material.GetDiffuseColor();
//		p.m_diffuse_texture = Texture2DManager::Instance()->Load(object->GetMaterial().GetDiffuseMap())->GetCode();
//		p.m_light_position = Math::vec3(990, 1010, 1010);
//		p.m_mesh_matrix = Math::mat4::CreateIdentity();
//		p.m_mesh_matrix_inversed = Math::mat4::CreateIdentity();
//		p.m_normal_matrix = (camera->GetViewMatrix()**location).RotationPart().Inversed().Transposed();
//		p.m_normal_texture = Texture2DManager::Instance()->Load(object->GetMaterial().GetNormalMap())->GetCode();
//		p.m_proj = camera->GetProjectionMatrix();
//		p.m_view = camera->GetViewMatrix();
//		p.m_view_world = camera->GetViewMatrix()**location;
//		p.m_world = *location;
//		p.m_specular = material.GetSpecularColor();
//		p.m_specular_power = material.GetSpecularFactor();
//
//
//		::Render(object, location, parameters, p);
//	}
//
//	OpenGL::Batch* MakeBatch(
//		const Utility::Entity* object,
//		const Math::Matrix4x4<float>* parent,
//		const CharacterRender::Parameters* params,
//
//
//	void Render(const Utility::Entity* object, const Math::Matrix4x4<float>* parent, const CharacterRender::Parameters* params, OpenGL::RenderPass* pass)
//	{
//		const Math::Matrix4x4<float>* location = params->m_location;
//		const Utility::Camera* camera = params->m_camera;
//		const Utility::Material& material = object->GetMaterial();
//
//		p.m_ambient = Math::vec4(1,1,1,1);//Math::vec4(material.GetAmbient(), material.GetAmbient(), material.GetAmbient(), 1));
//		p.m_specular = material.GetSpecularColor();
//		p.m_diffuse = material.GetDiffuseColor();
//		p.m_specular_power = material.GetSpecularFactor();
//
//		if (!object->IsCollisionVolume())
//		{
//			if (object->IsSkinnedMesh())
//			{
//				OpenGL::Batch batch;
//				batch.m_parameters
//				OpenGL::SkinMesh* vao = OpenGL::SkinnedMeshManager::Instance()->Load(object->GetName() + L".skinned_vao");
//				if (vao)
//				{
//					impl->m_rc->SetMeshMatrix(vao->GetMeshTransform());
//					impl->m_rc->SetWorldMatrix(*location*vao->GetMeshTransform()*Math::mat4::CreateRotation(1, 0, 0, -Math::PI/2));
//
//					impl->m_tc->SetTexture0(Texture2DManager::Instance()->Load(object->GetMaterial().GetDiffuseMap()));
//					impl->m_tc->SetTexture1(Texture2DManager::Instance()->Load(object->GetMaterial().GetNormalMap()));
//
//					impl->m_tc->Bind();
//					impl->m_rc->Begin();
//					vao->Bind(impl->m_rc->GetSupportedint());
//					vao->Render();
//					vao->Unbind();
//
//					impl->m_rc->End();
//					impl->m_tc->Unbind();
//				}
//
//				if (params->m_show_bbox)
//				{
//					impl->m_bbox_render->Render(object->AsBoundingBox(), *parent*object->GetLocalMatrix(), camera->GetViewMatrix(), camera->GetProjectionMatrix());
//				}
//				if (params->m_show_aabb)
//					impl->m_bbox_render->RenderAABB(object->AsBoundingBox(), *parent*object->GetLocalMatrix(), camera->GetViewMatrix(), camera->GetProjectionMatrix());
//			}
//		}
//		else
//		{
//			if (params->m_show_bbox)
//			{
//				impl->m_bbox_render->Render(object->AsBoundingBox(), *parent*object->GetLocalMatrix(), camera->GetViewMatrix(), camera->GetProjectionMatrix());
//			}
//			if (params->m_show_aabb)
//				impl->m_bbox_render->RenderAABB(object->AsBoundingBox(), *parent*object->GetLocalMatrix(), camera->GetViewMatrix(), camera->GetProjectionMatrix());
//		}
//
//		for each (auto child in object->GetChildren())
//		{
//			Math::mat4 temp = *parent*object->GetLocalMatrix();
//			Render(child.get(), &temp, params);
//		}
//	}
//
//
//	CharacterRender::CharacterRender()
//		: impl(new CharacterRender::CharacterRenderImpl())
//	{}
//
//	CharacterRender::~CharacterRender()
//	{
//		impl.reset(0);
//	}
//}
