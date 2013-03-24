#ifndef _H_PUNK_ENVIRONMENT
#define _H_PUNK_ENVIRONMENT

#include <memory>
#include "../string/string.h"
#include "../config.h"

namespace System
{
	class PUNK_ENGINE Environment
	{
	public:		
		Environment();
		void SetCurrentFolder(const string& dir);
		const string GetCurrentFolder();
		const string GetFontFolder();
		const string GetModelFolder();
		const string GetTextureFolder();
		const string GetMapFolder();
		const string GetSaveFolder();
		const string GetQuestFolder();
		const string GetSoundFolder();
		const string GetShaderFolder();
		const string GetArmatureFolder();
		const string GetWeaponFolder();
		const string GetOpenCLFolder();

		static Environment* Instance();
		static void Destroy();
	private:
		static Environment* m_instance;

	};
}

#endif