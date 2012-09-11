#include <iostream>

#include "../punk_engine/system/string.h"
#include "../punk_engine/system/system.h"
#include "../punk_engine/math/math.h"
#include "../punk_engine/images/images.h"
#include "../punk_engine/utility/utility.h"
#include "../punk_engine/system/driver/video/driver.h"
#include "../punk_engine/gui/gui.h"

class Viewer
{
	std::auto_ptr<GUI::Manager> m_gui;
	OpenGL::Driver m_driver;
	std::auto_ptr<OpenGL::RenderContextLight> m_light_context;
	float x, y, z;
	GUI::ListBox* lst_all_food;
	GUI::Button* btn_load;
	GUI::Widget* lbl_file;
	GUI::TextBox* txt_file;
	GUI::Widget* lbl_name;
	GUI::TextBox* txt_name;
	GUI::Widget* lbl_desc;
	GUI::TextBox* txt_desc;
	GUI::Widget* lbl_satiety;
	GUI::TextBox* txt_satiety;
	GUI::Widget* lbl_help;
	GUI::Button* btn_save;
	GUI::Button* btn_delete;
	GUI::Button* btn_clear;
	GUI::Button* btn_index;
	GUI::TextBox* txt_index;
public:
	
	Viewer()
	{		
		/// start driver
		m_driver.Start(System::Window::Instance());
		System::Window::Instance()->SetSize(400, 600);
		System::Window::Instance()->SetPosition(200, 100);
		m_driver.SetClearColor(0.0, 0.0, 0, 1);
	
		m_gui.reset(new GUI::Manager());
		float y = 0.95;
		float h = 0.05;
		float w0 = 0.2;
		float w1 = 0.2;
		float w2 = 1 - w1 - w0;
		btn_load = new GUI::Button(w0, y, w1+w2, h, L"Load");
		y -= h;
		lbl_file = new GUI::Widget(w0, y, w1, h, L"File:");
		txt_file = new GUI::TextBox(w0+w1, y, w2, h);
		y -= h;
		lbl_name = new GUI::Widget(w0, y, w1, h, L"Name*:");
		txt_name = new GUI::TextBox(w0+w1, y, w2, h);
		y -= h;
		lbl_desc = new GUI::Widget(w0, y, w1, h, L"Description*:");
		txt_desc = new GUI::TextBox(w0+w1, y, w2, h);
		y -= h;
		lbl_satiety = new GUI::Widget(w0, y, w1, h, L"Satiety**:");
		txt_satiety = new GUI::TextBox(w0+w1, y, w2, h);
		y -= h;
		btn_index = new GUI::Button(w0, y, w1, h, L"Index:");
		txt_index = new GUI::TextBox(w0+w1, y, w2, h);
		y -= h;
		btn_save = new GUI::Button(w0, y, (w1+w2) / 2, h, L"Save");
		btn_clear = new GUI::Button(w0 + (w1+w2) / 2, y, (w1+w2) / 2, h, L"Clear fields");
		y -= h;
		btn_delete = new GUI::Button(w0, y, w1+w2, h, L"Delete");

		lst_all_food = new GUI::ListBox(0, 0, w0, 1);

		m_gui->AddRootWidget(btn_load);
		m_gui->AddRootWidget(btn_save);
		m_gui->AddRootWidget(lbl_file);
		m_gui->AddRootWidget(txt_file);
		m_gui->AddRootWidget(lbl_name);
		m_gui->AddRootWidget(txt_name);
		m_gui->AddRootWidget(lbl_desc);
		m_gui->AddRootWidget(txt_desc);
		m_gui->AddRootWidget(lbl_satiety);
		m_gui->AddRootWidget(txt_satiety);
		m_gui->AddRootWidget(btn_delete);
		m_gui->AddRootWidget(btn_clear);
		m_gui->AddRootWidget(lst_all_food);
		m_gui->AddRootWidget(btn_index);
		m_gui->AddRootWidget(txt_index);
		m_gui->SetFocusedWidget(btn_load);		

		btn_load->SetNextWidget(txt_file);
		txt_file->SetNextWidget(txt_name);
		txt_name->SetNextWidget(txt_desc);
		txt_desc->SetNextWidget(txt_satiety);
		txt_satiety->SetNextWidget(btn_index);
		btn_index->SetNextWidget(txt_index);
		txt_index->SetNextWidget(btn_save);
		btn_save->SetNextWidget(btn_clear);
		btn_clear->SetNextWidget(btn_delete);
		btn_delete->SetNextWidget(lst_all_food);
		lst_all_food->SetNextWidget(btn_load);

		ListAllFood();

		btn_load->SetMouseLeftClickHandler(System::EventHandler(this, &Viewer::OnLoad));
		btn_save->SetMouseLeftClickHandler(System::EventHandler(this, &Viewer::OnSave));
		btn_delete->SetMouseLeftClickHandler(System::EventHandler(this, &Viewer::OnDelete));
		btn_clear->SetMouseLeftClickHandler(System::EventHandler(this, &Viewer::OnClear));
		btn_index->SetMouseLeftClickHandler(System::EventHandler(this, &Viewer::OnIndex));
	}
	
	void OnIndex(System::Event*)
	{
		System::string data = System::Environment::Instance()->GetCurrentFolder() + L"food";
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
		txt_satiety->SetText(L"");
		txt_index->SetText(L"");
	}

	void OnDelete(System::Event*)
	{
		int cur_sel = lst_all_food->GetCurrentSelection();
		if (cur_sel == -1)
			return;
		char buf[256];
		System::string path = System::Environment::Instance()->GetCurrentFolder() + L"\\food\\" + lst_all_food->GetItem(cur_sel)->GetText();

		System::Folder::DeleteFile(path);
		ListAllFood();
	}

	void OnLoad(System::Event*)
	{
		int cur_sel = lst_all_food->GetCurrentSelection();
		if (cur_sel == -1)
			return;
		char buf[256];
		System::string path = System::Environment::Instance()->GetCurrentFolder() + L"\\food\\" + lst_all_food->GetItem(cur_sel)->GetText();
		path.ToANSI(buf, 256);
		std::ifstream stream(buf, std::ios_base::binary);
		Utility::FoodType food;
		food.Load(stream);
		stream.close();

		txt_file->SetText(lst_all_food->GetItem(cur_sel)->GetText());
		txt_desc->SetText(food.m_description);
		txt_name->SetText(food.m_name);
		txt_satiety->SetText(System::string::Convert(food.m_satiety));
		txt_index->SetText(System::string::Convert(food.m_code));
	}

	void OnSave(System::Event*)
	{		
		Utility::FoodType food;
		food.SetName(txt_name->GetText().Data());
		food.SetDescription(txt_desc->GetText().Data());
		try
		{
			food.m_satiety = txt_satiety->GetText().ToInt32();
			food.m_code = txt_index->GetText().ToInt32();
		}
		catch(...)
		{
			System::Logger::Instance()->WriteError(L"Bad satiety value");
			return;
		}
		
		char buf[256];
		System::string path = System::Environment::Instance()->GetCurrentFolder() + L"food\\" + txt_file->GetText();
		path.ToANSI(buf, 256);
		std::ofstream stream(buf, std::ios_base::binary);
		if (!stream.is_open())
		{
			System::Logger::Instance()->WriteError(L"Can't save new food");
			return;
		}
		food.Save(stream);
		stream.close();
		ListAllFood();
	}

	void ListAllFood()
	{
		System::string data = System::Environment::Instance()->GetCurrentFolder() + L"food";
		System::Folder fld;
		fld.Open(data);
		std::list<System::string> files = fld.ListAllItems();
		lst_all_food->RemoveAllItems();
		for each (System::string lst in files)
		{
			lst_all_food->AddItem(new GUI::ListBox::ListBoxItem(lst));
		}
		fld.Close();
	}

	void OnButtonPress(System::Event* event)
	{
		GUI::Balloon* b = static_cast<GUI::Balloon*>(event->reciever);
		if (b)
		{
			b->Blink();
		}
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

		m_gui->Render();
		
		m_driver.SwapBuffers();
	}
};

int main(int argc, char** argv)
{
	System::Window::Instance()->SetTitle(L"FoodMaker");	
	System::Mouse::Instance()->LockInWindow(false);
	OpenGL::Module module;
	module.Init();
	Viewer viewer;
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(&viewer, &Viewer::OnIdle));
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(&viewer, &Viewer::OnKeyDown));
	System::Window::Instance()->Loop();

	module.Destroy();

	return 0;
}