#include <fstream>
#include <memory>
#include "action_male_walk.h"

namespace Virtual
{
	ActionMaleWalk* ActionMaleWalk::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.ToStdString().c_str(), std::ios::binary);
		if (!stream.is_open())
			throw System::PunkInvalidArgumentException(L"Can't open file " + path);
		return CreateFromStream(stream);
	}

	ActionMaleWalk* ActionMaleWalk::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<ActionMaleWalk> node(new ActionMaleWalk);
		node->Load(stream);
		return node.release();
	}
}
