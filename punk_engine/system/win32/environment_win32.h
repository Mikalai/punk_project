#ifndef _H_PUNK_ENVIRONMENT_WIN32
#define _H_PUNK_ENVIRONMENT_WIN32

#include "string_win32.h"
#include "../singletone.h"
#include "../config.h"

namespace System
{
	SingletoneInterface(Environment, MODULE_SYSTEM);

	class MODULE_SYSTEM Environment : public Singletone(Environment)
	{
	public:
		static string GetCurrentFolder();
		static void SetCurrentFolder(const string& dir);
		static string GetFontFolder();
		static string GetModelFolder();
		static string GetTexutreFolder();
		static string GetMapFolder();
		static string GetSaveFolder();
		static string GetQuestFolder();
		static const string GetShaderFolder();
	};
}

#endif