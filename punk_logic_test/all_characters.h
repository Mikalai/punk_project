#ifndef _H_ALL_CHARACTERS
#define _H_ALL_CHARACTERS

#include <memory>
#include "character.h"
#include "../punk_engine/system/system.h"

class AllCharacters
{	
	static std::auto_ptr<AllCharacters> m_instance;
public:
	
	std::vector<std::shared_ptr<Character>> m_characters;	
	Character* MakeNewCharacter();
	
	AllCharacters();	
	static AllCharacters* Instance();
	static void Destroy();

	void Save(std::ostream& stream);
	void Load(std::istream& stream);
};

#endif //	 _H_ALL_CHARACTERS