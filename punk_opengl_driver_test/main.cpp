//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

#include "../punk_engine/system/string.h"
#include "../punk_engine/system/system.h"
#include "../punk_engine/math/math.h"
#include "../punk_engine/images/images.h"
#include "../punk_engine/utility/utility.h"
#include "../punk_engine/system/driver/video/driver.h"

class Test
{
	OpenGL::Driver* driver;
	Utility::Model mdl;
	Utility::SkinAnimation* anim;

	OpenGL::VertexArrayObject* vao;
	ShaderProgram* program;
	Utility::Camera* camera; 
	OpenGL::TextureContext* m_texture_context;
	Math::mat4* skelet;
	OpenGL::VertexArrayObject* skin_vao;
	ShaderProgram* skin_program;
	int bones_count;

	float a1;
	float a2;
public:

	Test()
	{
		driver = new OpenGL::Driver;
		try
		{
			driver->Start(System::Application::GetInstance()->GetWindow());
		}
		catch (System::SystemError& err)
		{
			wprintf(L"%s\n", err.Message().Data());
			exit(0);
		}

		try
		{
			mdl.LoadPunkModel(System::string("d:\\project\\punk_project\\punk_engine\\blender\\naked_brutal_man23.pmd"));
		}
		catch (Utility::UtilityError& err)
		{
			wprintf(L"%s\n", err.w_what().Data());
		}
		catch (System::SystemError& err)
		{
			wprintf(L"%s\n", err.Message().Data());
		}


		Utility::StaticMesh* mesh = mdl.CookStaticMesh();
		Utility::SkinnedMesh* smesh;
		
		mdl.CookSkinnedMesh(smesh, skelet, bones_count);
		mdl.CookAnimation(L"ArmatureAction", anim);

		vao = new OpenGL::VertexArrayObject();
		vao->Create(mesh->GetVertexBuffer(), mesh->GetVertexBufferSize(), mesh->GetIndexBuffer(), mesh->GetVertexCount(), mesh->GetIndexCount(), mesh->GetOneVertexSize(), mesh->GetVertexComponentCode());

		skin_vao = new OpenGL::VertexArrayObject();
		skin_vao->Create(smesh->GetVertexBuffer(), smesh->GetVertexBufferSize(), smesh->GetIndexBuffer(), smesh->GetVertexCount(), smesh->GetIndexCount(), smesh->GetOneVertexSize(), smesh->GetVertexComponentCode());

		program = driver->GetShaderProgram(L"skinning");
		skin_program = driver->GetShaderProgram(L"skinning");

		camera = new Utility::Camera();
		camera->SetPosition(Math::vec3(5,0,-5));

		m_texture_context = new OpenGL::TextureContext();
		m_texture_context->SetDiffuseMap(driver->GetTexture2D(mdl.m_materials[mdl.m_material].diffuse_map));
		m_texture_context->SetNormalMap(driver->GetTexture2D(mdl.m_materials[mdl.m_material].normal_map));

		a1 = 0;
		a2 = 0;

		System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(this, &Test::OnKey));

	}

	~Test()
	{
		driver->Shutdown();
		delete driver;
	}

	void OnKey(System::Event* event)
	{
		System::KeyDownEvent* key = dynamic_cast<System::KeyDownEvent*>(event);

		if (key == 0)
			return;

		if (key->key == System::PUNK_KEY_Q)
			a1 += 0.1;
		if (key->key == System::PUNK_KEY_E)
			a2 += 0.1;
	}

	void Draw(System::Event* event)
	{
		try
		{
			driver->ClearBuffer(OpenGL::Driver::COLOR_BUFFER|OpenGL::Driver::DEPTH_BUFFER|OpenGL::Driver::STENCIL_BUFFER);

			OpenGL::RenderContext context;
	/*		context.Begin(program);
			m_texture_context->Apply();
			{
			Math::mat4 m = Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, 4.0/3.0, 0.01, 100.0) * Math::mat4::CreateTargetCameraMatrix(Math::vec3(0,0,-5), Math::vec3(0,0,0), Math::vec3(0, 1, 0));

			Math::mat4 proj = camera->GetProjectionMatrix();
			Math::mat4 world = Math::mat4::CreateTranslate(3,3,0);
			Math::mat4 view = camera->GetViewMatrix();
			Math::mat3 normal = (view*world).Inversed().Transposed().RotationPart();
			program->SetUniformMatrix4f(program->GetUniformLocation("uWorld"), world);
			program->SetUniformMatrix4f(program->GetUniformLocation("uView"), view);
			program->SetUniformMatrix4f(program->GetUniformLocation("uProj"), proj);
			program->SetUniformMatrix4f(program->GetUniformLocation("uViewWorld"), view*world);
			program->SetUniformMatrix4f(program->GetUniformLocation("uProjViewWorld"), proj*view*world);
			program->SetUniformMatrix3f(program->GetUniformLocation("uNormalMatrix"), normal);
			program->SetUniformVector3f(program->GetUniformLocation("uLightPosition"), Math::vec3(4, 3, 0));
			program->SetUniformVector3f(program->GetUniformLocation("uEyePosition"), camera->GetPosition());
			program->SetUniformVector4f(program->GetUniformLocation("uAmbient"), Math::vec4(0,0,0,1));
			program->SetUniformVector4f(program->GetUniformLocation("uSpecular"), Math::vec4(1,1,1,1));
			program->SetUniformVector4f(program->GetUniformLocation("uDiffuse"), Math::vec4(1,1,1,1));
			program->SetUniformFloat(program->GetUniformLocation("uSpecularPower"), 16.0);
			}
			driver->Render(vao);
			context.End();/**/
/**/
			static float t  = 0, a = 0;
			static int cur = 0;
			static int next = cur+1;
			context.Begin(skin_program);
			m_texture_context->Apply();
			{
				Math::mat4 m = Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, 4.0/3.0, 0.01, 100.0) * Math::mat4::CreateTargetCameraMatrix(Math::vec3(0,0,-5), Math::vec3(0,0,0), Math::vec3(0, 1, 0));

				Math::mat4 proj = camera->GetProjectionMatrix();
				Math::mat4 world;// = Math::mat4::CreateRotation(0, 1, 0, a);
				a+= 0.0001;
				Math::mat4 view = camera->GetViewMatrix();
				Math::mat3 normal = (view*world).Inversed().Transposed().RotationPart();

				skin_program->SetUniformMatrix4f(skin_program->GetUniformLocation("uWorld"), world);
				skin_program->SetUniformMatrix4f(skin_program->GetUniformLocation("uView"), view);
				skin_program->SetUniformMatrix4f(skin_program->GetUniformLocation("uProj"), proj);
				skin_program->SetUniformMatrix4f(skin_program->GetUniformLocation("uViewWorld"), view*world);
				skin_program->SetUniformMatrix4f(skin_program->GetUniformLocation("uProjViewWorld"), proj*view*world);
				skin_program->SetUniformMatrix3f(skin_program->GetUniformLocation("uNormalMatrix"), normal);
				skin_program->SetUniformVector3f(skin_program->GetUniformLocation("uLightPosition"), Math::vec3(40, 30, 0));
				skin_program->SetUniformVector3f(skin_program->GetUniformLocation("uEyePosition"), camera->GetPosition());
				skin_program->SetUniformVector4f(skin_program->GetUniformLocation("uAmbient"), Math::vec4(0,0,0,1));
				skin_program->SetUniformVector4f(skin_program->GetUniformLocation("uSpecular"), Math::vec4(1,1,1,1));
				skin_program->SetUniformVector4f(skin_program->GetUniformLocation("uDiffuse"), Math::vec4(1,1,1,1));

				//Math::mat4 m;
				
				for (int bone = 0; bone < anim->GetBonesCount(); bone++)
				{
					char buf[256];
					sprintf(buf, "uBones[%d]", bone);
					m = Math::linear_interpolation(anim->GetGlobal(cur, bone), anim->GetGlobal(next, bone), t); //mdl.m_skeleton_animation[L"test_action"].m_pose[L"bottom"][20].m_rotation.ToMatrix4x4();
					//m = anim->GetGlobal(1, 0);//mdl.m_skeleton[L"bottom"  ].m_matrix_local;	
					//m = Math::mat4::CreateRotation(1,0,0, a1);
					skin_program->SetUniformMatrix4f(skin_program->GetUniformLocation(buf), m);				
				}
/*				//m = anim->GetGlobal(0,1); //Math::linear_interpolation(anim->GetGlobal(cur, 1), anim->GetGlobal(next, 1), t);
				m = Math::linear_interpolation(anim->GetGlobal(cur, 1), anim->GetGlobal(next, 1), t);
				skin_program->SetUniformMatrix4f(skin_program->GetUniformLocation("uBones[1]"), m);
				//m = anim->GetGlobal(0,2);// Math::linear_interpolation(anim->GetGlobal(cur, 2), anim->GetGlobal(next, 2), t);
				//m = m*mdl.m_skeleton_animation[L"test_action"].m_pose[L"up"][20].m_rotation.ToMatrix4x4();;//anim->GetGlobal(1, 2);//mdl.m_skeleton[L"up"    ].m_matrix_local;//Math::mat4::CreateIdentity();//
				m = Math::linear_interpolation(anim->GetGlobal(cur, 2), anim->GetGlobal(next, 2), t);
				skin_program->SetUniformMatrix4f(skin_program->GetUniformLocation("uBones[2]"), m);*/

				t += 0.0001;
				if (t >= 1)
				{
					cur++;
					next = cur + 1;
					if (cur == anim->GetFramesCount() - 1)
					{
						next = 0;
					}

					if (cur == anim->GetFramesCount())
					{
						cur = 0;
						next = 1;
					}
					t = 0;
				}

				//skin_program->SetUniformMatrix4f(skin_program->GetUniformLocation("uBones[3]"), skelet[3].Transposed());

				skin_program->SetUniformFloat(skin_program->GetUniformLocation("uSpecularPower"), 16.0);
			}
			driver->Render(skin_vao);
			context.End();
			
			
			driver->SwapBuffers();	
		}
		catch(System::SystemError& err)
		{
			wprintf(L"%s\n", err.Message().Data());
			exit(0);
		}
	}
};

int main()
{	
	//_CrtSetBreakAlloc(469);

	Test* t = new Test();;

	System::Application::GetInstance()->GetWindow()->SetTitle(L"OpenGL Test");	
	System::Application::GetInstance()->GetEventManager()->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(t, &Test::Draw));
	System::Application::GetInstance()->Run();
	delete t;
	System::Application::GetInstance()->Release();

	//_CrtDumpMemoryLeaks();
	return 0;
}