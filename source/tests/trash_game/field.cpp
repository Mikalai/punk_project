#include "../../math/math.h"

#include "field.h"

Field::Field()
{	
	m_terrain.reset(new Utility::Terrain);
	m_terrain->SetLandscape(ImageModule::ImageManager::Instance()->Load(L"terrain.png"));
	m_terrain->SetScale(1.0f);

	m_diffuse_1 = OpenGL::Texture2DManager::Instance()->Load(L"grass.png");
	m_diffuse_2 = OpenGL::Texture2DManager::Instance()->Load(L"ground.png");

	m_terrain_render.reset(new Render::TerrainRender);
	m_terrain_render->SetTerrain(m_terrain.get());
	m_terrain_render->SetDiffuseMap1(m_diffuse_1);
	m_terrain_render->SetDiffuseMap2(m_diffuse_2);	
	m_terrain_render->Init();

	m_grass = Utility::ObjectManager::Instance()->Load(L"grass.object");

	m_grass_rc.reset(new OpenGL::RenderContextGrass);
	m_grass_tc.reset(new OpenGL::TextureContext);

	m_time = 0;

	Utility::PhysicalSimulator::Instance()->SetTerrain(*m_terrain.get());
}

void Field::SetCameraReference(Utility::CameraRef camera)
{
	m_camera = camera;
}

void Field::Update(float time, float delta)
{
	m_time += delta;
}

void Field::Render()
{
	m_terrain_render->Render(m_camera);
	Math::Noise noise;
	float wind_strength = sin(m_time);
	Math::vec3 wind_direction(sin(m_time), cos(m_time), cos(m_time));
	float heiught = m_terrain->GetHeight(1000, 1000);
	m_grass_rc->SetDiffuseColor(Math::vec4(1,1,1,1));
	m_grass_rc->SetProjectionMatrix(m_camera->GetProjectionMatrix());
	m_grass_rc->SetViewMatrix(m_camera->GetViewMatrix());
	m_grass_rc->SetPosition(Math::vec3(1000, 0, 1000));
	m_grass_rc->SetTime(m_time);
	m_grass_rc->SetWindStrength(wind_strength);
	m_grass_rc->SetWindDirection(wind_direction);
	m_grass_tc->SetTexture0(OpenGL::Texture2DManager::Instance()->Load(m_grass->GetMaterial().GetDiffuseMap()));
	m_grass_tc->SetTexture1(m_terrain_render->GetHeightMap());
	m_grass_tc->Bind();

	OpenGL::VertexArrayObject* vao = OpenGL::VaoManager::Instance()->Load(m_grass->GetName() + L".vao");
	
	m_grass_rc->Begin();								
	vao->Bind(m_grass_rc->GetSupportedVertexAttributes());
	vao->RenderInstanced(10000);							
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