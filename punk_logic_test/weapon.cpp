#include "all_textures.h"
#include "all_vao.h"
#include "character.h"
#include "weapon.h"
#include "../punk_engine/utility/model/armature.h"

AllWeapon::AllWeapon()
{
	m_mini14.reset(new Weapon);
	m_mini14->m_body_vao = AllVAO::Instance()->m_mini14.get();
	m_mini14->m_backsight_vao = AllVAO::Instance()->m_mini14_backsight.get();
	m_mini14->m_holder_vao = AllVAO::Instance()->m_mini14_holder.get();
	m_mini14->m_diffuse_map_backsight = AllTextures::Instance()->m_mini14_skin.get();
	m_mini14->m_diffuse_map_body = AllTextures::Instance()->m_mini14_skin.get();
	m_mini14->m_diffuse_map_holder = AllTextures::Instance()->m_mini14_skin.get();

	m_m16a2.reset(new Weapon);
	m_m16a2->m_body_vao = AllVAO::Instance()->m_a16a2.get();
	m_m16a2->m_backsight_vao = AllVAO::Instance()->m_a16a2_backsight.get();
	m_m16a2->m_holder_vao = AllVAO::Instance()->m_a16a2_holder.get();
	m_m16a2->m_diffuse_map_backsight = AllTextures::Instance()->m_mini14_skin.get();
	m_m16a2->m_diffuse_map_body = AllTextures::Instance()->m_m16a2_skin.get();
	m_m16a2->m_diffuse_map_holder = AllTextures::Instance()->m_m16a2_skin.get();
}

std::auto_ptr<AllWeapon> AllWeapon::m_instance;


void WeaponRenderable::Render(Weapon* weapon, Character* player, OpenGL::TextureContext* tc, OpenGL::RenderContext* rc)
{
	OpenGL::RenderContextBumpMapping* light_rc = dynamic_cast<OpenGL::RenderContextBumpMapping*>(rc);
	if (light_rc)
	{
		OpenGL::StaticObject* vao = weapon->m_body_vao;

		if (player)
		{
			Utility::Bone* bone = player->m_armature->GetBoneByName(L"Palm_R");
			const Math::mat4 world = bone->GetWorldMatrix();
			
			if (!bone)
				return;

			light_rc->SetWorldMatrix(Math::mat4::CreateFreeCameraMatrix(player->GetPosition(), player->GetOrientation(), 
				Math::vec3(0, 1, 0)).Inversed() * Math::mat4::CreateScaling(player->m_scale, player->m_scale, player->m_scale) * bone->GetAnimatedGlobalMatrix() * world * Math::mat4::CreateScaling(player->m_scale, player->m_scale, player->m_scale).Inversed() * vao->GetMeshTransform() * Math::mat4::CreateRotation(1, 0, 0, -Math::PI / 2.0));
		}
		else
		{
		}

		tc->SetTexture0(weapon->m_diffuse_map_body);
		tc->SetTexture1(weapon->m_diffuse_map_body);
		tc->Bind();				

		light_rc->Begin();
		vao->Bind(rc->GetSupportedVertexAttributes());
		vao->Render();
		vao->Unbind();

		tc->SetTexture0(weapon->m_diffuse_map_holder);
		tc->SetTexture1(weapon->m_diffuse_map_holder);
		tc->Bind();				

		vao = weapon->m_holder_vao;
		vao->Bind(rc->GetSupportedVertexAttributes());
		vao->Render();
		vao->Unbind();

		tc->SetTexture0(weapon->m_diffuse_map_backsight);
		tc->SetTexture1(weapon->m_diffuse_map_backsight);
		tc->Bind();				

		vao = weapon->m_backsight_vao;
		vao->Bind(rc->GetSupportedVertexAttributes());
		vao->Render();
		vao->Unbind();

		tc->Unbind();
	}
}
