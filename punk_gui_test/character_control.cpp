#include "character_control.h"

CharacterControl::CharacterControl()
{
	m_armature = Utility::ArmatureManager::Instance()->Load(L"Armature.armature");
	m_armature->GetArmatureAnimation().EnableTrack(L"stand", true);

	m_feet_vao = OpenGL::VaoManager::Instance()->Load(L"man_feet.vao");
	m_low_vao = OpenGL::VaoManager::Instance()->Load(L"man_low.vao");
	m_arms_vao = OpenGL::VaoManager::Instance()->Load(L"man_arms.vao");
	m_head_vao = OpenGL::VaoManager::Instance()->Load(L"man_head.vao");
	m_up_vao = OpenGL::VaoManager::Instance()->Load(L"man_up.vao");
	m_hair_vao = OpenGL::VaoManager::Instance()->Load(L"man_hair.vao");

	m_diffuse_map = OpenGL::Texture2DManager::Instance()->Load(L"male_skin.png");
	m_normal_map = OpenGL::Texture2DManager::Instance()->Load(L"male_skin_normal.png");

	m_rc.reset(new OpenGL::RenderContextSkinning);
	m_weapon_rc.reset(new OpenGL::RenderContextBumpMapping);

	m_tc.reset(new OpenGL::TextureContext);	

	m_dir.Set(0, 0, 1);
	m_speed = 0;

	m_animation.resize(5);
	std::fill(m_animation.begin(), m_animation.end(), 0);

	m_state = STATE_STAY;

	m_back_rotation = 0;

	m_aiming = false;

	//	to initialize audio call instance
	Audio::AudioManager::Instance();
	for (int i = 0; i < sizeof(m_players)/sizeof(m_players[0]); ++i)
	{
		m_players[i].Init();
	}

	m_weapon = Utility::WeaponTypeManager::Instance()->Load(L"mini14.weapon");

	m_weapon_body = OpenGL::VaoManager::Instance()->Load(System::string(m_weapon->GetBody().m_geom_name));
	m_weapon_holder = OpenGL::VaoManager::Instance()->Load(System::string(m_weapon->GetHolder().m_geom_name));
	m_weapon_backsight = OpenGL::VaoManager::Instance()->Load(System::string(m_weapon->GetBacksight().m_geom_name));
	m_weapon_light = OpenGL::VaoManager::Instance()->Load(System::string(m_weapon->GetLight().m_geom_name));

	m_weapon_diffuse_map = OpenGL::Texture2DManager::Instance()->Load(L"mini14.png");
	m_weapon_normal_map = OpenGL::Texture2DManager::Instance()->Load(L"mini14_normal.png");		
	m_horizontal_rotation = 0;
}

void CharacterControl::Forward()
{
	if (m_state != STATE_GO_FORWARD)
	{
		m_animation[0] = 0;
		m_armature->GetArmatureAnimation().DisableAllTracks();
		m_armature->GetArmatureAnimation().EnableTrack(L"walk", true);

		m_speed = 5;
		m_state = STATE_GO_FORWARD;
	}
	else
	{
		m_armature->GetArmatureAnimation().EnableTrack(L"stand", false);
	}
}

void CharacterControl::Die()
{
	m_animation[0] = 0;
	m_armature->GetArmatureAnimation().DisableAllTracks();
	m_armature->GetArmatureAnimation().EnableTrack(L"die", true);

	m_speed = 0;
}

void CharacterControl::Stop()
{
	if (m_state != STATE_STAY)
	{
		m_animation[0] = 0;
		m_armature->GetArmatureAnimation().DisableAllTracks();
		m_armature->GetArmatureAnimation().EnableTrack(L"stand", true);

		m_speed = 0;
		m_state = STATE_STAY;
	}
	else
	{
	}
}

void CharacterControl::Aiming(bool v)
{
	m_aiming = v;
}

void CharacterControl::RotateHorizontal(float angle)
{	
	m_horizontal_rotation += angle;
	m_location = m_location*Math::mat4::CreateRotation(0, -1, 0, angle);
	m_dir.Set(0, 0, 1);
	m_dir = m_location.RotationPart() * m_dir;
}

void CharacterControl::RotateVertical(float angle)
{
	Utility::Bone* bone = m_armature->GetBoneByName(L"Back");

	m_back_rotation += angle;

	if (m_back_rotation > Math::PI / 2.0)
		m_back_rotation = Math::PI / 2.0;
	if (m_back_rotation < -Math::PI / 2.0)
		m_back_rotation = -Math::PI / 2.0;

	bone->SetBoneMatrix(Math::mat4::CreateRotation(-1, 0, 0, m_back_rotation));

	//m_dir = Math::mat4::CreateRotation(1, 0, 0, angle).RotationPart() * m_dir;
}

void CharacterControl::Fire()
{
	Audio::Sound* snd = Audio::AudioManager::Instance()->Load(m_weapon->GetSoundShoot().m_sound_name);
	m_players->SetSound(snd);
	m_players->Play();

	Math::vec3 start = GetRightHandTransform().TranslationPart();
	Math::vec3 dir = GetDirection();
	Math::vec3 point;
	if (m_field->GetTerrain()->IntersectWithRay(start, dir, point))
	{
		m_field->Hit(point, 0.5);
	}
}

void CharacterControl::Update(float dt)
{		
	if (m_speed != 0)
		m_animation[0] += dt*10.0*m_speed;
	else
		m_animation[0] += dt*10.0;
	Math::vec3 pos = m_location.TranslationPart();	
	pos += m_dir*m_speed*dt;

	pos.Y() = m_field->GetTerrain()->GetHeight(pos.X(), pos.Z());
	m_location = Math::mat4::CreateTranslate(pos)*m_location.RotationPart4x4();

	Math::vec3 cam_pos(m_location.TranslationPart());
	cam_pos -= m_dir * 5.0f;
	cam_pos.Y() = pos.Y() + 3;

	m_camera->SetPositionAndTarget(cam_pos, m_location.TranslationPart()+Math::vec3(0,1.8,0), Math::vec3(0, 1, 0));
}

void CharacterControl::RenderWeapon()
{
	Math::mat4 m1, m2;

	Utility::Bone* arm1 = m_armature->GetBoneByName(L"Thumb_R");
	m1 = arm1->GetAnimatedGlobalMatrix()*arm1->GetWorldMatrix();
	Utility::Bone* arm2 = m_armature->GetBoneByName(L"Thumb_L");
	m2 = arm2->GetAnimatedGlobalMatrix()*arm2->GetWorldMatrix();

	Math::vec3 p1 = (m_location*Math::mat4::CreateRotation(1, 0, 0, -Math::PI/2)*m1 * Math::vec4(0,0,0,1)).XYZ();
	Math::vec3 p2 = (m_location*Math::mat4::CreateRotation(1, 0, 0, -Math::PI/2)*m2 * Math::vec4(0,0,0,1)).XYZ();
	
	m_line.SetLocalTransform(Math::mat4::CreateIdentity());
	m_line.SetProjectionTransform(m_camera->GetProjectionMatrix());
	m_line.SetViewTranform(m_camera->GetViewMatrix());
	m_line.SetColor(1,1,1,1);
	m_line.Draw(p1, p2);

	Math::mat4 test_mat = Math::mat4::CreateTargetCameraMatrix(p1, p2, Math::vec3(0,1,0)).Inversed()*Math::mat4::CreateRotation(1, 0, 0, Math::PI/2);



	m_weapon_rc->SetProjectionMatrix(m_camera->GetProjectionMatrix());
	m_weapon_rc->SetViewMatrix(m_camera->GetViewMatrix());	
	m_weapon_rc->SetLightPosition(Math::vec3(990, 1010, 1010));
	m_weapon_rc->SetAmbientColor(Math::vec4(0,0,0,1));
	m_weapon_rc->SetSpecularColor(Math::vec4(0.8,0.8,0,1));
	m_weapon_rc->SetDiffuseColor(Math::vec4(1,1, 0,1));
	m_weapon_rc->SetSpecularPower(128.0f);

	m_tc->SetTexture0(m_weapon_diffuse_map);
	m_tc->SetTexture1(m_weapon_normal_map);

	m_tc->Bind();

	m_weapon_rc->SetWorldMatrix(test_mat*m_weapon->GetBody().m_transform*Math::mat4::CreateScaling(0.7, 0.7, 0.7));
	m_weapon_rc->Begin();
	m_weapon_body->Bind(m_weapon_rc->GetSupportedVertexAttributes());
	m_weapon_body->Render();
	m_weapon_body->Unbind();

	m_weapon_rc->End();

	m_tc->Unbind();
}

void CharacterControl::Render()
{
	m_rc->SetProjectionMatrix(m_camera->GetProjectionMatrix());
	m_rc->SetViewMatrix(m_camera->GetViewMatrix());	
	m_rc->SetLightPosition(Math::vec3(990, 1010, 1010));
	m_rc->SetAmbientColor(Math::vec4(0,0,0,1));
	m_rc->SetSpecularColor(Math::vec4(0.8,0.8,0,1));
	m_rc->SetDiffuseColor(Math::vec4(1,1, 0,1));
	m_rc->SetSpecularPower(128.0f);

	//m_armature->GetArmatureAnimation().EnableTrack(L"stand", true);

	if (m_aiming)
	{
		m_armature->GetArmatureAnimation().UpdateBones(m_animation[0]);	
		if (m_state == STATE_GO_FORWARD)
			m_armature->GetArmatureAnimation().EnableTrack(L"walk", false);	
		else if (m_state == STATE_STAY)
			m_armature->GetArmatureAnimation().EnableTrack(L"stand", false);	

		m_armature->GetArmatureAnimation().EnableTrack(L"rifle_aiming", true);
		Utility::Bone* l = m_armature->GetBoneByName(L"Shoulder_L");
		Utility::Bone* r = m_armature->GetBoneByName(L"Shoulder_R");
		l->UpdatePose(15, true);		
		r->UpdatePose(15, true);
		m_armature->GetArmatureAnimation().EnableTrack(L"rifle_aiming", false);

		if (m_state == STATE_GO_FORWARD)
			m_armature->GetArmatureAnimation().EnableTrack(L"walk", true);	
		else if (m_state == STATE_STAY)
			m_armature->GetArmatureAnimation().EnableTrack(L"stand", true);	
	}
	else
	{
		m_armature->GetArmatureAnimation().UpdateBones(m_animation[0]);	
		if (m_state == STATE_GO_FORWARD)
			m_armature->GetArmatureAnimation().EnableTrack(L"walk", false);	
		else if (m_state == STATE_STAY)
			m_armature->GetArmatureAnimation().EnableTrack(L"stand", false);	
		m_armature->GetArmatureAnimation().EnableTrack(L"rifle_walk", true);
		Utility::Bone* l = m_armature->GetBoneByName(L"Shoulder_L");
		Utility::Bone* r = m_armature->GetBoneByName(L"Shoulder_R");
		l->UpdatePose(0, true);		
		r->UpdatePose(0, true);
		m_armature->GetArmatureAnimation().EnableTrack(L"rifle_walk", false);
		if (m_state == STATE_GO_FORWARD)
			m_armature->GetArmatureAnimation().EnableTrack(L"walk", true);	
		else if (m_state == STATE_STAY)
			m_armature->GetArmatureAnimation().EnableTrack(L"stand", true);	
	}

	OpenGL::VertexArrayObjectRef meshes[] = { m_hair_vao, m_head_vao, m_arms_vao , m_feet_vao, m_low_vao, m_up_vao };

	m_tc->SetTexture0(m_diffuse_map);
	m_tc->SetTexture1(m_normal_map);
	m_tc->Bind();

	for (int i = 0; i < sizeof(meshes)/sizeof(meshes[0]); ++i)
	{
		for (int j = 0; j < m_armature->GetBonesCount(); ++j)
		{			
			const Math::mat4 m = meshes[i]->GetMeshTransform().Inversed()*/*Math::mat4::CreateRotation(1, 0, 0, -Math::PI/2)*/m_armature->GetBoneByIndex(j)->GetAnimatedGlobalMatrix()*meshes[i]->GetMeshTransform();
			m_rc->SetBoneMatrix(j, m);
		}

		m_rc->SetWorldMatrix(m_location*meshes[i]->GetMeshTransform()*Math::mat4::CreateRotation(1, 0, 0, -Math::PI/2));

		m_rc->Begin();
		meshes[i]->Bind(m_rc->GetSupportedVertexAttributes());
		meshes[i]->Render();
		meshes[i]->Unbind();
	}

	m_rc->End();
	m_tc->Unbind();

	{
		Math::vec3 start = GetRightHandTransform().TranslationPart();
		Math::vec3 dir = GetDirection();
		m_line.SetColor(1, 0, 0, 1);
		m_line.SetLocalTransform(Math::mat4::CreateIdentity());
		m_line.SetProjectionTransform(m_camera->GetProjectionMatrix());
		m_line.SetViewTranform(m_camera->GetViewMatrix());
		m_line.Draw(start, start+10.0f*dir);
	}
	RenderWeapon();

	RenderAxis();
}

const Math::vec3 CharacterControl::GetDirection() const
{
	return (m_location).RotationPart()*
		Math::mat4::CreateRotation(-1, 0, 0, m_back_rotation).RotationPart()
		*Math::vec3(0,0,1);
}

const Math::mat4 CharacterControl::GetRightHandTransform() const
{
	Utility::Bone* arm1 = m_armature->GetBoneByName(L"Thumb_R");
	Math::mat4 m1 = arm1->GetAnimatedGlobalMatrix()*arm1->GetWorldMatrix();
	return m_location*Math::mat4::CreateRotation(1, 0, 0, -Math::PI/2)*m1;
}

void CharacterControl::RenderAxis()
{
	m_line.SetLocalTransform(Math::mat4::CreateIdentity());
	m_line.SetProjectionTransform(m_camera->GetProjectionMatrix());
	m_line.SetViewTranform(m_camera->GetViewMatrix());

	m_line.SetColor(1, 0, 0, 1);
	m_line.Draw(m_location.TranslationPart(), m_location.TranslationPart() + Math::vec3(3, 0, 0));
	m_line.SetColor(0, 1, 0, 1);
	m_line.Draw(m_location.TranslationPart(), m_location.TranslationPart() + Math::vec3(0, 3, 0));
	m_line.SetColor(0, 0, 1, 1);
	m_line.Draw(m_location.TranslationPart(), m_location.TranslationPart() + Math::vec3(0, 0, 3));
}