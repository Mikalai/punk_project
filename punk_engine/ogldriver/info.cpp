#include "driver.h"

namespace DriverInfo
{
	std::vector<PunkString> Info::GetScreenWidth(Driver* driver)
	{
		std::vector<PunkString> list;
		list.push_back(PunkString("width = ") + driver->m_screen.width);
		return list;
	}

	std::vector<PunkString> Info::GetScreenHeight(Driver *driver)
	{
		std::vector<PunkString> list;
		list.push_back(PunkString("height = ") + driver->m_screen.height);
		return list;
	}

	std::vector<PunkString> Info::GetGLExtensions(Driver *driver)
	{
		PunkString str = (Char*)glGetString(GL_EXTENSIONS);
		std::vector<PunkString> l = str.Split(" ");
		std::vector<PunkString> list;
		for (int i = 0;  i < l.size(); i++)
			list.push_back(l[i]);
		list.push_back(PunkString("total = ") + l.size());
		return list;
	}
}
#include "Driver.h"

namespace DriverInfo
{
	std::vector<PunkString> Info::GetScreenWidth(TDriver* driver)
	{
		std::vector<PunkString> list;
		list.push_back(PunkString("width = ") + driver->m_screen.width);
		return list;
	}

	std::vector<PunkString> Info::GetScreenHeight(TDriver *driver)
	{
		std::vector<PunkString> list;
		list.push_back(PunkString("height = ") + driver->m_screen.height);
		return list;
	}

	std::vector<PunkString> Info::GetGLExtensions(TDriver *driver)
	{
		PunkString str = (Char*)glGetString(GL_EXTENSIONS);
		std::vector<PunkString> l = str.Split(" ");
		std::vector<PunkString> list;
		for (int i = 0;  i < l.size(); i++)
			list.push_back(l[i]);
		list.push_back(PunkString("total = ") + l.size());
		return list;
	}
}