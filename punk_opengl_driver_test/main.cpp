#include "../punk_engine/system/string.h"
#include "../punk_engine/system/system.h"
#include "../punk_engine/math/math.h"
#include "../punk_engine/images/images.h"
#include "../punk_engine/utility/utility.h"
#include "../punk_engine/system/driver/video/driver.h"
#include "../punk_engine/system/application/application.h"

using namespace OpenGL;

class Test
{
	OpenGL::Driver m_driver;
	std::auto_ptr<OpenGL::RenderContextSolid3D> m_solid_context;
	std::auto_ptr<OpenGL::RenderContextTextured3D> m_textured_context;
	std::auto_ptr<OpenGL::RenderContextTerrain> m_terrain_context;
	std::auto_ptr<OpenGL::RenderContextBumpMapping> m_bump_mapping;
	std::auto_ptr<OpenGL::QuadObject> m_quad;
	std::auto_ptr<OpenGL::GridObject> m_grid;
	std::auto_ptr<OpenGL::StaticObject> m_static_vao;
	std::auto_ptr<Utility::StaticMesh> m_static_mesh;
	ImageModule::RGBAImage m_image;
	ImageModule::RGBImage m_gray_image;
	std::auto_ptr<OpenGL::Texture2D> m_texture;
	std::auto_ptr<OpenGL::Texture2D> m_height_map;
	std::auto_ptr<OpenGL::TextureContext> m_texture_context;
	Math::Camera m_camera;
	float x, y, z;
public:
	
	Test()
	{
		Utility::Scene scene;
		scene.Load(L"simple_house.pmd");
		m_static_mesh.reset(scene.CookStaticMesh(L"Cube"));
		System::Buffer buffer;
		m_static_mesh->Save(buffer);
		System::BinaryFile::Save(System::Environment::GetModelFolder() + L"simple_house.mesh", buffer);

		x = y = z = 10;
		m_driver.Start(System::Window::GetInstance());
		m_driver.SetClearColor(0.7, 0.6, 0, 1);
		m_solid_context.reset(new OpenGL::RenderContextSolid3D());
		m_textured_context.reset(new OpenGL::RenderContextTextured3D());
		m_bump_mapping.reset(new OpenGL::RenderContextBumpMapping());

		m_static_vao.reset(new OpenGL::StaticObject());
		m_static_vao->SetStaticObject(m_static_mesh.get());
		m_static_vao->Init();

		m_quad.reset(new OpenGL::QuadObject());
		m_quad->Init();

		m_grid.reset(new OpenGL::GridObject());
		m_grid->SetWidth(1);
		m_grid->SetHeight(1);
		m_grid->SetHeightSlice(16);
		m_grid->SetWidthSlice(16);
		m_grid->Init();/**/

		m_image = ImageModule::Importer().LoadRGBA(System::Environment::GetTexutreFolder() + L"diffuse_map.png");
		m_gray_image = ImageModule::Importer().LoadRGB(System::Environment::GetTexutreFolder() + L"house_normal.png");
		m_height_map.reset(new OpenGL::Texture2D(m_gray_image));		

		m_terrain_context.reset(new OpenGL::RenderContextTerrain());		

		m_texture.reset(new OpenGL::Texture2D(m_image));
		m_texture_context.reset(new OpenGL::TextureContext());
		m_texture_context->SetDiffuseMap(m_texture.release());
		m_texture_context->SetNormalMap(m_height_map.release());
	//	m_camera.SetPositionAndDirection(Math::vec3(0,1.8, 0), Math::vec3(0, 0, 1), Math::vec3(0,1,0));
	//	m_camera.SetProperties(Math::PI/4, 1.3, 1, 1000);		

	}

	void OnMouseMove(System::Event* event)
	{
		System::MouseMoveEvent& e = static_cast<System::MouseMoveEvent&>(*event);
		m_camera.AdvanceLongitude(float(e.x - e.x_prev)*0.001f);
		m_camera.AdvanceLatitude(float(e.y-e.y_prev)*0.001f);

	}

	void OnKeyDown(System::Event* event)
	{
		System::KeyDownEvent& e = static_cast<System::KeyDownEvent&>(*event);
		switch (e.key)
		{
		case System::PUNK_KEY_A:
			x -= 1;
			break;
		case System::PUNK_KEY_D:
			x += 1;
			break;
		}
	}

	void OnIdle(System::Event* event)
	{		
		m_driver.ClearBuffer(OpenGL::Driver::COLOR_BUFFER|OpenGL::Driver::DEPTH_BUFFER);	
			
/*		static Math::vec3 sun(100, 100, 100);
		static float angle = 0;
		
		Math::mat4 proj = m_camera.GetProjectionMatrix();
		Math::vec3 camera_position = m_camera.GetPosition();
		Math::mat4 projViewWorld = m_camera.GetViewProjectionMatrix();
		Math::mat3 normalTransform = m_camera.GetViewMatrix().RotationPart();

		int passCount = 1;
		
		int start = -4;
		int end = 4;
		
		

		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		for (int level = 1; level < 6; level++)
		{
			for (int i = start; i < end; i++)
			{
				for (int j = start; j < end; j++)
				{
					Math::vec2 position((int)camera_position[0], (int)camera_position[2]);

					Math::mat4 world_transform = Math::mat4::CreateTranslate(position[0], 0, position[1]);
					//if (j == -1)
					//continue;
					if (level != 1)
						if (!(j < start+2 || j >= end - 2 || i < start+2 || i >= end - 2))
							continue;

					//if (!Common::Camera::GetActiveCamera()->BoxInFrustum(m_vao->GetBoundingBox().Transform(world_transform)))
					//continue;

					m_terrain_context->SetWorldMatrix(Math::mat4::CreateIdentity());
					m_terrain_context->SetViewMatrix(m_camera.GetViewMatrix());
					m_terrain_context->SetProjectionMatrix(proj);
					m_terrain_context->SetNormalTransform(normalTransform);
					m_terrain_context->SetLightDirection(sun.Normalized());
					m_terrain_context->SetDiffuseColor(Math::vec4(1,1,0,1));
					m_terrain_context->SetPosition(position);
					m_terrain_context->SetLevel(level);					
					m_terrain_context->SetI(i);
					m_terrain_context->SetJ(j);
					
					//	angle += 0.000001;
					
		

					m_terrain_context->Begin();
					m_texture_context->Bind();
					m_grid->Bind(m_terrain_context->GetSupportedVertexAttributes());
					m_grid->Render();
					m_grid->Unbind();
					m_texture_context->Unbind();
					m_terrain_context->End();
				}
			}
		}	*/	
		static float a = 0;
		a+= 0.001;
		m_bump_mapping->SetWorldMatrix(Math::mat4::CreateTranslate(0, 0, 0));
		m_bump_mapping->SetViewMatrix(Math::mat4::CreateTargetCameraMatrix(Math::vec3(10*sin(a), 10, 10*cos(a)), Math::vec3(0, 0, 0), Math::vec3(0, 1, 0)));
		m_bump_mapping->SetProjectionMatrix(Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, 1.3, 0.1, 100.0));
		m_bump_mapping->SetAmbientColor(Math::vec4(0,0,0,0));
		m_bump_mapping->SetSpecularColor(Math::vec4(1,1,1,1));
		m_bump_mapping->SetDiffuseColor(Math::vec4(1,1,1,1));
		m_bump_mapping->SetSpecularPower(16);
		m_bump_mapping->SetLightPosition(Math::vec3(10, 1, 10));
		m_bump_mapping->Begin();		
		m_texture_context->Bind();
		m_static_vao->Bind(m_bump_mapping->GetSupportedVertexAttributes());
		struct Vertex
		{
			float x,y,z,w;
			float nx,ny,nz,nw;
			float tx,ty,tz,tw;
			float bx,by,bz,bw;
			float u, v, s, q;
		};

	//	Vertex* v = (Vertex*)m_static_vao->MapVertexBuffer();

		m_static_vao->Render();		
		//m_bump_mapping->SetWorldMatrix(Math::mat4::CreateTranslate(1, 0, 0));
		/*m_bump_mapping->Begin();	
		m_static_vao->Render();*/	
		m_static_vao->Unbind();
		m_texture_context->Unbind();
		m_bump_mapping->End();/**/

		/*m_solid_context->SetDiffuseColor(Math::vec4(1, 1, 1, 1));
		m_solid_context->SetWorldMatrix(Math::mat4::CreateIdentity());//Math::mat4::CreateTranslate(0, 0, -1));
		m_solid_context->SetViewMatrix(Math::mat4::CreateIdentity());
		m_solid_context->SetProjectionMatrix(Math::mat4::CreateIdentity());//Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, 1.3, 	
		m_solid_context->Begin();		
		//m_texture_context->Bind();
		m_quad->Bind(m_solid_context->GetSupportedVertexAttributes());
		m_quad->Render();
		m_quad->Unbind();
		//m_texture_context->Unbind();
		m_solid_context->End();/**/

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
	System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(&test, &Test::OnKeyDown));
	System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_MOUSE_MOVE, System::EventHandler(&test, &Test::OnMouseMove));
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