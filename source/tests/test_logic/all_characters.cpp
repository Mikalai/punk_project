#include "all_characters.h"

std::auto_ptr<AllCharacters> AllCharacters::m_instance;

AllCharacters::AllCharacters()
{}

AllCharacters* AllCharacters::Instance()
{
	if (!m_instance.get())
		m_instance.reset(new AllCharacters);
	return m_instance.get();
}

void AllCharacters::Destroy()
{
	m_instance.reset(0);
}

void AllCharacters::Save(std::ostream& stream)
{
	int count = m_characters.size();
	stream.write(reinterpret_cast<const char*>(&count), sizeof(count));
	for each ( std::shared_ptr<Character> chr in m_characters)
	{
		chr->Save(stream);
	}
}

void AllCharacters::Load(std::istream& stream)
{
	int count;
	stream.read(reinterpret_cast<char*>(&count), sizeof(count));
	m_characters.resize(count);
	for each ( std::shared_ptr<Character> chr in m_characters)
	{
		chr.reset(new Character);
		chr->Load(stream);
	}
}