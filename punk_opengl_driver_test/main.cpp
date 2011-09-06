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
	OpenGL::VertexArrayObject* vao;
	ShaderProgram* program;
	Utility::Camera* camera; 
	OpenGL::TextureContext* m_texture_context;
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
			mdl.LoadPunkModel(System::string("d:\\project\\punk_project\\punk_engine\\blender\\simple_anim2.pmd"));
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

		vao = new OpenGL::VertexArrayObject();
		vao->Create(mesh->GetVertexBuffer(), mesh->GetVertexBufferSize(), mesh->GetIndexBuffer(), mesh->GetVertexCount(), mesh->GetIndexCount(), mesh->GetOneVertexSize(), mesh->GetVertexComponentCode());

		program = driver->GetShaderProgram(L"static_mesh");

		camera = new Utility::Camera();

		m_texture_context = new OpenGL::TextureContext();
		m_texture_context->SetDiffuseMap(driver->GetTexture2D(mdl.m_materials[mdl.m_material].diffuse_map));
		m_texture_context->SetNormalMap(driver->GetTexture2D(mdl.m_materials[mdl.m_material].normal_map));

	}

	~Test()
	{
		driver->Shutdown();
		delete driver;
	}

	void Draw(System::Event* event)
	{
		try
		{
			OpenGL::RenderContext context;
			context.Begin(program);
			m_texture_context->Apply();

			Math::mat4 m = Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, 4.0/3.0, 0.01, 100.0) * Math::mat4::CreateTargetCameraMatrix(Math::vec3(0,0,-5), Math::vec3(0,0,0), Math::vec3(0, 1, 0));

			Math::mat4 proj = camera->GetProjectionMatrix();
			Math::mat4 world = Math::mat4::CreateIdentity();
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

			driver->ClearBuffer(OpenGL::Driver::COLOR_BUFFER|OpenGL::Driver::DEPTH_BUFFER);
			driver->Render(vao);
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