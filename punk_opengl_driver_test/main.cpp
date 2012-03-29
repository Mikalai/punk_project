#include "../punk_engine/system/string.h"
#include "../punk_engine/system/system.h"
#include "../punk_engine/math/math.h"
#include "../punk_engine/images/images.h"
#include "../punk_engine/utility/utility.h"
#include "../punk_engine/system/driver/video/driver.h"
#include "../punk_engine/system/application/application.h"

class Test
{
	OpenGL::Driver m_driver;
public:
	Test()
	{
		m_driver.Start(System::Window::GetInstance());
		m_driver.SetClearColor(0.7, 0.6, 0, 1);
	}

	void OnIdle(System::Event* event)
	{
		m_driver.ClearBuffer(OpenGL::Driver::COLOR_BUFFER|OpenGL::Driver::DEPTH_BUFFER);	
		m_driver.SwapBuffers();
	}
};

int main()
{
	System::Window::GetInstance()->SetTitle(L"Punk OpenGL Driver Test");
	System::Mouse::GetInstance()->LockInWindow(false);
	OpenGL::Module module;
	module.Init();
	Test test;
	System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(&test, &Test::OnIdle));
	System::Window::GetInstance()->Loop();

	module.Destroy();
	return 0;
}

////#define _CRTDBG_MAP_ALLOC
////#include <stdlib.h>
////#include <crtdbg.h>
//
//#include "../punk_engine/system/string.h"
//#include "../punk_engine/system/system.h"
//#include "../punk_engine/math/math.h"
//#include "../punk_engine/images/images.h"
//#include "../punk_engine/utility/utility.h"
//#include "../punk_engine/system/driver/video/driver.h"
//#include "../punk_engine/system/application/application.h"
//
//class Test
//{
//	OpenGL::Driver* driver;
//	Utility::RawScene scene;
//	Utility::SkinAnimation* anim;
//
//	Utility::Model mdl;
//
//	OpenGL::VertexArrayObject* vao;
//	ShaderProgram* program;
//	Utility::Camera* camera; 
//	OpenGL::TextureContext* m_texture_context;
//	Math::mat4* skelet;
//	OpenGL::VertexArrayObject* skin_vao;
//	ShaderProgram* skin_program;
//	ShaderProgram* program_2d;
//	int bones_count;
//
//	OpenGL::VertexArrayObject* m_axis;
//	OpenGL::VertexArrayObject* m_bone_vao;
//	Utility::Model m_axis_mdl;
//	Utility::Model m_bone_mdl;
//	float a1;
//	float a2;
//public:
//
//	Test()
//	{
//		driver = new OpenGL::Driver;
//		try
//		{			
//			driver->Start(System::Window::GetInstance());
//		}
//		catch (System::SystemError& err)
//		{
//			wprintf(L"%s\n", err.Message().Data());
//			exit(0);
//		}
//
//		try
//		{
//			mdl.LoadPunkModel(System::string("D:\\project\\punk_project\\punk_engine\\blender\\something.pmd"));
//			m_axis_mdl.LoadPunkModel(System::string("D:\\project\\punk_project\\punk_engine\\blender\\axis.pmd"));
//			m_bone_mdl.LoadPunkModel(System::string("D:\\project\\punk_project\\punk_engine\\blender\\bone.pmd"));
//		}
//		catch (Utility::UtilityError& err)
//		{
//			wprintf(L"%s\n", err.w_what().Data());
//		}
//		catch (System::SystemError& err)
//		{
//			wprintf(L"%s\n", err.Message().Data());
//		}
//
//
//		Utility::StaticMesh* mesh = mdl.CookStaticMesh();
//		Utility::StaticMesh* axis_mesh = m_axis_mdl.CookStaticMesh();
//		Utility::StaticMesh* bone_mesh = m_bone_mdl.CookStaticMesh();
//		Utility::SkinnedMesh* smesh;
//
//		Utility::Material mat = mdl.m_materials.at(L"diffuse");
//		mdl.CookSkinnedMesh(smesh, skelet, bones_count);
//		mdl.CookAnimation(L"Run", anim);
//
//		//	scene.CookAnimation(L"ArmatureAction", anim);
//
//		m_bone_vao = new OpenGL::VertexArrayObject();
//		m_bone_vao->Create(bone_mesh->GetVertexBuffer(), bone_mesh->GetVertexBufferSize(), bone_mesh->GetIndexBuffer(), bone_mesh->GetVertexCount(), bone_mesh->GetIndexCount(), bone_mesh->GetOneVertexSize(), bone_mesh->GetVertexComponentCode());
//
//		m_axis = new OpenGL::VertexArrayObject();
//		m_axis->Create(axis_mesh->GetVertexBuffer(), axis_mesh->GetVertexBufferSize(), axis_mesh->GetIndexBuffer(), axis_mesh->GetVertexCount(), axis_mesh->GetIndexCount(), axis_mesh->GetOneVertexSize(), axis_mesh->GetVertexComponentCode());
//
//		vao = new OpenGL::VertexArrayObject();
//		vao->Create(mesh->GetVertexBuffer(), mesh->GetVertexBufferSize(), mesh->GetIndexBuffer(), mesh->GetVertexCount(), mesh->GetIndexCount(), mesh->GetOneVertexSize(), mesh->GetVertexComponentCode());
//
//		skin_vao = new OpenGL::VertexArrayObject();
//		skin_vao->Create(smesh->GetVertexBuffer(), smesh->GetVertexBufferSize(), smesh->GetIndexBuffer(), smesh->GetVertexCount(), smesh->GetIndexCount(), smesh->GetOneVertexSize(), smesh->GetVertexComponentCode());
//
//		program_2d = driver->GetShaderProgram(L"solid_color_2d");
//		program = driver->GetShaderProgram(L"static_mesh");
//		skin_program = driver->GetShaderProgram(L"skinning");
//
//		camera = new Utility::Camera();
//		camera->SetPosition(Math::vec3(5,5,-5));
//
//		m_texture_context = new OpenGL::TextureContext();
//		m_texture_context->SetDiffuseMap(driver->GetTexture2D(mat.GetDiffuseMap()));
//		m_texture_context->SetNormalMap(driver->GetTexture2D(mat.GetNormalMap()));
//
//		a1 = 0;
//		a2 = 0;
//
//		System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(this, &Test::OnKey));
//
//		//System::Mouse::GetInstance()->BindCursorToWindow(0);
//	}
//
//	~Test()
//	{
//		driver->Shutdown();
//		delete driver;
//	}
//
//	void OnKey(System::Event* event)
//	{
//		System::KeyDownEvent* key = dynamic_cast<System::KeyDownEvent*>(event);
//
//		if (key == 0)
//			return;
//
//		if (key->key == System::PUNK_KEY_Q)
//			a1 += 0.1;
//		if (key->key == System::PUNK_KEY_E)
//			a2 += 0.1;
//	}
//
//	void Draw(System::Event* event)
//	{
//		try
//		{
//			static float t  = 0, a = 0;
//			static int cur = 0;
//			static int next = cur+1;
//
//			driver->ClearBuffer(OpenGL::Driver::COLOR_BUFFER|OpenGL::Driver::DEPTH_BUFFER|OpenGL::Driver::STENCIL_BUFFER);
//
//			OpenGL::RenderContext context_2d;
//			context_2d.Begin(program_2d);
//			Math::mat4 world = Math::mat4::CreateTranslate(100, 100, 0)*Math::mat4::CreateScaling(100,100,1);
//			Math::mat4 view = Math::mat4::CreateIdentity();
//			Math::mat4 proj = Math::mat4::CreateOrthographicProjection(0, System::Window::GetInstance()->GetWidth(), System::Window::GetInstance()->GetHeight(), 0, -1, 1);
//			program_2d->SetUniformMatrix4f(program_2d->GetUniformLocation("uProjViewWorld"), proj*view*world);
//			program_2d->SetUniformVector4f(program_2d->GetUniformLocation("uDiffuseColor"), Math::vec4(0, 0, 1, 1));
//			program_2d->SetUniformFloat(program_2d->GetUniformLocation("uRadius"), 0.01f);
//
//			context_2d.DisableDepthTest();
//			context_2d.EnableBlending();
//			driver->RenderQuad();
//			context_2d.DisableBlending();
//			context_2d.EnableDepthTest();
//			context_2d.End();
//			driver->SwapBuffers();	
//		/*	OpenGL::RenderContext context;
//			context.Begin(program);
//			m_texture_context->Apply();
//			{
//				Math::mat4 m = Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, 4.0/3.0, 0.01, 100.0) * Math::mat4::CreateTargetCameraMatrix(Math::vec3(0,0,-5), Math::vec3(0,0,0), Math::vec3(0, 1, 0));
//
//				Math::mat4 proj = camera->GetProjectionMatrix();
//				Math::mat4 world = Math::mat4::CreateTranslate(5,5,0);
//				Math::mat4 view = camera->GetViewMatrix();
//				Math::mat3 normal = (view*world).Inversed().Transposed().RotationPart();
//
//				program->SetUniformMatrix4f(program->GetUniformLocation("uView"), view);
//				program->SetUniformMatrix4f(program->GetUniformLocation("uProj"), proj);
//				program->SetUniformMatrix4f(program->GetUniformLocation("uViewWorld"), view*world);
//				program->SetUniformMatrix4f(program->GetUniformLocation("uProjViewWorld"), proj*view*world);
//				program->SetUniformMatrix3f(program->GetUniformLocation("uNormalMatrix"), normal);
//				program->SetUniformVector3f(program->GetUniformLocation("uLightPosition"), Math::vec3(4, 3, 0));
//				program->SetUniformVector3f(program->GetUniformLocation("uEyePosition"), camera->GetPosition());				
//				program->SetUniformVector4f(program->GetUniformLocation("uSpecular"), Math::vec4(1,1,1,1));
//				program->SetUniformVector4f(program->GetUniformLocation("uDiffuse"), Math::vec4(1,1,1,1));
//				program->SetUniformFloat(program->GetUniformLocation("uSpecularPower"), 16.0);
//
//				for (int bone = 0; bone < anim->GetBonesCount(); bone++)
//				{
//					char buf[256];
//					sprintf(buf, "uBones[%d]", bone);
//					Math::mat4 m = anim->GetInterpolatedTransform(bone, cur, next, t);
//					program->SetUniformVector4f(program->GetUniformLocation("uAmbient"), Math::vec4(bone/20.0f,(20-bone)/20.0f,bone/20.0f,1));
//					//	if (m[15] != 1.0)
//					//	throw;
//
//					//		Math::mat4 src = scene.GetSourceGlobalMatrix(bone);
//					//m = anim->GetGlobal(1, 0);//scene.m_skeleton[L"bottom"  ].m_matrix_local;	
//					//m = Math::mat4::CreateRotation(1,0,0, a1);
//					const Utility::Bone& b = anim->GetBone(bone);					
//					program->SetUniformMatrix4f(program->GetUniformLocation("uWorld"), Math::mat4::CreateRotation(1,0,0,Math::PI/2)*Math::mat4::CreateTranslate(5, 0, 0)*m*b.GetMatrix()*Math::mat4::CreateRotation(1,0,0,-Math::PI/2));				
//					driver->Render(m_bone_vao);
//				}
//				
//				program->SetUniformMatrix4f(program->GetUniformLocation("uWorld"), world);
//				driver->Render(m_axis);
//				context.End();/**/
//			//}
//			/**/
//
//			/*context.Begin(skin_program);
//			m_texture_context->Apply();
//			{
//				//Math::mat4 m = Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, 4.0/3.0, 0.01, 100.0) * Math::mat4::CreateTargetCameraMatrix(Math::vec3(0,0,-5), Math::vec3(0,0,0), Math::vec3(0, 1, 0));
//
//				Math::mat4 proj = camera->GetProjectionMatrix();
//				Math::mat4 world = Math::mat4::CreateScaling(0.1,0.1,0.1)*Math::mat4::CreateRotation(1, 0, 0, -Math::PI/2);
//				a+= 0.0001;
//				Math::mat4 view = camera->GetViewMatrix();
//				Math::mat3 normal = (view*world).Inversed().Transposed().RotationPart();
//
//				skin_program->SetUniformMatrix4f(skin_program->GetUniformLocation("uWorld"), world);
//				skin_program->SetUniformMatrix4f(skin_program->GetUniformLocation("uView"), view);
//				skin_program->SetUniformMatrix4f(skin_program->GetUniformLocation("uProj"), proj);
//				skin_program->SetUniformMatrix4f(skin_program->GetUniformLocation("uViewWorld"), view*world);
//				skin_program->SetUniformMatrix4f(skin_program->GetUniformLocation("uProjViewWorld"), proj*view*world);
//				skin_program->SetUniformMatrix3f(skin_program->GetUniformLocation("uNormalMatrix"), normal);
//				skin_program->SetUniformVector3f(skin_program->GetUniformLocation("uLightPosition"), Math::vec3(40, 30, 0));
//				skin_program->SetUniformVector3f(skin_program->GetUniformLocation("uEyePosition"), camera->GetPosition());
//				skin_program->SetUniformVector4f(skin_program->GetUniformLocation("uAmbient"), Math::vec4(0,0,0,1));
//				skin_program->SetUniformVector4f(skin_program->GetUniformLocation("uSpecular"), Math::vec4(1,1,1,1));
//				skin_program->SetUniformVector4f(skin_program->GetUniformLocation("uDiffuse"), Math::vec4(1,1,1,1));
//
//				//Math::mat4 m;
//
//				for (int bone = 0; bone < anim->GetBonesCount(); bone++)
//				{
//					char buf[256];
//					sprintf(buf, "uBones[%d]", bone);
//					Math::mat4 m = anim->GetInterpolatedTransform(bone, cur, next, t);
//
//					//	if (m[15] != 1.0)
//					//	throw;/**/
//
//					//		Math::mat4 src = scene.GetSourceGlobalMatrix(bone);
//					//m = anim->GetGlobal(1, 0);//scene.m_skeleton[L"bottom"  ].m_matrix_local;	
//					//m = Math::mat4::CreateRotation(1,0,0, a1);
//		/*!!!!			skin_program->SetUniformMatrix4f(skin_program->GetUniformLocation(buf), m);				
//				}
//				/*				//m = anim->GetGlobal(0,1); //Math::linear_interpolation(anim->GetGlobal(cur, 1), anim->GetGlobal(next, 1), t);
//				m = Math::linear_interpolation(anim->GetGlobal(cur, 1), anim->GetGlobal(next, 1), t);
//				skin_program->SetUniformMatrix4f(skin_program->GetUniformLocation("uBones[1]"), m);
//				//m = anim->GetGlobal(0,2);// Math::linear_interpolation(anim->GetGlobal(cur, 2), anim->GetGlobal(next, 2), t);
//				//m = m*scene.m_skeleton_animation[L"test_action"].m_pose[L"up"][20].m_rotation.ToMatrix4x4();;//anim->GetGlobal(1, 2);//scene.m_skeleton[L"up"    ].m_matrix_local;//Math::mat4::CreateIdentity();//
//				m = Math::linear_interpolation(anim->GetGlobal(cur, 2), anim->GetGlobal(next, 2), t);
//				skin_program->SetUniformMatrix4f(skin_program->GetUniformLocation("uBones[2]"), m);*/
//
//		/*		t += 0.01;
//				if (t >= 1)
//				{
//					cur++;
//					next = cur + 1;
//					if (cur == anim->GetFramesCount() - 1)
//					{
//						cur = 0;
//						next = 1;
//					}
//					t = 0;
//				}/**/
//
//				//skin_program->SetUniformMatrix4f(skin_program->GetUniformLocation("uBones[3]"), skelet[3].Transposed());
//
//		//		skin_program->SetUniformFloat(skin_program->GetUniformLocation("uSpecularPower"), 16.0);
//	//		}
//		//	driver->Render(skin_vao);
//			///context.End();						
//		}
//		catch(System::SystemError& err)
//		{
//			wprintf(L"%s\n", err.Message().Data());
//			exit(0);
//		}
//	}
//};
//
//int main()
//{	
//	//_CrtSetBreakAlloc(469);
//
//	System::Window::GetInstance()->SetTitle(L"Punk OpenGL Driver Test");
//	Test* t = new Test();;
//	System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(t, &Test::Draw));
//	System::Window::GetInstance()->Loop();
//	delete t;
//	//_CrtDumpMemoryLeaks();
//	return 0;
//}*/