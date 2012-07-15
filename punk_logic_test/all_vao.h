#ifndef _H_ALL_VAO
#define _H_ALL_VAO

#include "../punk_engine/system/driver/video/driver.h"

struct AllVAO
{
	std::auto_ptr<OpenGL::StaticObject> m_male_up;
	std::auto_ptr<OpenGL::StaticObject> m_male_low;
	std::auto_ptr<OpenGL::StaticObject> m_male_feet;
	std::auto_ptr<OpenGL::StaticObject> m_male_hands;
	std::auto_ptr<OpenGL::StaticObject> m_male_head;
	std::auto_ptr<OpenGL::StaticObject> m_male_hair;
	std::auto_ptr<OpenGL::StaticObject> m_mini14;
	std::auto_ptr<OpenGL::StaticObject> m_mini14_backsight;
	std::auto_ptr<OpenGL::StaticObject> m_mini14_holder;

	std::auto_ptr<OpenGL::StaticObject> m_a16a2;
	std::auto_ptr<OpenGL::StaticObject> m_a16a2_backsight;
	std::auto_ptr<OpenGL::StaticObject> m_a16a2_holder;


	static std::auto_ptr<AllVAO> m_instance;

	AllVAO()
	{
		m_male_up.reset(new OpenGL::StaticObject);
		m_male_up->FromFileVAO(System::Environment::Instance()->GetModelFolder() + L"man_up.vao");
		m_male_low.reset(new OpenGL::StaticObject);
		m_male_low->FromFileVAO(System::Environment::Instance()->GetModelFolder() + L"man_low.vao");
		m_male_feet.reset(new OpenGL::StaticObject);
		m_male_feet->FromFileVAO(System::Environment::Instance()->GetModelFolder() + L"man_feet.vao");
		m_male_hands.reset(new OpenGL::StaticObject);
		m_male_hands->FromFileVAO(System::Environment::Instance()->GetModelFolder() + L"man_arms.vao");
		m_male_head.reset(new OpenGL::StaticObject);
		m_male_head->FromFileVAO(System::Environment::Instance()->GetModelFolder() + L"man_head.vao");
		m_male_hair.reset(new OpenGL::StaticObject);
		m_male_hair->FromFileVAO(System::Environment::Instance()->GetModelFolder() + L"man_hair.vao");
		m_mini14.reset(new OpenGL::StaticObject);
		m_mini14->FromFileVAO(System::Environment::Instance()->GetModelFolder() + L"mini14/rifle.vao");
		m_mini14_backsight.reset(new OpenGL::StaticObject);
		m_mini14_backsight->FromFileVAO(System::Environment::Instance()->GetModelFolder() + L"mini14/backsight.vao");
		m_mini14_holder.reset(new OpenGL::StaticObject);
		m_mini14_holder->FromFileVAO(System::Environment::Instance()->GetModelFolder() + L"mini14/holder.vao");
		m_a16a2.reset(new OpenGL::StaticObject);
		m_a16a2->FromFileVAO(System::Environment::Instance()->GetModelFolder() + L"m16a2/rifle.vao");
		m_a16a2_backsight.reset(new OpenGL::StaticObject);
		m_a16a2_backsight->FromFileVAO(System::Environment::Instance()->GetModelFolder() + L"m16a2/backsight.vao");
		m_a16a2_holder.reset(new OpenGL::StaticObject);
		m_a16a2_holder->FromFileVAO(System::Environment::Instance()->GetModelFolder() + L"m16a2/holder.vao");
	}

	static AllVAO* Instance() 
	{
		if (!m_instance.get())
			m_instance.reset(new AllVAO);
		return m_instance.get();
	}

	static void Destroy()
	{
		m_instance.reset(0);
	}
};

#endif