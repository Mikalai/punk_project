#include <iostream>

#include "../PUNK_ENGINE_API/system/string.h"
#include "../PUNK_ENGINE_API/system/system.h"
#include "../PUNK_ENGINE_API/math/math.h"
#include "../PUNK_ENGINE_API/images/images.h"
#include "../PUNK_ENGINE_API/utility/utility.h"
#include "../PUNK_ENGINE_API/system/driver/video/driver.h"
#include "../PUNK_ENGINE_API/gui/gui.h"
#include "../PUNK_ENGINE_API/audio/punk_audio.h"

class Viewer
{
	std::unique_ptr<GUI::Manager> m_gui;
	OpenGL::Driver m_driver;
	std::unique_ptr<OpenGL::RenderContextLight> m_light_context;
	GUI::ListBox* lst_all_weapon;
	GUI::Button* btn_load;
	GUI::Widget* lbl_file;
	GUI::TextBox* txt_file;
	GUI::Widget* lbl_name;
	GUI::TextBox* txt_name;
	GUI::Widget* lbl_desc;
	GUI::TextBox* txt_desc;
	GUI::Widget* lbl_weight;
	GUI::TextBox* txt_weight;
	GUI::Widget* lbl_kill_range;
	GUI::TextBox* txt_kill_range;
	GUI::Widget* lbl_holder_size;
	GUI::TextBox* txt_holder_size;
	GUI::Widget* lbl_bullet_type;
	GUI::ListBox* lst_bullet_type;
	GUI::Widget* lbl_backsight_type;
	GUI::ListBox* lst_backsight_type;
	GUI::Widget* lbl_purpose_type;
	GUI::ListBox* lst_purpose_type;
	GUI::Widget* lbl_control_type;
	GUI::ListBox* lst_control_type;
	GUI::Widget* lbl_kill_source_type;
	GUI::ListBox* lst_kill_source_type;
	GUI::Widget* lbl_usage_type;
	GUI::ListBox* lst_usage_type;
	GUI::Widget* lbl_automatic_type;
	GUI::ListBox* lst_automatic_type;
	GUI::Widget* lbl_barrel_count_type;
	GUI::ListBox* lst_barrel_count_type;
	GUI::Widget* lbl_barrel_type;
	GUI::ListBox* lst_barrel_type;
	GUI::Button* btn_index;
	GUI::TextBox* txt_index;
	GUI::TabWidget* tab_widget;
	GUI::Widget* wid_first;
	GUI::Widget* wid_second;
	GUI::Widget* wid_third;

	GUI::Widget* lbl_shoot_sound;
	GUI::Widget* lbl_reload_sound;

	GUI::Widget* wid_viewer;
	GUI::Widget* lbl_geom;
	GUI::Widget* lbl_diffuse_map;
	GUI::Widget* lbl_normal_map;
	GUI::ListBox* lst_geom;
	GUI::ListBox* lst_diffuse_map;
	GUI::ListBox* lst_normal_map;

	GUI::ListBox* lst_sound_shoot;
	GUI::ListBox* lst_sound_reload;

	GUI::Button* btn_save;
	GUI::Button* btn_delete;
	GUI::Button* btn_clear;

	std::unique_ptr<OpenGL::Texture2D> m_render_target;
	std::unique_ptr<OpenGL::Texture2D> m_diffuse_map;
	std::unique_ptr<OpenGL::Texture2D> m_normal_map;

	std::unique_ptr<OpenGL::StaticObject> m_vao;
	std::unique_ptr<OpenGL::RenderContextBumpMapping> m_rc;
	std::unique_ptr<OpenGL::TextureContext> m_tc;
	std::unique_ptr<OpenGL::FrameBuffer> m_frame_buffer;
	float m_phi, m_psy, x, y, z;

	Utility::Camera m_camera;

	std::unique_ptr<Audio::Player> m_player;

	Utility::WeaponType m_weapon;
public:

	Viewer()
	{
		/// start driver
		m_driver.Start(System::Window::Instance());
		System::Window::Instance()->SetSize(800, 600);
		System::Window::Instance()->SetPosition(200, 100);
		m_driver.SetClearColor(0.0, 0.0, 0, 1);

		m_gui.reset(new GUI::Manager());
		float count = 5;
		float y = 0.95f;
		float h = 0.05f;
		float w0 = 0.2f;
		float w1 = 0.2f;
		float w2 = 1 - w1 - w0;
		btn_load = new GUI::Button(w0, y, w1+w2, h, L"Load");
		lbl_barrel_type = new GUI::Widget(w0+w1+w2/2, y-h, w2/2, h, L"Barrel type:");
		lst_barrel_type = new GUI::ListBox(w0+w1+w2/2, y-6*h, w2/2, 5*h);
		y -= h;
		lbl_file = new GUI::Widget(w0, y, w1, h, L"File:");
		txt_file = new GUI::TextBox(w0+w1, y, w2/2, h);
		y -= h;
		lbl_name = new GUI::Widget(w0, y, w1, h, L"Name*:");
		txt_name = new GUI::TextBox(w0+w1, y, w2/2, h);
		y -= h;
		lbl_desc = new GUI::Widget(w0, y, w1, h, L"Description*:");
		txt_desc = new GUI::TextBox(w0+w1, y, w2/2, h);
		y -= h;
		lbl_weight = new GUI::Widget(w0, y, w1, h, L"Weight(g):");
		txt_weight = new GUI::TextBox(w0+w1, y, w2/2, h);
		y -= h;
		lbl_kill_range = new GUI::Widget(w0, y, w1, h, L"Kill range(m):");
		txt_kill_range = new GUI::TextBox(w0+w1, y, w2/2, h);
		y -= h;
		lbl_holder_size = new GUI::Widget(w0, y, w1, h, L"Holder capacity:");
		txt_holder_size = new GUI::TextBox(w0+w1, y, w2/2, h);
		y -= (count+1)*h;
		lbl_bullet_type = new GUI::Widget(w0, y+count*h, (1-w0)/4, h, L"Bullet type:");
		lst_bullet_type = new GUI::ListBox(w0, y, (1-w0)/4, count*h);
		lbl_backsight_type = new GUI::Widget(w0+(1-w0)/4, y+count*h, (1-w0)/4, h, L"Backsight type:");
		lst_backsight_type = new GUI::ListBox(w0+(1-w0)/4, y, (1-w0)/4, count*h);
		lbl_purpose_type = new GUI::Widget(w0+2.0f*(1-w0)/4.0f, y+count*h, (1-w0)/4, h, L"Purpose type:");
		lst_purpose_type = new GUI::ListBox(w0+2.0f*(1-w0)/4, y, (1-w0)/4, count*h);
		lbl_control_type = new GUI::Widget(w0+3.0f*(1-w0)/4, y+count*h, (1-w0)/4, h, L"Control type:");
		lst_control_type = new GUI::ListBox(w0+3.0f*(1-w0)/4, y, (1-w0)/4, count*h);
		y -= (count+1)*h;
		lbl_kill_source_type = new GUI::Widget(w0, y+count*h, (1-w0)/4, h, L"Kill source:");
		lst_kill_source_type = new GUI::ListBox(w0, y, (1-w0)/4, count*h);
		lbl_usage_type = new GUI::Widget(w0+(1-w0)/4, y+count*h, (1-w0)/4, h, L"Usage type:");
		lst_usage_type = new GUI::ListBox(w0+(1-w0)/4, y, (1-w0)/4, count*h);
		lbl_automatic_type = new GUI::Widget(w0+2*(1-w0)/4, y+count*h, (1-w0)/4, h, L"Automatic type:");
		lst_automatic_type = new GUI::ListBox(w0+2*(1-w0)/4, y, (1-w0)/4, count*h);
		lbl_barrel_count_type = new GUI::Widget(w0+3.0f*(1-w0)/4, y+count*h, (1-w0)/4, h, L"Barrel count:");
		lst_barrel_count_type = new GUI::ListBox(w0+3.0f*(1-w0)/4, y, (1-w0)/4, count*h);
		y -= h;
		btn_index = new GUI::Button(w0, y, w1, h, L"Index:");
		txt_index = new GUI::TextBox(w0+w1, y, w2/4, h);
		btn_save = new GUI::Button(w0+w1+w2/4, y, w2/4, h, L"Save");
		btn_clear = new GUI::Button(w0+w1+2.0f*w2/4, y, w2/4, h, L"Clear fields");
		btn_delete = new GUI::Button(w0+w1+3*w2/4, y, w2/4, h, L"Delete");
		lst_all_weapon = new GUI::ListBox(0, 0, w0, 1);

		lbl_geom = new GUI::Widget(0, 0.95, w0, 0.05, L"Geometry:");
		lst_geom = new GUI::ListBox(0, 0.7, w0, 0.25);
		lst_geom->OnItemChanged(System::EventHandler(this, &Viewer::OnItemChanged));
		lbl_diffuse_map = new GUI::Widget(0, 0.65, w0, 0.5, L"Diffuse map:");
		lst_diffuse_map = new GUI::ListBox(0, 0.4, w0, 0.25);
		lst_diffuse_map->OnItemChanged(System::EventHandler(this, &Viewer::OnDiffuseMapChanged));

		wid_viewer = new GUI::Widget(w0, 0, 1-w0, 1);
		wid_viewer->SetMouseMoveHandler(System::EventHandler(this, &Viewer::OnViewerMouseMove));
		wid_viewer->SetKeyDownHandler(System::EventHandler(this, &Viewer::OnViewerKeyDown));
		wid_viewer->SetIdleHandler(System::EventHandler(this, &Viewer::OnViewerIdle));
		wid_viewer->SetResizedHandler(System::EventHandler(this, &Viewer::OnViewerResized));

		wid_first = new GUI::Widget(0, 0, 1, 1, L"");
		wid_second = new GUI::Widget(0, 0, 1, 1, L"");
		wid_second->AddChild(lbl_geom);
		wid_second->AddChild(lst_geom);
		wid_second->AddChild(lbl_diffuse_map);
		wid_second->AddChild(lst_diffuse_map);
		wid_second->AddChild(wid_viewer);

		wid_third = new GUI::Widget(0, 0, 1, 1, L"");
		lbl_shoot_sound = new GUI::Widget(0, 0.95, w0, 0.05, L"Shoot:");
		wid_third->AddChild(lbl_shoot_sound);
		lbl_reload_sound = new GUI::Widget(0, 0.45, w0, 0.05, L"Reload:");
		wid_third->AddChild(lbl_reload_sound);
		lst_sound_reload = new GUI::ListBox(0, 0, w0, 0.45);
		lst_sound_reload->OnItemChanged(System::EventHandler(this, &Viewer::OnSoundReloadItemChanged));
		wid_third->AddChild(lst_sound_reload);
		lst_sound_shoot = new GUI::ListBox(0, 0.5, w0, 0.45);
		lst_sound_shoot->OnItemChanged(System::EventHandler(this, &Viewer::OnSoundShootItemChanged));
		lst_sound_shoot->SetText(L"QWERT");
		wid_third->AddChild(lst_sound_shoot);

		tab_widget = new GUI::TabWidget(0, 0, 1, 1);

		tab_widget->AddTab(L"Options", wid_first);
		tab_widget->AddTab(L"Geometry", wid_second);
		tab_widget->AddTab(L"Sound", wid_third);


		m_gui->AddRootWidget(tab_widget);
		wid_first->AddChild(btn_load);
		wid_first->AddChild(btn_save);
		wid_first->AddChild(lbl_file);
		wid_first->AddChild(txt_file);
		wid_first->AddChild(lbl_name);
		wid_first->AddChild(txt_name);
		wid_first->AddChild(lbl_desc);
		wid_first->AddChild(txt_desc);
		wid_first->AddChild(lbl_weight);
		wid_first->AddChild(txt_weight);
		wid_first->AddChild(btn_delete);
		wid_first->AddChild(btn_clear);
		wid_first->AddChild(lst_all_weapon);
		wid_first->AddChild(lbl_kill_range);
		wid_first->AddChild(txt_kill_range);
		wid_first->AddChild(lbl_holder_size);
		wid_first->AddChild(txt_holder_size);
		wid_first->AddChild(lbl_bullet_type);
		wid_first->AddChild(lst_bullet_type);
		wid_first->AddChild(lbl_backsight_type);
		wid_first->AddChild(lst_backsight_type);
		wid_first->AddChild(lbl_purpose_type);
		wid_first->AddChild(lst_purpose_type);
		wid_first->AddChild(lbl_control_type);
		wid_first->AddChild(lst_control_type);
		wid_first->AddChild(lbl_kill_source_type);
		wid_first->AddChild(lst_kill_source_type);
		wid_first->AddChild(lbl_usage_type);
		wid_first->AddChild(lst_usage_type);
		wid_first->AddChild(lbl_automatic_type);
		wid_first->AddChild(lst_automatic_type);
		wid_first->AddChild(lbl_barrel_count_type);
		wid_first->AddChild(lst_barrel_count_type);
		wid_first->AddChild(lbl_barrel_type);
		wid_first->AddChild(lst_barrel_type);
		wid_first->AddChild(btn_index);
		wid_first->AddChild(txt_index);
		m_gui->SetFocusedWidget(tab_widget->GetFirstTabButton());
		//m_gui->AddRootWidget(wid_viewer);


		tab_widget->GetLastTabButton()->SetNextWidget(lst_all_weapon);
		lst_all_weapon->SetNextWidget(btn_load);
		btn_load->SetNextWidget(txt_file);
		txt_file->SetNextWidget(txt_name);
		txt_name->SetNextWidget(txt_desc);
		txt_desc->SetNextWidget(txt_weight);
		txt_weight->SetNextWidget(txt_kill_range);
		txt_kill_range->SetNextWidget(txt_holder_size);
		txt_holder_size->SetNextWidget(lst_barrel_type);
		lst_barrel_type->SetNextWidget(lst_bullet_type);
		lst_bullet_type->SetNextWidget(lst_backsight_type);
		lst_backsight_type->SetNextWidget(lst_purpose_type);
		lst_purpose_type->SetNextWidget(lst_control_type);
		lst_control_type->SetNextWidget(lst_kill_source_type);
		lst_kill_source_type->SetNextWidget(lst_usage_type);
		lst_usage_type->SetNextWidget(lst_automatic_type);
		lst_automatic_type->SetNextWidget(lst_barrel_count_type);
		lst_barrel_count_type->SetNextWidget(btn_index);
		btn_index->SetNextWidget(txt_index);
		txt_index->SetNextWidget(btn_save);
		btn_save->SetNextWidget(btn_clear);
		btn_clear->SetNextWidget(btn_delete);
		btn_delete->SetNextWidget(tab_widget->GetFirstTabButton());	// this will get first tab button

		ListAllWeapon();

		btn_load->SetMouseLeftClickHandler(System::EventHandler(this, &Viewer::OnLoad));
		btn_save->SetMouseLeftClickHandler(System::EventHandler(this, &Viewer::OnSave));
		btn_delete->SetMouseLeftClickHandler(System::EventHandler(this, &Viewer::OnDelete));
		btn_clear->SetMouseLeftClickHandler(System::EventHandler(this, &Viewer::OnClear));
		btn_index->SetMouseLeftClickHandler(System::EventHandler(this, &Viewer::OnIndex));

		InitRender();

		ListAllSounds();
		Audio::AudioManager::Instance();
		m_player.reset(new Audio::Player());
	}

	void OnDiffuseMapChanged(System::Event* e)
	{
		int new_item = (int)e;
		if (new_item < 0)
			return;

		System::string file = lst_diffuse_map->GetItem(new_item)->GetText();
		int index = (int)lst_diffuse_map->GetItem(new_item)->GetData();

		m_weapon.GetMapDiffuse().SetDiffuse(file);
	}

	void OnNormalMapChanged(System::Event* e)
	{
		int new_item = (int)e;
		if (new_item < 0)
			return;

		System::string file = lst_normal_map->GetItem(new_item)->GetText();
		int index = (int)lst_normal_map->GetItem(new_item)->GetData();

		m_weapon.GetMapNormal().SetNormal(file);
	}

	void OnSoundShootItemChanged(System::Event* e)
	{
		int new_item = (int)e;
		if (new_item < 0)
			return;

		System::string file = lst_sound_shoot->GetItem(new_item)->GetText();
		int index = (int)lst_sound_shoot->GetItem(new_item)->GetData();
		m_player.reset(new Audio::Player);
		m_player->SetSound(Audio::AudioManager::Instance()->Get(index));
		m_player->Stop();
		m_player->Play();

		m_weapon.SetSoundShoot(Utility::WeaponType::SoundElement(file));
	}

	void OnShootItemChanged(System::Event* e)
	{
		int new_item = (int)e;
		if (new_item < 0)
			return;

		System::string file = lst_sound_shoot->GetItem(new_item)->GetText();
		int index = (int)lst_sound_shoot->GetItem(new_item)->GetData();
		m_player.reset(new Audio::Player);
		m_player->SetSound(Audio::AudioManager::Instance()->Get(index));
		m_player->Stop();
		m_player->Play();

		m_weapon.SetSoundShoot(Utility::WeaponType::SoundElement(file));
	}

	void OnSoundReloadItemChanged(System::Event* e)
	{
		int new_item = (int)e;
		if (new_item < 0)
			return;

		System::string file = lst_sound_reload->GetItem(new_item)->GetText();
		int index = (int)lst_sound_reload->GetItem(new_item)->GetData();
		m_player.reset(new Audio::Player);
		m_player->SetSound(Audio::AudioManager::Instance()->Get(index));
		m_player->Stop();
		m_player->Play();

		m_weapon.SetSoundReload(Utility::WeaponType::SoundElement(file));
	}


	void InitRender()
	{
		CreateTexture();
		//
		//	create vao

		m_rc.reset(new OpenGL::RenderContextBumpMapping());
		m_tc.reset(new OpenGL::TextureContext());

		m_phi = 0;
		m_psy = 0;
		x = y = 0;
		z = -2;

		//
		//	create frame buffer
		//
		m_frame_buffer.reset(new OpenGL::FrameBuffer());
		m_frame_buffer->Init((int)wid_viewer->GetScreenWidth(), (int)wid_viewer->GetScreenHeight());
		//
		//	set fbo as a texture
		wid_viewer->SetBackgroundTexture(m_frame_buffer->GetColorTexture());
	}

	void Render()
	{
		m_frame_buffer->Activate();
		m_driver.SetClearColor(1, 1, 0, 1);
		m_driver.ClearBuffer(OpenGL::Driver::COLOR_BUFFER | OpenGL::Driver::DEPTH_BUFFER);

		if (m_vao.get())
		{
			m_rc->SetAmbientColor(Math::vec4(0,0,0,1));
			m_rc->SetDiffuseColor(Math::vec4(1,1,1,1));
			m_rc->SetLightPosition(m_camera.GetPosition());
			m_rc->SetSpecularColor(Math::vec4(1,1,1,1));
			m_rc->SetSpecularPower(16);
			m_rc->SetProjectionMatrix(Math::mat4::CreatePerspectiveProjection(Math::PI / 4.0f, m_frame_buffer->GetColorTexture()->GetWidth() / (float)m_frame_buffer->GetColorTexture()->GetHeight(), 0.1f, 100.0f));
			m_rc->SetViewMatrix(m_camera.GetViewMatrix());
			m_rc->Begin();
			m_tc->SetTexture0(m_diffuse_map.get());
			m_tc->SetTexture1(m_normal_map.get());
			m_tc->Bind();
			m_vao->Bind(m_rc->GetSupportedVertexAttributes());
			m_vao->Render();
			m_vao->Unbind();
			m_tc->Unbind();
			m_rc->End();
		}
		m_frame_buffer->Deactivate();
	}

	void MakeVao(Utility::Scene* scene, Utility::Object* obj)
	{
		if (obj)
		{
			std::unique_ptr<OpenGL::StaticObject> vao(new OpenGL::StaticObject);
			if (obj->GetMesh())
			{
				vao->SetStaticObject(scene->CookStaticMesh(obj->GetName()));
				vao->Init();

				System::Folder fld;
				fld.Open(System::Environment::Instance()->GetModelFolder());
				std::ofstream stream((obj->GetName()+L".vao").Data(), std::ios_base::binary);
				vao->Save(stream);
				stream.close();
				fld.Close();
			}
			for each (auto child in obj->GetChildren())
			{
				MakeVao(scene, child.get());
			}
		}
	}

	void OnItemChanged(System::Event* e)
	{
		int new_item = (int)e;
		if (new_item < 0)
			return;

		System::string file = lst_geom->GetItem(new_item)->GetText();

		Utility::Scene* scene = Utility::SceneFileManager::Instance()->Get(new_item);

		if (!scene)
		{
			System::Logger::Instance()->WriteError(L"No scheme for weapon");
			return;
		}

		m_weapon.MakeFromScheme(txt_file->GetText(), *scene);


		for (int i = 0; i < scene->GetObjectsCount(); i++)
		{
			MakeVao(scene, scene->FindObjectByName(scene->GetObjectName(i)));
		}

		///	recache data in the folder
		OpenGL::VaoManager::Instance()->Init();
	}

	void CreateTexture()
	{
		ImageModule::Importer importer;
		std::unique_ptr<ImageModule::RGBAImage> test(importer.LoadRGBA(System::Environment::Instance()->GetTextureFolder() + L"checker2.png"));
		m_diffuse_map.reset(new OpenGL::Texture2D(*test));
		std::unique_ptr<ImageModule::RGBImage> testrgb(importer.LoadRGB(System::Environment::Instance()->GetTextureFolder() + L"bump.png"));
		m_normal_map.reset(new OpenGL::Texture2D(*testrgb));

		//
		//	create render target
		//
		m_render_target.reset(new OpenGL::TextTexture2D());

	}

	void ListAllSounds()
	{
		lst_sound_reload->RemoveAllItems();
		lst_sound_shoot->RemoveAllItems();
		auto all_sounds = Audio::AudioManager::Instance()->GetAll();

		for each (auto sound in all_sounds)
		{
			std::unique_ptr<GUI::ListBox::ListBoxItem> item1(new GUI::ListBox::ListBoxItem(sound->GetLocation(), (void*)sound->GetIndex()));
			std::unique_ptr<GUI::ListBox::ListBoxItem> item2(new GUI::ListBox::ListBoxItem(sound->GetLocation(), (void*)sound->GetIndex()));
			lst_sound_reload->AddItem(item1.release());
			lst_sound_shoot->AddItem(item2.release());
		}
	}

	void ListAllWeapon()
	{
		auto all_weapons = Utility::WeaponTypeManager::Instance()->GetAll();
		lst_all_weapon->RemoveAllItems();

		for each (auto weapon in all_weapons)
		{
			lst_all_weapon->AddItem(new GUI::ListBox::ListBoxItem(weapon->GetLocation()));
		}

		LoadAllBullets();
		InitBarrelType();
		InitBarrelCount();
		InitAutomatic();
		InitUsageType();
		InitKillSource();
		InitControlType();
		InitPurposeType();
		ListAllVao();
	}

	void InitPurposeType()
	{
		lst_purpose_type->RemoveAllItems();
		lst_purpose_type->AddItem(new GUI::ListBox::ListBoxItem(L"NO", (void*)Utility::WeaponType::PURPOSE_NO));
		lst_purpose_type->AddItem(new GUI::ListBox::ListBoxItem(L"WAR", (void*)Utility::WeaponType::PURPOSE_WAR));
		lst_purpose_type->AddItem(new GUI::ListBox::ListBoxItem(L"RANGING", (void*)Utility::WeaponType::PURPOSE_RANGING));
		lst_purpose_type->AddItem(new GUI::ListBox::ListBoxItem(L"CLASS", (void*)Utility::WeaponType::PURPOSE_CLASS));
		lst_purpose_type->AddItem(new GUI::ListBox::ListBoxItem(L"SPORT", (void*)Utility::WeaponType::PURPOSE_SPORT));
		lst_purpose_type->AddItem(new GUI::ListBox::ListBoxItem(L"HUNT", (void*)Utility::WeaponType::PURPOSE_HUNT));
	}

	void InitControlType()
	{
		lst_control_type->RemoveAllItems();
		lst_control_type->AddItem(new GUI::ListBox::ListBoxItem(L"NO", (void*)Utility::WeaponType::CONTROL_NO));
		lst_control_type->AddItem(new GUI::ListBox::ListBoxItem(L"ONE_HAND_KNIFE", (void*)Utility::WeaponType::CONTROL_ONE_HAND_KNIFE));
		lst_control_type->AddItem(new GUI::ListBox::ListBoxItem(L"TWO_HAND_KNIFE", (void*)Utility::WeaponType::CONTROL_TWO_HAND_KNIFE));
		lst_control_type->AddItem(new GUI::ListBox::ListBoxItem(L"REVOLVER", (void*)Utility::WeaponType::CONTROL_REVOLVER));
		lst_control_type->AddItem(new GUI::ListBox::ListBoxItem(L"PISTOL", (void*)Utility::WeaponType::CONTROL_PISTOL));
		lst_control_type->AddItem(new GUI::ListBox::ListBoxItem(L"SUBMACHINE_GUN", (void*)Utility::WeaponType::CONTROL_SUBMACHINE_GUN));
		lst_control_type->AddItem(new GUI::ListBox::ListBoxItem(L"GUN", (void*)Utility::WeaponType::CONTROL_GUN));
		lst_control_type->AddItem(new GUI::ListBox::ListBoxItem(L"RIFLE", (void*)Utility::WeaponType::CONTROL_RIFLE));
		lst_control_type->AddItem(new GUI::ListBox::ListBoxItem(L"CARABINE", (void*)Utility::WeaponType::CONTROL_CARABINE));
		lst_control_type->AddItem(new GUI::ListBox::ListBoxItem(L"MACHINE_GUN", (void*)Utility::WeaponType::CONTROL_MACHINE_GUN));
		lst_control_type->AddItem(new GUI::ListBox::ListBoxItem(L"GRENADE_LAUNCHER", (void*)Utility::WeaponType::CONTROL_GRENADE_LAUNCHER));
	}

	void InitKillSource()
	{
		lst_kill_source_type->RemoveAllItems();
		lst_kill_source_type->AddItem(new GUI::ListBox::ListBoxItem(L"NO", (void*)Utility::WeaponType::KILL_SOURCE_NO));
		lst_kill_source_type->AddItem(new GUI::ListBox::ListBoxItem(L"COLD (knives)", (void*)Utility::WeaponType::KILL_SOURCE_COLD));
		lst_kill_source_type->AddItem(new GUI::ListBox::ListBoxItem(L"FIRING", (void*)Utility::WeaponType::KILL_SOURCE_FIRING));
		lst_kill_source_type->AddItem(new GUI::ListBox::ListBoxItem(L"PNEUMATIC", (void*)Utility::WeaponType::KILL_SOURCE_PNEUMATIC));
	}

	void InitUsageType()
	{
		lst_usage_type->RemoveAllItems();
		lst_usage_type->AddItem(new GUI::ListBox::ListBoxItem(L"NO", (void*)Utility::WeaponType::USAGE_NO));
		lst_usage_type->AddItem(new GUI::ListBox::ListBoxItem(L"PORTABLE", (void*)Utility::WeaponType::USAGE_PORTABLE));
		lst_usage_type->AddItem(new GUI::ListBox::ListBoxItem(L"STATIONAR", (void*)Utility::WeaponType::USAGE_STATIONAR));
	}

	void InitAutomatic()
	{
		lst_automatic_type->RemoveAllItems();
		lst_automatic_type->AddItem(new GUI::ListBox::ListBoxItem(L"NO", (void*)Utility::WeaponType::AUTOMATIC_NO));
		lst_automatic_type->AddItem(new GUI::ListBox::ListBoxItem(L"FULL", (void*)Utility::WeaponType::AUTOMATIC_FULL));
		lst_automatic_type->AddItem(new GUI::ListBox::ListBoxItem(L"SELF_RELOADING", (void*)Utility::WeaponType::AUTOMATIC_SELF_RELOADING));
	}

	void InitBarrelType()
	{
		lst_barrel_type->RemoveAllItems();
		lst_barrel_type->AddItem(new GUI::ListBox::ListBoxItem(L"NO", (void*)Utility::WeaponType::BARREL_NO));
		lst_barrel_type->AddItem(new GUI::ListBox::ListBoxItem(L"RIFLED", (void*)Utility::WeaponType::BARREL_RIFLED));
		lst_barrel_type->AddItem(new GUI::ListBox::ListBoxItem(L"SMOOTH_BORE", (void*)Utility::WeaponType::BARREL_SMOOTH_BORE));
	}

	void InitBarrelCount()
	{
		lst_barrel_count_type->RemoveAllItems();
		lst_barrel_count_type->AddItem(new GUI::ListBox::ListBoxItem(L"NO", (void*)Utility::WeaponType::BARREL_COUNT_NO));
		lst_barrel_count_type->AddItem(new GUI::ListBox::ListBoxItem(L"ONE", (void*)Utility::WeaponType::BARREL_COUNT_ONE));
		lst_barrel_count_type->AddItem(new GUI::ListBox::ListBoxItem(L"TWO", (void*)Utility::WeaponType::BARREL_COUNT_TWO));
		lst_barrel_count_type->AddItem(new GUI::ListBox::ListBoxItem(L"MANY", (void*)Utility::WeaponType::BARREL_COUNT_MANY));
	}

	void LoadAllBullets()
	{
		System::string data = System::Environment::Instance()->GetCurrentFolder() + L"bullet";
		System::Folder fld;
		fld.Open(data);
		std::list<System::string> files = fld.ListAllItems();
		lst_bullet_type->RemoveAllItems();
		for each (System::string lst in files)
		{
			char buf[2048];
			lst.ToANSI(buf, 2048);
			Utility::BulletType bullet;
			std::ifstream stream(buf, std::ios_base::binary);
			bullet.Load(stream);
			stream.close();
			lst_bullet_type->AddItem(new GUI::ListBox::ListBoxItem(bullet.m_name, (void*)bullet.m_index));
		}
		fld.Close();
	}

	void ListAllVao()
	{
		lst_geom->RemoveAllItems();
		auto scenes = Utility::SceneFileManager::Instance()->GetAll();
		for each (auto scene in scenes)
		{
			lst_geom->AddItem(new GUI::ListBox::ListBoxItem(scene->GetLocation(), (void*)scene->GetIndex()));
		}
	}

	void OnViewerMouseMove(System::Event* event)
	{
		m_camera.OnMouseMove(event);
	}

	void OnViewerKeyDown(System::Event* event)
	{
		m_camera.OnKeyDown(event);
	}

	void OnViewerIdle(System::Event* event)
	{
		m_camera.OnIdle(event);
	}

	void OnViewerResized(System::Event* event)
	{
		if (m_frame_buffer.get())
		{
			m_frame_buffer->Init((int)wid_viewer->GetScreenWidth(), (int)wid_viewer->GetScreenHeight());
			wid_viewer->SetBackgroundTexture(m_frame_buffer->GetColorTexture());
		}
	}

	void OnIndex(System::Event*)
	{
		System::string data = System::Environment::Instance()->GetCurrentFolder() + L"weapon";
		System::Folder fld;
		fld.Open(data);
		std::list<System::string> files = fld.ListAllItems();
		fld.Close();
		txt_index->SetText(System::string::Convert(files.size()));
	}

	void OnClear(System::Event*)
	{
		txt_file->SetText(L"");
		txt_desc->SetText(L"");
		txt_name->SetText(L"");
		txt_weight->SetText(L"");
		txt_index->SetText(L"");
		txt_kill_range->SetText(L"");
		txt_holder_size->SetText(L"");
		lst_bullet_type->SelectItem(0);
		lst_backsight_type->SelectItem(0);
		lst_purpose_type->SelectItem(0);
		lst_control_type->SelectItem(0);
		lst_kill_source_type->SelectItem(0);
		lst_usage_type->SelectItem(0);
		lst_automatic_type->SelectItem(0);
		lst_barrel_count_type->SelectItem(0);
		lst_barrel_type->SelectItem(0);

		ListAllVao();
		ListAllSounds();
	}

	void OnDelete(System::Event*)
	{
		int cur_sel = lst_all_weapon->GetCurrentSelection();
		if (cur_sel == -1)
			return;
		System::string path = System::Environment::Instance()->GetCurrentFolder() + L"\\weapon\\" + lst_all_weapon->GetItem(cur_sel)->GetText();

		System::Folder::DeleteFile(path);
		ListAllWeapon();
	}

	void OnLoad(System::Event*)
	{
		int cur_sel = lst_all_weapon->GetCurrentSelection();
		if (cur_sel == -1)
			return;
		char buf[256];

		m_weapon = *Utility::WeaponTypeManager::Instance()->Load(lst_all_weapon->GetItem(cur_sel)->GetText());

		txt_file->SetText(lst_all_weapon->GetItem(cur_sel)->GetText().Replace(L".weapon", L""));
		txt_desc->SetText(m_weapon.GetDescription());
		txt_name->SetText(m_weapon.GetName());
		txt_weight->SetText(System::string::Convert(m_weapon.GetWeight()));
		txt_kill_range->SetText(System::string::Convert(m_weapon.GetKillRange()));
		//txt_index->SetText(System::string::Convert(m_weapon.m_index));
		txt_holder_size->SetText(System::string::Convert(m_weapon.GetHolderSize()));

		lst_automatic_type->SelectItem(m_weapon.GetTypeAutomatic());
		//lst_backsight_type->SelectItem(m_weapon.GetBackSightType());
		lst_barrel_count_type->SelectItem(m_weapon.GetTypeBarrelCount());
		lst_barrel_type->SelectItem(m_weapon.GetTypeBarrel());
		for (int i = 0; i < lst_bullet_type->GetItemsCount(); ++i)
		{
			if ((int)lst_bullet_type->GetItem(i)->GetData() == m_weapon.GetBulletType())
			{
				lst_bullet_type->SelectItem(i);
				break;
			}
		}
		lst_control_type->SelectItem(m_weapon.GetTypeControl());
		lst_kill_source_type->SelectItem(m_weapon.GetTypeKillSource());
		lst_purpose_type->SelectItem(m_weapon.GetTypePurpose());
		lst_usage_type->SelectItem(m_weapon.GetTypeUsage());
	}

	void OnSave(System::Event*)
	{
		m_weapon.SetName(txt_name->GetText().Data());
		m_weapon.SetDescription(txt_desc->GetText().Data());
		try
		{
			m_weapon.SetWeight(txt_weight->GetText().ToInt32());
			m_weapon.SetKillRange(txt_kill_range->GetText().ToInt32());
			m_weapon.SetHolderSize(txt_holder_size->GetText().ToInt32());
			m_weapon.SetTypeAutomatic(Utility::WeaponType::AutomaticType(lst_automatic_type->GetCurrentSelection()));
			m_weapon.SetTypeBarrelCount(Utility::WeaponType::BarrelCountType(lst_barrel_count_type->GetCurrentSelection()));
			m_weapon.SetTypeBarrel(Utility::WeaponType::BarrelType(lst_barrel_type->GetCurrentSelection()));
			m_weapon.SetBulletType(int(lst_bullet_type->GetItem(lst_bullet_type->GetCurrentSelection())->GetData()));
			m_weapon.SetTypeControl(Utility::WeaponType::ControlType(lst_control_type->GetCurrentSelection()));
			m_weapon.SetTypeKillSource(Utility::WeaponType::KillSourceType(lst_kill_source_type->GetCurrentSelection()));
			m_weapon.SetTypePurpose(Utility::WeaponType::PurposeType(lst_purpose_type->GetCurrentSelection()));
			m_weapon.SetTypeUsage(Utility::WeaponType::UsageType(lst_usage_type->GetCurrentSelection()));
		}
		catch(...)
		{
			System::Logger::Instance()->WriteError(L"Bad satiety value");
			return;
		}

		Utility::WeaponTypeManager::Instance()->Manage(txt_file->GetText(), new Utility::WeaponType(m_weapon));

		//char buf[256];
		//System::string path = System::Environment::Instance()->GetCurrentFolder() + L"weapon\\" + txt_file->GetText() + L".weapon";
		//path.ToANSI(buf, 256);
		//std::ofstream stream(buf, std::ios_base::binary);
		//if (!stream.is_open())
		//{
		//	System::Logger::Instance()->WriteError(L"Can't save new bullet");
		//	return;
		//}
		//m_weapon.Save(stream);
		//stream.close();
		ListAllWeapon();
	}

	void OnIdle(System::Event* event)
	{

		Render();

		m_gui->Render();

		m_driver.SwapBuffers();
	}
};

int main(int argc, char** argv)
{
	System::Window::Instance()->SetTitle(L"WeaponMaker");
	System::Mouse::Instance()->LockInWindow(false);
	OpenGL::Module module;
	module.Init();
	Viewer viewer;
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(&viewer, &Viewer::OnIdle));
	System::Window::Instance()->Loop();

	module.Destroy();

	return 0;
}
