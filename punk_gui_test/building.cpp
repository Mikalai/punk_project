#include "building.h"

Building::Building()
{	
	m_rc.reset(new OpenGL::RenderContextBumpMapping);
	m_tc.reset(new OpenGL::TextureContext);	

	m_object = Utility::ObjectManager::Instance()->Load(L"hummer_chassis_transform.object");

//	m_player.SetSound(Audio::AudioManager::Instance()->Load(m_object->GetChild(L"sound_rotate_wheel", true)->GetSound()->GetFilename()));
	//m_player.Play(true);
}

void Building::Render(Utility::CameraRef camera, Utility::TerrainRef terrain)
{
	m_rc->SetProjectionMatrix(camera->GetProjectionMatrix());
	m_rc->SetViewMatrix(camera->GetViewMatrix());	

	Render(m_object, Math::mat4::CreateTranslate(1000, 
		terrain->GetHeight(1000, 1000), 1000)*Math::mat4::CreateRotation(1, 0, 0, -Math::PI/2.0)
		, camera->GetViewMatrix(), camera->GetProjectionMatrix());
}

void Building::Render(Utility::ObjectRef object, const Math::mat4& parent, const Math::mat4& view, const Math::mat4& proj)
{	
	Math::mat4 mat;
	if (object->GetName() == L"wheel")
	{
		static float time = 0;
		Utility::ObjectRef wheel = m_object->GetChild(L"wheel");
		wheel->AsAnimationMixer().EnableTrack(L"wheel", true);
		Math::vec3 pos = wheel->AsAnimationMixer().GetPosition(time);
		Math::quat rot = wheel->AsAnimationMixer().GetRotation(time);
		mat = rot.ToMatrix4x4();
		time += 0.1;
	}

	if (!object->IsCollisionVolume())
	{
		if (object->GetMesh() )
		{
			OpenGL::VertexArrayObject* vao = OpenGL::VaoManager::Instance()->Load(object->GetName() + L".vao");
			if (vao)
			{
				m_rc->SetLightPosition(Math::vec3(990, 1010, 1010));
				m_rc->SetAmbientColor(Math::vec4(0,0,0,1));
				m_rc->SetSpecularColor(Math::vec4(1,1,1,1));
				m_rc->SetDiffuseColor(Math::vec4(1,1,1,1));
				m_rc->SetSpecularPower(128.0f);
				m_rc->SetWorldMatrix(parent*object->GetLocalMatrix()*mat);

				m_tc->SetTexture0(OpenGL::Texture2DManager::Instance()->Load(object->GetMaterial().GetDiffuseMap()));
				m_tc->SetTexture1(OpenGL::Texture2DManager::Instance()->Load(object->GetMaterial().GetNormalMap()));

				m_tc->Bind();
				m_rc->Begin();

				vao->Bind(m_rc->GetSupportedVertexAttributes());
				vao->Render();
				vao->Unbind();
				m_rc->End();
				m_tc->Unbind();
			}
		}
	}
	else
	{		
		render.Render(object->AsBoundingBox(), parent*object->GetLocalMatrix()*mat, view, proj);
		render.RenderAABB(object->AsBoundingBox(), parent*object->GetLocalMatrix()*mat, view, proj);
	}

	for each (auto child in object->GetChildren())
	{
		Render(child.get(), parent*object->GetLocalMatrix()*mat, view, proj);
	}
}