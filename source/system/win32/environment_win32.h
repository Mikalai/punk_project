#ifndef _H_PUNK_ENVIRONMENT_WIN32
#define _H_PUNK_ENVIRONMENT_WIN32

#include "../../string/string.h"
#include "../singletone.h"
#include "../../config.h"

namespace System
{
	SingletoneInterface(Environment, PUNK_ENGINE);

	class PUNK_ENGINE Environment : public Singletone(Environment)
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
	};
}

#endif