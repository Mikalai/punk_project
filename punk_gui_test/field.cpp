#include "../punk_engine/math/math.h"

#include "field.h"

Field::Field()
{	
	m_terrain.reset(new Utility::Terrain);
	m_terrain->SetLandscape(ImageModule::ImageManager::Instance()->Load(L"terrain.png"));
	
	m_diffuse_1 = OpenGL::Texture2DManager::Instance()->Load(L"grass.png");
	m_diffuse_2 = OpenGL::Texture2DManager::Instance()->Load(L"ground.png");

	m_terrain_render.reset(new Render::TerrainRender);
	m_terrain_render->SetTerrain(m_terrain.get());
	m_terrain_render->SetDiffuseMap1(m_diffuse_1);
	m_terrain_render->SetDiffuseMap2(m_diffuse_2);	
	m_terrain_render->Init();

	m_grass = Utility::ObjectManager::Instance()->Load(L"grass.object");

	m_grass_rc.reset(new OpenGL::RenderContextTextured3D);
	m_grass_tc.reset(new OpenGL::TextureContext);
}

void Field::SetCameraReference(Utility::CameraRef camera)
{
	m_camera = camera;
}

void Field::Render()
{
	m_terrain_render->Render(m_camera);

	m_grass_rc->SetDiffuseColor(Math::vec4(1,1,1,1));
	m_grass_rc->SetProjectionMatrix(m_camera->GetProjectionMatrix());
	m_grass_rc->SetViewMatrix(m_camera->GetViewMatrix());
	
	m_grass_tc->SetTexture0(OpenGL::Texture2DManager::Instance()->Load(m_grass->GetMaterial().GetDiffuseMap()));
	m_grass_tc->Bind();

	OpenGL::VertexArrayObject* vao = OpenGL::VaoManager::Instance()->Load(m_grass->GetName() + L".vao");
	auto pos = m_camera->GetPosition();
	vao->Bind(m_grass_rc->GetSupportedVertexAttributes());
	for (int i = -50; i <= 100; i++)
	{
		for (int j = -50; j <= 100; j++)
		{
			float delta_x = (abs(i) % 2) ? 0.25 : 0;
			float delta_y = (abs(j) % 2) ? 0.25 : 0;
			float x = 1000;
			float z = 1000;
			float y = m_terrain->GetHeight(x + 0.5*(float)i + delta_x, z + 0.5*(float)j + delta_y);			
			Math::mat4 m = Math::mat4::CreateTranslate(x + 0.5*(float)i + delta_x, y, z+0.5*(float)j+delta_y);
			auto bbox = m_grass->AsBoundingBox();
			if (m_camera->BoxInFrustum(bbox.Transform(m)))
			{
				m_grass_rc->SetWorldMatrix(m);
				m_grass_rc->Begin();								
				vao->Render();						
			}
		}
	}
	vao->Unbind();		
	m_grass_rc->End();			
	m_grass_tc->Unbind();	
}

void Field::Hit(const Math::vec3& point, float radius)
{
	float height = m_terrain->GetHeight(point.X(), point.Z());
	float x = -radius;
	while (x <= radius)
	{
		float z = -radius;
		while (z <= radius)
		{
			m_terrain->SetHeight(point.X() + x, point.Z() + z, height - radius);
			z += 1.0f;
		}
		x += 1.0f;
	}
}