#include <iostream>
#include <fstream>

#include "../punk_engine/system/string.h"
#include "../punk_engine/system/system.h"
#include "../punk_engine/math/math.h"
#include "../punk_engine/images/images.h"
#include "../punk_engine/utility/utility.h"
#include "../punk_engine/system/driver/video/driver.h"
#include "../punk_engine/gui/gui.h"
#include "../punk_engine/logic/logic.h"
#include "../punk_engine/render/render.h"

#include "gui_control.h"
#include "all_vao.h"
#include "all_textures.h"
#include "all_armature.h"
#include "weapon.h"

#include "character.h"
#include "inventory.h"

class Character;

class IGameRender
{
public:
	virtual void RenderPlayer(Character* player) = 0;
};

class GameRender : public IGameRender
{
public:
	
};

class PlayerRender
{
	std::auto_ptr<OpenGL::TextureContext> m_texture_context;
public:

	PlayerRender()
	{
		m_texture_context.reset(new OpenGL::TextureContext);
	}

	void Render(OpenGL::RenderContext* rc, Character* player)
	{
		static float frame = 0.5;
		frame += 0.1;
		if (player->m_body == Character::MALE)
		{
			Utility::Armature* arm = player->m_armature;
			arm->GetArmatureAnimation().UpdateBones(frame);			
			OpenGL::RenderContextSkinning* light_rc = dynamic_cast<OpenGL::RenderContextSkinning*>(rc);
			if (light_rc)
			{
				OpenGL::StaticObject* vao = AllVAO::Instance()->m_male_up.get();
				for (int i = 0; i < arm->GetBonesCount(); ++i)
				{
					light_rc->SetBoneMatrix(i, vao->GetMeshTransform().Inversed()*arm->GetBoneByIndex(i)->GetAnimatedGlobalMatrix()*vao->GetMeshTransform());
				}
				m_texture_context->SetTexture0(AllTextures::Instance()->m_male_skin.get());
				m_texture_context->SetTexture1(AllTextures::Instance()->m_male_skin.get());
				m_texture_context->Bind();				
				light_rc->SetWorldMatrix(Math::mat4::CreateFreeCameraMatrix(player->GetPosition(), player->GetOrientation(), 
					Math::vec3(0, 1, 0)).Inversed() /**Math::mat4::CreateRotation(1, 0, 0, -Math::PI / 2)*/  * Math::mat4::CreateScaling(player->m_scale, player->m_scale, player->m_scale) *vao->GetMeshTransform());
				light_rc->Begin();
				vao->Bind(rc->GetSupportedVertexAttributes());
				vao->Render();
				vao->Unbind();
				vao = AllVAO::Instance()->m_male_low.get();
				vao->Bind(rc->GetSupportedVertexAttributes());
				vao->Render();
				vao->Unbind();

				vao = AllVAO::Instance()->m_male_feet.get();
				vao->Bind(rc->GetSupportedVertexAttributes());
				vao->Render();
				vao->Unbind();

				vao = AllVAO::Instance()->m_male_hair.get();
				vao->Bind(rc->GetSupportedVertexAttributes());
				vao->Render();
				vao->Unbind();

				vao = AllVAO::Instance()->m_male_hands.get();
				vao->Bind(rc->GetSupportedVertexAttributes());
				vao->Render();
				vao->Unbind();

				vao = AllVAO::Instance()->m_male_head.get();
				vao->Bind(rc->GetSupportedVertexAttributes());
				vao->Render();
				vao->Unbind();
				m_texture_context->Unbind();
			}
		}
	}
};



class MyApp
{
	Logic::Simulator m_simulator;
	std::auto_ptr<Character> m_player;
	std::auto_ptr<GUIControl> m_gui_control;
	System::ResourceManager<OpenGL::StaticObject> m_geometry_manager;
	Logic::Tree m_tree;

	Utility::Terrain m_terrain;

	std::auto_ptr<GUI::Manager> m_gui;
	OpenGL::Driver m_driver;
	std::auto_ptr<OpenGL::RenderContextBumpMapping> m_light_context;
	std::auto_ptr<OpenGL::RenderContextSkinning> m_skin_context;
	std::auto_ptr<OpenGL::TextureContext> m_texture_context;
	Utility::Camera m_camera;
	float x, y, z;
	std::vector<std::shared_ptr<Utility::StaticMesh>> m_meshes; 
	std::auto_ptr<Render::TerrainRender> m_terrain_render;

	System::ResourceManager<ImageModule::Image> m_image_manager;

	std::auto_ptr<OpenGL::Line> m_line;

	Math::vec2 m_start, m_cur;

	Math::vec3 m_point1;
	Math::vec3 m_point2;

	PlayerRender m_player_render;

public:

	void LoadAllFood()
	{
		System::Folder folder;
		folder.Open(System::Environment::Instance()->GetCurrentFolder() + L"food\\");
		std::list<System::string> food_staff = folder.ListAllItems();
		for each(System::string filename in food_staff)
		{
			std::wcout << L"Loading food from " << filename.Data() << std::endl;
			char file[256];
			filename.ToANSI(file, 256);
			FoodType food;
			food.FromTextFileANSI(file);
			AllFoodTypes::Instance()->m_food_types.push_back(food);
		}

		for (int i = 0; i < AllFoodTypes::Instance()->m_food_types.size(); ++i)
		{
			AllFoodTypes::Instance()->m_food_types[i].m_code = i;
		}

		folder.Close();
	}

	MyApp(const char* filename)
	{	
		LoadAllFood();
		m_driver.Start(System::Window::Instance());
		m_driver.SetClearColor(0.7, 0.6, 0, 1);
		m_light_context.reset(new OpenGL::RenderContextBumpMapping());
		m_skin_context.reset(new OpenGL::RenderContextSkinning());
		m_gui.reset(new GUI::Manager());		

		Utility::Scene scene;
		/// Load scene
		scene.Load(System::string(filename));		
		int objects_count = scene.GetObjectsCount();
		m_meshes.resize(objects_count);

		for (int i = 0; i < objects_count; ++i)
		{
			const System::string& name = scene.GetObjectName(i);
			m_meshes[i].reset(scene.CookStaticMesh(name));
		}

		/// for each mesh create static vao
		for (int i = 0; i < objects_count; ++i)
		{
			std::auto_ptr<OpenGL::StaticObject> vao(new OpenGL::StaticObject());
			vao->SetStaticObject(m_meshes[i].get());			
			vao->Init();

			m_geometry_manager.ManageResource(System::Resource<OpenGL::StaticObject>(vao.release()));
		}

		/*scene.Load(L"tree.pmd");
		objects_count = scene.GetObjectsCount();
		m_meshes.resize(objects_count);

		for (int i = 0; i < objects_count; ++i)
		{
		const System::string& name = scene.GetObjectName(i);
		m_meshes[i].reset(scene.CookStaticMesh(name));
		}

		/// for each mesh create static vao		
		for (int i = 0; i < objects_count; ++i)
		{
		std::stringstream str;
		str << i << ".vao";
		std::ofstream stream(str.str(), std::ios_base::binary);
		std::auto_ptr<OpenGL::StaticObject> vao(new OpenGL::StaticObject());
		vao->SetStaticObject(m_meshes[i].get());			
		vao->Init();
		vao->Save(stream);
		m_geometry_manager.ManageResource(System::Resource<OpenGL::StaticObject>(vao.release()));
		}*/

		std::auto_ptr<OpenGL::StaticObject> vao(new OpenGL::StaticObject());
		vao->FromFileVAO(System::Environment::Instance()->GetModelFolder() + L"trunk_10.vao");

		m_geometry_manager.ManageResource(System::Resource<OpenGL::StaticObject>(vao.release()));

		m_geometry_manager[0].Unload();
		m_geometry_manager[0].Reload();

		/// init camera staff
		x = 1024;
		y = 0;
		z = 1024;		

		m_camera.SetPosition(Math::vec3(1024.3, 10, 1024.6));
		m_camera.SetProperties
			(Math::PI / 4.0
			, System::Window::Instance()->GetHeight() / (float)System::Window::Instance()->GetWidth()
			, 0.1
			, 100.0);

		m_simulator.Add(&m_tree);

		ImageModule::Importer file;		
		ImageModule::GrayImage* landscape = file.LoadGray(System::Environment::Instance()->GetTexutreFolder() + L"terrain.png");
		ImageModule::RGBImage* diffuse1 = file.LoadRGB(System::Environment::Instance()->GetTexutreFolder() + L"grass.png");
		ImageModule::RGBImage* diffuse2 = file.LoadRGB(System::Environment::Instance()->GetTexutreFolder() + L"ground.png");

		m_image_manager.ManageResource(System::Resource<ImageModule::Image>(landscape));
		m_image_manager.ManageResource(System::Resource<ImageModule::Image>(diffuse1));
		m_image_manager.ManageResource(System::Resource<ImageModule::Image>(diffuse2));


		m_terrain.SetBaseHeight(0);
		m_terrain.SetLandscape(landscape);
		m_terrain.SetOffset(Math::vec3(0,0,0));
		m_terrain.SetScale(1);


		m_terrain_render.reset(new Render::TerrainRender());
		m_terrain_render->SetTerrain(&m_terrain);
		m_terrain_render->SetDiffuseMap1(*diffuse1);
		m_terrain_render->SetDiffuseMap2(*diffuse2);
		m_terrain_render->Init();

		m_line.reset(new OpenGL::Line);
		
		m_player.reset(new Character);
		m_player->SetPosition(Math::vec3(1024, m_terrain.GetHeight(1024, 1024), 1024));
		m_player->SetOrientation(Math::vec3(1, 0, 0));
		//m_simulator.Add(m_player.get());

		m_texture_context.reset(new OpenGL::TextureContext);
		m_gui_control.reset(new GUIControl());
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

	void OnMouseLDown(System::Event* event)
	{
		System::MouseLeftButtonDownEvent* e = static_cast<System::MouseLeftButtonDownEvent*>(event);
		m_cur = m_start.Set(e->x, e->y);
	}

	void OnMouseMove(System::Event* event)
	{
		System::MouseMoveEvent* e = static_cast<System::MouseMoveEvent*>(event);
		m_cur.Set(e->x, e->y);

		if (System::Mouse::Instance()->GetButtonState(System::Mouse::LEFT_BUTTON) 
			|| System::Mouse::Instance()->GetButtonState(System::Mouse::RIGHT_BUTTON))
		{
			Math::vec3 v(-800, -600, 0);
			Math::vec3 pv = (m_camera.GetProjectionMatrix() * v.ToHomogeneous()).Normalize().XYZ();
			float a = (double)System::Window::Instance()->GetHeight() / (double)System::Window::Instance()->GetWidth();

			float x = (-1 + 2*m_cur.X() / (double) System::Window::Instance()->GetWidth()) / a;
			float y = (-1 + 2*m_cur.Y() / (double) System::Window::Instance()->GetHeight());

			std::cout << x << " " << y << " " << a << std::endl;
			Math::vec3 p(x, y, -1/tan(Math::PI/8));
			m_point1 = p = (m_camera.GetViewMatrix().Inversed() * p.ToHomogeneous()).XYZ();
			m_point2 = m_camera.GetPosition();
			Math::vec3 point;
			if (m_terrain.IntersectWithRay(p, (p - m_camera.GetPosition()).Normalized(), point))
			{
				float height = m_terrain.GetHeight(point.X(), point.Z());
				if (System::Mouse::Instance()->GetButtonState(System::Mouse::LEFT_BUTTON))
					m_terrain.SetHeight(point.X(), point.Z(), height - 1);
				else
					m_terrain.SetHeight(point.X(), point.Z(), height + 1);
			}
		}
	}

	void OnIdle(System::Event* event)
	{	
		static float a = 0;
		a+= 0.001;

		{
			Math::vec3 camera_pos = m_camera.GetPosition();
			float height = m_terrain.GetHeight(camera_pos.X(), camera_pos.Z());	
			m_camera.SetBaseHeight(height + 2);						
		}

		m_driver.ClearBuffer(OpenGL::Driver::COLOR_BUFFER|OpenGL::Driver::DEPTH_BUFFER);				
		{
			int i = 0;
			OpenGL::StaticObject* vao = m_geometry_manager[0];			
			m_light_context->SetWorldMatrix(Math::mat4::CreateTranslate(Math::vec3(-0.9,-0.9,-0.5))*m_camera.GetViewMatrix().RotationPart4x4()*Math::mat4::CreateScaling(0.1, 0.1, 0.1));
			m_light_context->SetViewMatrix(Math::mat4::CreateIdentity());
			m_light_context->SetProjectionMatrix(Math::mat4::CreateOrthographicProjection(-1, 1, 1, -1, 0.1, 100.0));
			//m_light_context->SetProjectionMatrix(Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, 1.3, 0.1, 100.0));
			m_light_context->SetAmbientColor(Math::vec4(0,0,0,0));
			m_light_context->SetSpecularColor(Math::vec4(1,1,1,1));
			m_light_context->SetDiffuseColor(Math::vec4(1,1,1,1));
			m_light_context->SetSpecularPower(16);
			m_light_context->SetLightPosition(Math::vec3(10, 1, 10));
			m_light_context->Begin();				
			vao->Bind(m_light_context->GetSupportedVertexAttributes());
			vao->Render();		
			vao->Unbind();
			m_light_context->End();			

		/*	vao = m_geometry_manager[1];			
			m_light_context->SetViewMatrix(m_camera.GetViewMatrix());
			m_light_context->SetProjectionMatrix(m_camera.GetProjectionMatrix());
			m_light_context->SetAmbientColor(Math::vec4(0,0,0,0));
			m_light_context->SetSpecularColor(Math::vec4(1,1,1,1));
			m_light_context->SetDiffuseColor(Math::vec4(1,1,1,1));
			m_light_context->SetSpecularPower(16);
			m_light_context->SetLightPosition(Math::vec3(10, 1, 10));
			srand(1);
			for (int i = 0 ; i < 100; ++i)
			{
				float x = 1000 + rand() % 200;
				float z = 1000 + rand() % 200;
				float y = m_terrain.GetHeight(x, z);
				Math::mat4 local = Math::mat4::CreateTranslate(x, y, z)*Math::mat4::CreateRotation(1, 0, 0, -Math::PI/2);
				Math::BoundingBox bbox = vao->GetBoundingBox();
				bbox.Transform(local);
				if (m_camera.BoxInFrustum(bbox))
				{
					m_light_context->SetWorldMatrix(local);
					m_light_context->Begin();				
					vao->Bind(m_light_context->GetSupportedVertexAttributes());
					vao->Render();		
					vao->Unbind();
				}
			}
			m_light_context->End();		*/

			//m_light_context->SetWorldMatrix(Math::mat4::CreateTranslate(m_player->GetPosition()));
			m_skin_context->SetViewMatrix(m_camera.GetViewMatrix());
			m_skin_context->SetProjectionMatrix(m_camera.GetProjectionMatrix());
			m_skin_context->SetAmbientColor(Math::vec4(0,0,0,0));
			m_skin_context->SetSpecularColor(Math::vec4(1,1,1,1));
			m_skin_context->SetDiffuseColor(Math::vec4(1,1,1,1));
			m_skin_context->SetSpecularPower(1);
			m_skin_context->SetLightPosition(Math::vec3(10, 1, 10));
			m_skin_context->Begin();
			m_player_render.Render(m_skin_context.get(), m_player.get());

			m_light_context->SetViewMatrix(m_camera.GetViewMatrix());
			m_light_context->SetProjectionMatrix(m_camera.GetProjectionMatrix());
			WeaponRenderable wr;
			wr.Render(AllWeapon::Instance()->m_m16a2.get(), m_player.get(), m_texture_context.get(), m_light_context.get());
			m_skin_context->End();	
		}/**/

		m_terrain_render->Render(&m_camera);
//		m_gui->Render();

		m_line->SetLocalTransform(Math::mat4::CreateIdentity());
		m_line->SetViewTranform(m_camera.GetViewMatrix());
		m_line->SetProjectionTransform(m_camera.GetProjectionMatrix());
		m_line->SetColor(1, 1, 1, 1);		
		Math::vec3 pp = m_point2 + (m_point1 - m_point2).Normalized()*1000.0f;
		Math::vec3 p1(0,0,0);
		Math::vec3 p2(1024, 200, 1024);
		//m_line->Draw(p2, p1);
		m_line->Draw(pp, m_point1);

		m_gui_control->Render();

		/*if (System::Mouse::Instance()->GetButtonState(System::Mouse::LEFT_BUTTON))
		{
			m_line->SetLocalTransform(Math::mat4::CreateIdentity());
			m_line->SetViewTranform(Math::mat4::CreateIdentity());
			m_line->SetProjectionTransform(Math::mat4::CreateOrthographicProjection(0, System::Window::Instance()->GetWidth(), System::Window::Instance()->GetHeight(), 0, 0, 1));
			m_line->SetColor(0, 1, 0, 1);			
			m_line->Draw(Math::vec3(m_start.X(), m_start.Y(), 0), Math::vec3(m_start.X(), m_cur.Y(), 0));
			m_line->Draw(Math::vec3(m_start.X(), m_cur.Y(), 0), Math::vec3(m_cur.X(), m_cur.Y(), 0));
			m_line->Draw(Math::vec3(m_cur.X(), m_cur.Y(), 0), Math::vec3(m_cur.X(), m_start.Y(), 0));
			m_line->Draw(Math::vec3(m_cur.X(), m_start.Y(), 0), Math::vec3(m_start.X(), m_start.Y(), 0));
		}*/

		m_driver.SwapBuffers();
	}
};

int main(int argc, char** argv)
{
	System::Window::Instance()->SetTitle(L"Тэставаньне штучнага інтэлект");
	System::Mouse::Instance()->LockInWindow(true);
	OpenGL::Module module;
	module.Init();
	MyApp viewer("coordinate_system.pmd");
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(&viewer, &MyApp::OnIdle));
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(&viewer, &MyApp::OnKeyDown));
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_LBUTTON_DOWN, System::EventHandler(&viewer, &MyApp::OnMouseLDown));
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_MOVE, System::EventHandler(&viewer, &MyApp::OnMouseMove));
	System::Window::Instance()->Loop();

	module.Destroy();

	return 0;
}